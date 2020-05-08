/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** DLLoader
*/

#include <dlfcn.h>
#include <iostream>
#include <filesystem>
#include "ArcadeInterfaces.hpp"
#include "DLLoader.hpp"
#include "DLLoaderErrors.hpp"

template<typename T>
std::vector<std::string> DLLoader<T>::getAllFilesInFolder(const char *folderPath)
{
    std::vector<std::string> files;

    for (const auto &entry: std::filesystem::directory_iterator(folderPath))
        if (!std::filesystem::is_directory(entry.path().generic_string()))
            files.push_back(entry.path().generic_string());
    return (files);
}

template<typename T>
std::unique_ptr<T> DLLoader<T>::getLib(const std::string path)
{
    void *handle;
    void *fct;
    std::unique_ptr<T> (*load)(void);
    std::unique_ptr<T> lib;
    char *error;

    handle = dlopen(path.data(), RTLD_LOCAL | RTLD_NOW | RTLD_NODELETE);
    if (!handle)
        throw (OpenFailed(dlerror()));
    dlerror();
    fct = dlsym(handle, "createLib");
    if ((error = dlerror()))
        throw (LibFunctionLoaderNonExistent(error));
    load = reinterpret_cast<std::unique_ptr<T> (*)(void)> (fct);
    if (!load)
        throw (LibFunctionLoaderBadType("File \"" + path + "\" createLib don't have the type: std::unique_ptr<ArcadeInterface> (void)"));
    lib = load();
    dlclose(handle);
    return (lib);
}

template<typename T>
void DLLoader<T>::verifFilesName(std::vector<std::string> files)
{
    for (std::string file: files) {
        if (file.substr(file.find_last_of("/") + 1, file.size()).size() < std::string("lib_arcade_.so").size()  ||
            file.substr(file.find_last_of("/") + 1, file.size()).substr(0, 11).compare("lib_arcade_") != 0      ||
            file.find_last_of(".") == file.npos                                                                 ||
            file.substr(file.find_last_of("."), file.size()).compare(".so") != 0)
                throw (BadFilename("File \"" + file + "\" don't respect filename format (lib_name.so)."));
    }
}

bool compareStrings(std::string file1, std::string file2)
{
    if (file1.find_last_of("/") == file1.npos)
        file1 = "/" + file1;
    if (file2.find_last_of("/") == file2.npos)
        file2 = "/" + file2;
    file1 = file1.substr(file1.find_last_of("/"), file1.size());
    file2 = file2.substr(file2.find_last_of("/"), file2.size());
    return (file1.compare(file2) == 0);
}

template<typename T>
std::vector<std::string> DLLoader<T>::getListOfFiles(const char *folderPath, const char *libPath)
{
    std::vector<std::string> files;

    if (libPath)
        files.push_back(libPath);
    for (std::string file: getAllFilesInFolder(folderPath)) {
        if (!libPath)
            files.push_back(file);
        if (libPath && !compareStrings(file, std::string(libPath)))
            files.push_back(file);
    }
    verifFilesName(files);
    return (files);
}

template<typename T>
std::vector<std::unique_ptr<T>> DLLoader<T>::getAllLibs(const char *folderPath, const char *libPath)
{
    try {
        std::vector<std::string> files = getListOfFiles(folderPath, libPath);
        std::vector<std::unique_ptr<T>> libs = {};

        if (files.size() == 0)
            throw (ZeroLibLoaded("Program need at least one game in ./games"));
        for (std::string file: files)
            libs.push_back(getLib(file));
        return (libs);
    } catch (const DLLoaderError e) {
        std::cerr << e.what() << std::endl;
        std::cerr << e.type() << std::endl;
        exit (84);
    } catch (const std::exception e) {
        std::cerr << e.what() << std::endl;
        exit (84);
    }
}

template class DLLoader<IDisplayModule>;
template class DLLoader<IGameModule>;