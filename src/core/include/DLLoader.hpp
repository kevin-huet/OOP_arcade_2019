/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <string>
#include <vector>
#include <memory>

template <typename T>
class DLLoader {
    public:
        static std::vector<std::string> getAllFilesInFolder(const char *folderPath);
        static std::unique_ptr<T> getLib(std::string path);
        static void verifFilesName(std::vector<std::string> files);
        static std::vector<std::string> getListOfFiles(const char *folderPath, const char *libPath);
        static std::vector<std::unique_ptr<T>> getAllLibs(const char *folderPath, const char *libPath);
};

#endif /* !DLLOADER_HPP_ */
