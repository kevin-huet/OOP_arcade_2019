/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <memory>
#include <random>
#include <list>
#include "ArcadeInterfaces.hpp"

typedef std::pair<std::string,int> score;

class nibbler : public IGameModule {
    public:
        nibbler();
        ~nibbler();
        bool loadFromFile(const std::string &filepath);
        bool loadFromFile();
        bool saveToFile(const std::string &filepath) const;
        bool saveToFile() const;
        void setPlayerName(const std::string &);
        std::pair<std::string, int> getScore() const;
        std::vector<std::pair<std::string, int>> getBestScores() const;
        void setBestScores();
        void sort(void);
        void reset();
        void update(const IDisplayModule &lib);
        void render(IDisplayModule &lib) const;
        const std::string &getLibName() const;
    private:
        void sortScores(void);
        bool strIsNumber(std::string str);
        void renderSnake(IDisplayModule &lib) const;
        void renderMap(IDisplayModule &lib) const;
        void renderFruit(IDisplayModule &lib) const;
        void updateKey(const IDisplayModule &lib);
        void moveSnake();
        void removeEndSnake();
        void eatFruit();
        bool isCorrect();
        void endTest();
    private:
        enum gameState {GAME, WIN, LOSE};
        gameState state = GAME;
        std::string libName = "Nibbler";
        std::vector<score> scoreList;
        std::vector<score> scoreListSort;
        std::string name;
        int actualScore = 0;
        score bestScore;
        float moveSpeed = 80;
        float moveTimer = moveSpeed;
        std::pair<int, int> mapSize = {30, 20};
        std::pair<int, int> direction = {0, 1};
        std::list<std::pair<int, int>> snake;
        IDisplayModule::Keys lastKey;
        IDisplayModule::Keys lastActualiseKey;
        std::pair<int, int> fruit;
        bool fruitEaten = false;
};

#endif /* !NIBBLER_HPP_ */