/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** CoreErrors
*/

#ifndef COREERRORS_HPP_
#define COREERRORS_HPP_

#include <string>
#include <exception>

class CoreError : public std::exception
{
    public:
        CoreError(std::string const &message, std::string const type) noexcept {
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

class BadArguments : public CoreError
{
    public:
        BadArguments(std::string const &message) noexcept : CoreError(message, "Bad Arguments")
        {}
};

#endif /* !COREERRORS_HPP_ */
