/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibsErrors
*/

#ifndef LIBSERRORS_HPP_
#define LIBSERRORS_HPP_

#include <string>
#include <exception>

class LibsError : public std::exception
{
    public:
        LibsError(std::string const &message, std::string const type) noexcept {
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

class NeedAsset : public LibsError
{
    public:
        NeedAsset(std::string const &message) noexcept : LibsError(message, "Need asset")
        {}
};
#endif /* !LIBSERRORS_HPP_ */
