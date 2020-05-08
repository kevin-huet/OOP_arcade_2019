/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Mob
*/

#include "Mob.hpp"

void Mob::render(IDisplayModule &lib, bool chased) const
{
    if (chased)
        lib.setColor(IDisplayModule::BLUE);    
    else
        lib.setColor(_color);
    lib.putFillCircle(_pos.first * 16 + 4, _pos.second * 16 + 32 + 4, 4);
}

void Mob::move(std::vector<std::vector<mapPoint>> map, const IDisplayModule &lib, bool chased)
{
    _moveTimer -= lib.getDelta();
    if (_moveTimer <= 0) {
        if (chased)
            _moveTimer += _moveSpeed;
        _moveTimer += _moveSpeed;
        if (_pos.first + _direction.first > map[0].size())
            _pos.first = map[0].size() - 1;
        else if (_pos.second + _direction.second > map.size())
            _pos.second = map[0].size() - 1;
        else if (_pos.first + _direction.first == map[0].size())
            _pos.first = 0;
        else if (_pos.second + _direction.second == map.size())
            _pos.second = 0;
        else if (map[_pos.second + _direction.second][_pos.first + _direction.first] != WALL)
            _pos = {_pos.first + _direction.first, _pos.second + _direction.second};
    }
}