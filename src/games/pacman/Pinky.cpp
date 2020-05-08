/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Pinky
*/

#include "Pinky.hpp"

void Pinky::chooseDirection(std::vector<std::vector<mapPoint>> map, Mob player)
{
    coord prediction;
    bool find = false;

    if (_moves.size() == 0) {
        if (ABSOLUE((int) (_pos.first - player.getPos().first)) < 5 && ABSOLUE((int) (_pos.second - player.getPos().second)) < 5)
            if (!setDestination(player.getPos(), map)) {
                _direction = {rand() % 3 - 1, 0};
                return;
            }
        for (size_t i = 5; !find; i--) {
            prediction = {player.getPos().first + player.getDir().first * i, player.getPos().second + player.getDir().second * i};
            if (checkDestination(prediction, map))
                find = true;
        }
        if (!setDestination(prediction, map))
            _direction = {rand() % 3 - 1, 0};
    }
}