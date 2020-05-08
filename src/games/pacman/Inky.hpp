/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Inky
*/

#ifndef INKY_HPP_
#define INKY_HPP_

#include "Fantom.hpp"

class Inky : public Fantom {
    public:
        Inky() : Fantom()
        {
            _color = IDisplayModule::Colors::CYAN;
            _pos = {10, 9};
            _basePos = {10, 9};
            _moveSpeed = 80;
        }
        ~Inky()
        {}

        void chooseDirection(std::vector<std::vector<mapPoint>> map, Mob player);
    protected:
    private:
};
#endif /* !INKY_HPP_ */
