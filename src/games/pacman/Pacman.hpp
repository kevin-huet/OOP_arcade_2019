/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <memory>
#include <random>
#include "ArcadeInterfaces.hpp"
#include "Fantom.hpp"
#include "Player.hpp"
#include "Blinky.hpp"
#include "Clyde.hpp"
#include "Inky.hpp"
#include "Pinky.hpp"
#include "enums.hpp"

typedef std::pair<std::string, int> score;

const std::vector<std::vector<mapPoint>> mapConst = {
    {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
    {WALL, SUPD, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, WALL, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, SUPD, WALL},
    {WALL, DOTS, WALL, WALL, DOTS, WALL, WALL, WALL, DOTS, WALL, DOTS, WALL, WALL, WALL, DOTS, WALL, WALL, DOTS, WALL},
    {WALL, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, WALL},
    {WALL, DOTS, WALL, WALL, DOTS, WALL, DOTS, WALL, WALL, WALL, WALL, WALL, DOTS, WALL, DOTS, WALL, WALL, DOTS, WALL},
    {WALL, DOTS, DOTS, DOTS, DOTS, WALL, DOTS, DOTS, DOTS, WALL, DOTS, DOTS, DOTS, WALL, DOTS, DOTS, DOTS, DOTS, WALL},
    {WALL, WALL, WALL, WALL, DOTS, WALL, WALL, WALL, DOTS, WALL, DOTS, WALL, WALL, WALL, DOTS, WALL, WALL, WALL, WALL},
    {VOID, VOID, VOID, WALL, DOTS, WALL, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, WALL, DOTS, WALL, VOID, VOID, VOID},
    {WALL, WALL, WALL, WALL, DOTS, WALL, DOTS, WALL, WALL, WALL, WALL, WALL, DOTS, WALL, DOTS, WALL, WALL, WALL, WALL},
    {VOID, VOID, VOID, VOID, DOTS, DOTS, DOTS, WALL, VOID, VOID, VOID, WALL, DOTS, DOTS, DOTS, VOID, VOID, VOID, VOID},
    {WALL, WALL, WALL, WALL, DOTS, WALL, DOTS, WALL, WALL, WALL, WALL, WALL, DOTS, WALL, DOTS, WALL, WALL, WALL, WALL},
    {VOID, VOID, VOID, WALL, DOTS, WALL, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, WALL, DOTS, WALL, VOID, VOID, VOID},
    {WALL, WALL, WALL, WALL, DOTS, WALL, DOTS, WALL, WALL, WALL, WALL, WALL, DOTS, WALL, DOTS, WALL, WALL, WALL, WALL},
    {WALL, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, WALL, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, WALL},
    {WALL, DOTS, WALL, WALL, DOTS, WALL, WALL, WALL, DOTS, WALL, DOTS, WALL, WALL, WALL, DOTS, WALL, WALL, DOTS, WALL},
    {WALL, DOTS, DOTS, WALL, DOTS, DOTS, DOTS, DOTS, DOTS, SPWN, DOTS, DOTS, DOTS, DOTS, DOTS, WALL, DOTS, DOTS, WALL},
    {WALL, WALL, DOTS, WALL, DOTS, WALL, DOTS, WALL, WALL, WALL, WALL, WALL, DOTS, WALL, DOTS, WALL, DOTS, WALL, WALL},
    {WALL, DOTS, DOTS, DOTS, DOTS, WALL, DOTS, DOTS, DOTS, WALL, DOTS, DOTS, DOTS, WALL, DOTS, DOTS, DOTS, DOTS, WALL},
    {WALL, DOTS, WALL, WALL, WALL, WALL, WALL, WALL, DOTS, WALL, DOTS, WALL, WALL, WALL, WALL, WALL, WALL, DOTS, WALL},
    {WALL, SUPD, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, DOTS, SUPD, WALL},
    {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL} 
};

class Pacman : public IGameModule {
    public:
        Pacman();
        ~Pacman();
        bool loadFromFile(const std::string &filepath);
        bool loadFromFile();
        bool saveToFile(const std::string &filepath) const;
        bool saveToFile() const;
        void setPlayerName(const std::string &);
        std::pair<std::string, int> getScore() const;
        std::vector<std::pair<std::string, int>> getBestScores() const;
        void reset();
        void update(const IDisplayModule &lib);
        void render(IDisplayModule &lib) const;
        const std::string &getLibName() const;
    
    private:
        void sortScores(void);
        bool strIsNumber(std::string str);
        void endTest();
        void allMove(const IDisplayModule &lib);
        void doorOpening();
        void superTimerClock();
        void changeDirection(const IDisplayModule &lib);
        void renderMap(IDisplayModule &lib) const;
    private:
        enum gameState {GAME, WIN, LOSE};
        gameState state = GAME;
        std::string libName = "Pacman";
        std::vector<score> scoreList;
        std::vector<score> scoreListSort;
        std::string name;
        int actualScore = 0;
        score bestScore;
        float moveSpeed = 80;
        float moveTimer = moveSpeed;
        bool superPower = false;
        int superSpeed = 50;
        int superTimer = superSpeed;
        int doorTime = 0;
        Player pacman;
        std::vector<Fantom *> fantoms = {new Blinky(), new Clyde(), new Inky(), new Pinky()};
        std::vector<std::vector<mapPoint>> map = mapConst;
};

#endif /* !pacman_HPP_ */