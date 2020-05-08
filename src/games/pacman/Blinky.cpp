/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Blinky
*/

#include "Blinky.hpp"

void Blinky::chooseDirection(std::vector<std::vector<mapPoint>> map, Mob player)
{
    if (_moves.size() == 0) {
        if (!setDestination(player.getPos(), map))
            _direction = {rand() % 3 - 1, 0};
    }
}