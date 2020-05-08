/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Pinky
*/

#ifndef PINKY_HPP_
#define PINKY_HPP_

#include "Fantom.hpp"

class Pinky : public Fantom {
    public:
        Pinky() : Fantom()
        {
            _color = IDisplayModule::Colors::MAGENTA;
            _pos = {9, 9};
            _basePos = {9, 9};
            _moveSpeed = 80;
        }
        ~Pinky()
        {}

        void chooseDirection(std::vector<std::vector<mapPoint>> map, Mob player);
    protected:
    private:
};

#endif /* !PINKY_HPP_ */
