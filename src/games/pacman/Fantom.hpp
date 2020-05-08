/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Fantom
*/

#ifndef FANTOM_HPP_
#define FANTOM_HPP_

#define ABSOLUE(a) (a < 0 ? a * -1 : a)

#include "Mob.hpp"

class Fantom : public Mob {
    public:
        virtual ~Fantom() = default;

        virtual void chooseDirection([[maybe_unused]]std::vector<std::vector<mapPoint>> map, [[maybe_unused]]Mob player) = 0;
        void move(std::vector<std::vector<mapPoint>> map, const IDisplayModule &lib, bool chased);
    protected:
        bool setDestination(coord newDest, std::vector<std::vector<mapPoint>> map);
        bool checkDestination(coord dest, std::vector<std::vector<mapPoint>> map);

    private:
        bool findPath(std::vector<std::vector<mapPoint>> map);
        bool recursiveSolve(coord point, std::vector<std::vector<bool>> &wasHere, std::vector<std::vector<mapPoint>> map);
        bool recursiveSolveLeft(coord point, std::vector<std::vector<bool>> &wasHere, std::vector<std::vector<mapPoint>> map);
        bool recursiveSolveRight(coord point, std::vector<std::vector<bool>> &wasHere, std::vector<std::vector<mapPoint>> map);
        bool recursiveSolveUp(coord point, std::vector<std::vector<bool>> &wasHere, std::vector<std::vector<mapPoint>> map);
        bool recursiveSolveDown(coord point, std::vector<std::vector<bool>> &wasHere, std::vector<std::vector<mapPoint>> map);

    protected:
        std::vector<coordInt> _moves = {};
        coord _destination = {0, 0};
};

#endif /* !FANTOM_HPP_ */
