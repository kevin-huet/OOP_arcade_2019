/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Clyde
*/

#ifndef CLYDE_HPP_
#define CLYDE_HPP_

#include "Fantom.hpp"

class Clyde : public Fantom {
    public:
        Clyde() : Fantom()
        {
            _color = IDisplayModule::Colors::GREEN;
            _pos = {8, 9};
            _basePos = {8, 9};
            _moveSpeed = 80;
        }
        ~Clyde()
        {}

        void chooseDirection(std::vector<std::vector<mapPoint>> map, Mob player);
    protected:
    private:
};
#endif /* !CLYDE_HPP_ */
