/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Mob.hpp"

class Player : public Mob {
    public:
        Player() : Mob()
        {
            _color = IDisplayModule::Colors::YELLOW;
            _pos = {9, 15};
            _basePos = {9, 15};
            _moveSpeed = 100;
        }
        ~Player()
        {}

        void chooseDirection(const IDisplayModule &lib, std::vector<std::vector<mapPoint>> map);
};

#endif /* !PLAYER_HPP_ */
