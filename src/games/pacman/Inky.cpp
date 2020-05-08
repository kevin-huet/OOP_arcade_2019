/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Inky
*/

#include "Inky.hpp"

void Inky::chooseDirection(std::vector<std::vector<mapPoint>> map, Mob player)
{
    coord destination;

    if (_moves.size() == 0) {
        destination = {rand() % map[0].size(), rand() % map.size()};
        while (checkDestination(destination, map))
            destination = {rand() % map[0].size(), rand() % map.size()};
        if (!setDestination(destination, map))
            _direction = {rand() % 3 - 1, 0};
    }

    if (_pos.first - 3 <= player.getPos().first && player.getPos().first <= _pos.first + 3)
        if (_pos.second - 3 <= player.getPos().second && player.getPos().second <= _pos.second + 3) {
            destination = {_pos.first + player.getDir().first, _pos.second + player.getDir().second};
            if (!checkDestination(destination, map))
                destination = {_pos.first + player.getDir().first, _pos.second};
            if (!checkDestination(destination, map))
                destination = {_pos.first, _pos.second + player.getDir().second};
            if (!checkDestination(destination, map))
                destination = {_pos.first, _pos.second};
            setDestination(destination, map);
        }
}