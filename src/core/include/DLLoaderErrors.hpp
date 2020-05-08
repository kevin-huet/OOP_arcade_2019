/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** DLLoaderErrors
*/

#ifndef DLLOADERERRORS_HPP_
#define DLLOADERERRORS_HPP_

#include <string>
#include <exception>

class DLLoaderError : public std::exception
{
    public:
        DLLoaderError(std::string const &message, std::string const type) noexcept {
            _message = message;
            _type = type;
        }

        const char *type() const noexcept {
            return (_type.data());
        }
        const char *what() const noexcept override {
            return (_message.data());
        }
    protected:
        std::string _message;
        std::string _type;
};

class ZeroLibLoaded : public DLLoaderError
{
    public:
        ZeroLibLoaded(std::string const &message) noexcept : DLLoaderError(message, "Zero Lib Loaded")
        {}
};

class BadFilename : public DLLoaderError
{
    public:
        BadFilename(std::string const &message) noexcept : DLLoaderError(message, "Bad Filename")
        {}
};

class OpenFailed : public DLLoaderError
{
    public:
        OpenFailed(std::string const &message) noexcept : DLLoaderError(message, "Open Failed")
        {}
};

class FileNonExistent : public DLLoaderError
{
    public:
        FileNonExistent(std::string const &message) noexcept : DLLoaderError(message, "File Non Existent")
        {}
};

class LibFunctionLoaderNonExistent : public DLLoaderError
{
    public:
        LibFunctionLoaderNonExistent(std::string const &message) noexcept : DLLoaderError(message, "Lib Function Loader Non Existent")
        {}
};

class LibFunctionLoaderBadType : public DLLoaderError
{
    public:
        LibFunctionLoaderBadType(std::string const &message) noexcept : DLLoaderError(message, "Lib Function Loader Bad Type")
        {}
};

#endif /* !DLLOADERERRORS_HPP_ */
