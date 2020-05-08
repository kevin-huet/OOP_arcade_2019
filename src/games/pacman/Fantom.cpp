/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Fantom
*/

#include "Fantom.hpp"

bool Fantom::recursiveSolveLeft(coord point, std::vector<std::vector<bool>> &wasHere, std::vector<std::vector<mapPoint>> map)
{
    if (point.second > 0)
        if (recursiveSolve({point.first, point.second - 1}, wasHere, map)) {
            _moves.push_back({0,-1});
            return (true);
        }
    if (point.first < map[point.second].size() - 1)
        if (recursiveSolve({point.first + 1, point.second}, wasHere, map)) {
            _moves.push_back({1,0});
            return (true);
        }
    if (point.first > 0)
        if (recursiveSolve({point.first - 1, point.second}, wasHere, map)) {
            _moves.push_back({-1,0});
            return (true);
        }
    if (point.second < map.size() - 1)
        if (recursiveSolve({point.first, point.second + 1}, wasHere, map)) {
            _moves.push_back({0,1});
            return (true);
        }
    return (false);
}

bool Fantom::recursiveSolveRight(coord point, std::vector<std::vector<bool>> &wasHere, std::vector<std::vector<mapPoint>> map)
{
    if (point.second < map.size() - 1)
        if (recursiveSolve({point.first, point.second + 1}, wasHere, map)) {
            _moves.push_back({0,1});
            return (true);
        }
    if (point.first < map[point.second].size() - 1)
        if (recursiveSolve({point.first + 1, point.second}, wasHere, map)) {
            _moves.push_back({1,0});
            return (true);
        }
    if (point.first > 0)
        if (recursiveSolve({point.first - 1, point.second}, wasHere, map)) {
            _moves.push_back({-1,0});
            return (true);
        }
    if (point.second > 0)
        if (recursiveSolve({point.first, point.second - 1}, wasHere, map)) {
            _moves.push_back({0,-1});
            return (true);
        }
    return (false);
}

bool Fantom::recursiveSolveUp(coord point, std::vector<std::vector<bool>> &wasHere, std::vector<std::vector<mapPoint>> map)
{
    if (point.first > 0)
        if (recursiveSolve({point.first - 1, point.second}, wasHere, map)) {
            _moves.push_back({-1,0});
            return (true);
        }
    if (point.second > 0)
        if (recursiveSolve({point.first, point.second - 1}, wasHere, map)) {
            _moves.push_back({0,-1});
            return (true);
        }
    if (point.second < map.size() - 1)
        if (recursiveSolve({point.first, point.second + 1}, wasHere, map)) {
            _moves.push_back({0,1});
            return (true);
        }
    if (point.first < map[point.second].size() - 1)
        if (recursiveSolve({point.first + 1, point.second}, wasHere, map)) {
            _moves.push_back({1,0});
            return (true);
        }
    return (false);
}

bool Fantom::recursiveSolveDown(coord point, std::vector<std::vector<bool>> &wasHere, std::vector<std::vector<mapPoint>> map)
{
    if (point.first < map[point.second].size() - 1)
        if (recursiveSolve({point.first + 1, point.second}, wasHere, map)) {
            _moves.push_back({1,0});
            return (true);
        }
    if (point.second > 0)
        if (recursiveSolve({point.first, point.second - 1}, wasHere, map)) {
            _moves.push_back({0,-1});
            return (true);
        }
    if (point.second < map.size() - 1)
        if (recursiveSolve({point.first, point.second + 1}, wasHere, map)) {
            _moves.push_back({0,1});
            return (true);
        }
    if (point.first > 0)
        if (recursiveSolve({point.first - 1, point.second}, wasHere, map)) {
            _moves.push_back({-1,0});
            return (true);
        }
    return (false);
}

bool Fantom::recursiveSolve(coord point, std::vector<std::vector<bool>> &wasHere, std::vector<std::vector<mapPoint>> map)
{
    if (point.first == _destination.first && point.second == _destination.second)
        return (true);
    if (map[point.second][point.first] == WALL || wasHere[point.second][point.first])
        return (false);
    wasHere[point.second][point.first] = true;
    if (point.first < _destination.first && ABSOLUE((int) (point.first - _destination.first)) > ABSOLUE((int) (point.second - _destination.second)))
        return (recursiveSolveDown(point, wasHere, map));
    else if (point.first > _destination.first && ABSOLUE((int) (point.first - _destination.first)) > ABSOLUE((int) (point.second - _destination.second)))
        return (recursiveSolveUp(point, wasHere, map));
    else if (point.second < _destination.second)
        return (recursiveSolveRight(point, wasHere, map));
    else if (point.second > _destination.second)
        return (recursiveSolveLeft(point, wasHere, map));
    return (false);
}

bool Fantom::findPath(std::vector<std::vector<mapPoint>> map)
{
    std::vector<std::vector<bool>> wasHere;

    for (size_t i = 0; i < map.size(); i++) {
        wasHere.push_back({});
        for (size_t j = 0; j < map[i].size(); j++) {
            wasHere[i].push_back(false);
        }
    }
    return (recursiveSolve(_pos, wasHere, map));
}

bool Fantom::setDestination(coord newDest, std::vector<std::vector<mapPoint>> map)
{
    _destination = newDest;
    return (findPath(map));
}

bool Fantom::checkDestination(coord dest, std::vector<std::vector<mapPoint>> map)
{
    return (dest.first < map[0].size() && dest.second < map.size() && map[dest.second][dest.first] != WALL);
}

void Fantom::move(std::vector<std::vector<mapPoint>> map, const IDisplayModule &lib, bool chased)
{
    _moveTimer -= lib.getDelta();
    if (_moveTimer <= 0) {
        if (_moves.size() != 0) {
            _direction = _moves[_moves.size() - 1];
            _moves.pop_back();
        }
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