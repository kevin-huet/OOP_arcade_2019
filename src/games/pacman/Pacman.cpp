/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Pacman
*/

#include "Pacman.hpp"

extern "C" std::unique_ptr<IGameModule> createLib(void)
{
    return std::make_unique<Pacman>();
}

Pacman::Pacman()
{
    loadFromFile();
    sortScores();
    if (scoreListSort.size() != 0)
        bestScore = scoreListSort[0];
    else
        bestScore = {"", 0};
}

Pacman::~Pacman()
{
    for (auto &&fantom: fantoms)
        delete (fantom);
}

bool Pacman::strIsNumber(std::string str)
{
    for (char c: str) {
        if (!isalpha(c))
            return (false);
    }
    return (true);
}

bool Pacman::loadFromFile(const std::string &filepath)
{
    std::string file_line;
    std::ifstream file (filepath, std::ifstream::in);

    scoreList.clear();
    if (file.good()) {
        while (getline(file, file_line)) {
            if (file_line.find_first_of(":") != file_line.find_last_of(":") || file_line.find(':') == file_line.npos || 
            file_line.find(':') == 0 || strIsNumber(file_line.substr(file_line.find(':') + 1, file_line.size()))) {
                scoreList.clear();
                return (false);
            }
            scoreList.push_back({file_line.substr(0, file_line.find(':')), std::stoi(file_line.substr(file_line.find(':') + 1, file_line.size()))});
        }
        return (true);
    }
    else
        return (false);
}

bool Pacman::loadFromFile()
{
    return (loadFromFile(SAVE_PATH + libName));
}

bool Pacman::saveToFile(const std::string &filepath) const
{
    std::ofstream file;

    file.open(filepath, std::ofstream::out | std::ofstream::trunc);
    if (file.good()) {
        file.clear();
        for (score player: scoreListSort)
            file << player.first << ":" << player.second << std::endl;
        return (true);
    }
    return (false);
}

bool Pacman::saveToFile() const
{
    return (saveToFile(SAVE_PATH + libName));
}

void Pacman::setPlayerName(const std::string &_name)
{
    this->name = _name;
}

std::pair<std::string, int> Pacman::getScore() const
{
    std::pair<std::string, int> p;
    p.first = this->name;
    p.second = this->actualScore;
    return (p);
}

void Pacman::sortScores(void)
{
    scoreListSort.clear();
	std::copy(this->scoreList.begin(), this->scoreList.end(), std::back_inserter<std::vector<score>>(this->scoreListSort));
	std::sort(this->scoreListSort.begin(), this->scoreListSort.end(), [](const score& l, const score& r) {
		if (l.second != r.second)
			return l.second > r.second;
		return l.first < r.first;
	});
}

std::vector<std::pair<std::string, int>> Pacman::getBestScores() const
{
    return (this->scoreListSort);
}

void Pacman::endTest()
{
    size_t count = 0;
    for (auto &&line: map)
        for (auto &&point: line)
            if (point == DOTS)
                count++;
    if (!count) {
        scoreList.push_back(getScore());
        sortScores();
        saveToFile();
        state = WIN;
    }
    for (auto &&fantom: fantoms)
        if (fantom->getPos() == pacman.getPos()) {
            if (!superPower) {
                scoreList.push_back(getScore());
                sortScores();
                saveToFile();
                state = LOSE;
            }
            else {
                actualScore += 20;
                fantom->reset();
            }
        }
}

void Pacman::allMove(const IDisplayModule &lib)
{
    pacman.move(map, lib, false);
    if (map[pacman.getPos().second][pacman.getPos().first] == DOTS) {
        map[pacman.getPos().second][pacman.getPos().first] = VOID;
        actualScore += 1;
    }
    if (map[pacman.getPos().second][pacman.getPos().first] == SUPD) {
        map[pacman.getPos().second][pacman.getPos().first] = VOID;
        actualScore += 1;
        superPower = true;
        superTimer = superSpeed;
    }
    for (auto &&fantom: fantoms) {
        fantom->chooseDirection(map, pacman);
        fantom->move(map, lib, superPower);
    }
    endTest();
}

void Pacman::doorOpening()
{
    doorTime++;
    if (doorTime == 15)
        map[8][9] = WALD;
}

void Pacman::superTimerClock()
{
    if (superPower) {
        superTimer--;
        if (superTimer == 0)
            superPower = false;
    }
}

void Pacman::update(const IDisplayModule &lib)
{
    if (state == GAME) {
        moveTimer -= lib.getDelta();
        pacman.chooseDirection(lib, map);
        allMove(lib);
        if (moveTimer <= 0) {
            moveTimer += moveSpeed;
            doorOpening();
            superTimerClock();
        }
    }
}

void Pacman::render(IDisplayModule &lib) const
{
    if (state == GAME) {
        lib.setColor(IDisplayModule::WHITE);
        if (getBestScores().size() == 0)
            lib.putText(std::string("HighScore: 0"), 16, 0, 8);
        else
            lib.putText(std::string("HighScore: ") + std::to_string(getBestScores()[0].second), 16, 0, 8);
        lib.putText(std::string("Score: ") + std::to_string(actualScore), 16, 240, 8);
        renderMap(lib);
        pacman.render(lib, false);
        for (auto &&fantom: fantoms)
            fantom->render(lib, superPower);
    }
    else {
        lib.setColor(IDisplayModule::WHITE);
        if (state == WIN)
            lib.putText(std::string("You Won ! GG !"), 32, 40, 80);
        else
            lib.putText(std::string("You Lost ... :c"), 32, 40, 80);
        if (bestScore.second < actualScore) {
            lib.putText(std::string("HighScore: ") + std::to_string(actualScore) + std::string(" by " + name), 16, 40, 140);
            lib.putText(std::string("NEW HIGHSCORE !!!"), 16, 40, 180);
        }
        else
            lib.putText(std::string("HighScore: ") + std::to_string(bestScore.second) + std::string(" by " + bestScore.first), 16, 40, 140);
    }
}

void Pacman::renderMap(IDisplayModule &lib) const
{
    size_t i = 0;
    size_t j = 0;

    for (auto &&line: map) {
        j = 0;
        for (auto &&point: line) {
            if (point == WALL) {
                lib.setColor(IDisplayModule::BLUE);
                lib.putFillRect(j * 16, 32 + i * 16, 16, 16);
            }
            if (point == WALD) {
                lib.setColor(IDisplayModule::BLUE);
                lib.putLine(j * 16, 32 + i * 16 + 8, (j + 1) * 16, 32 + i * 16 + 8);
            }
            if (point == DOTS) {
                lib.setColor(IDisplayModule::WHITE);
                lib.putCircle(j * 16 + 6, 6 + 32 + i * 16, 2);
            }
            if (point == SUPD) {
                lib.setColor(IDisplayModule::YELLOW);
                lib.putCircle(j * 16 + 6, 6 + 32 + i * 16, 2);
            }
            j++;
        }
        i++;
    }
}

const std::string &Pacman::getLibName() const
{
    return (libName);
}

void Pacman::reset()
{
    loadFromFile();
    sortScores();
    if (scoreListSort.size() != 0)
        bestScore = scoreListSort[0];
    else
        bestScore = {"", 0};
    actualScore = 0;
    moveTimer = 10;
    pacman.reset();
    for (auto &&fantom: fantoms)
        fantom->reset();
    map = mapConst;
    state = GAME;
    doorTime = 0;
}