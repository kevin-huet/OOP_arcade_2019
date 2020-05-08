/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Blinky
*/

#ifndef BLINKY_HPP_
#define BLINKY_HPP_

#include "Fantom.hpp"

class Blinky : public Fantom {
    public:
        Blinky() : Fantom()
        {
            _color = IDisplayModule::Colors::RED;
            _pos = {10, 9};
            _basePos = {10, 9};
            _moveSpeed = 80;
        }
        ~Blinky()
        {}

        void chooseDirection([[maybe_unused]]std::vector<std::vector<mapPoint>> map, [[maybe_unused]]Mob player) override;
    protected:
    private:
};
#endif /* !BLINKY_HPP_ */
