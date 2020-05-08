/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Player
*/

#include "Player.hpp"

void Player::chooseDirection(const IDisplayModule &lib, std::vector<std::vector<mapPoint>> map)
{
    if (lib.isKeyPressed(IDisplayModule::UP) && (_pos.second == 0 || (map[_pos.second + -1][_pos.first + 0] != WALL && map[_pos.second + -1][_pos.first + 0] != WALD)))
        _direction = {0, -1};
    if (lib.isKeyPressed(IDisplayModule::DOWN) && (_pos.second == map.size() - 1 || (map[_pos.second + 1][_pos.first + 0] != WALL && map[_pos.second + 1][_pos.first + 0] != WALD)))
        _direction = {0, 1};
    if (lib.isKeyPressed(IDisplayModule::LEFT) && (_pos.first == 0 || (map[_pos.second + 0][_pos.first + -1] != WALL && map[_pos.second + 0][_pos.first + -1] != WALD)))
        _direction = {-1, 0};
    if (lib.isKeyPressed(IDisplayModule::RIGHT) && (_pos.first == map[0].size() - 1 || (map[_pos.second + 0][_pos.first + 1] != WALL && map[_pos.second + 0][_pos.first + 1] != WALD)))
        _direction = {1, 0};
}