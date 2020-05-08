/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Mob
*/

#ifndef MOB_HPP_
#define MOB_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <memory>
#include <random>
#include "ArcadeInterfaces.hpp"
#include "enums.hpp"

typedef std::pair<size_t, size_t> coord;
typedef std::pair<int, int> coordInt;

class Mob {
    public:
        Mob()
        {}
        ~Mob()
        {}

        void render(IDisplayModule &lib, bool chased) const;
        coord getPos() const {return (_pos);}
        coord getDir() const {return (_direction);}
        
        void move(std::vector<std::vector<mapPoint>> map, const IDisplayModule &lib, bool chased);
        void reset() {_pos = _basePos; _direction = {0, 0};};

    protected:
        IDisplayModule::Colors _color;
        coordInt _direction = {0, 0};
        coord _basePos;
        coord _pos;
        float _moveTimer = 0;
        float _moveSpeed;
};

#endif /* !MOB_HPP_ */
