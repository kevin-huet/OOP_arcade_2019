/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** nibbler
*/

#include "nibbler.hpp"

extern "C" std::unique_ptr<IGameModule> createLib(void)
{
    return std::make_unique<nibbler>();
}

nibbler::nibbler()
{
    loadFromFile();
    sortScores();
    if (scoreListSort.size() != 0)
        bestScore = scoreListSort[0];
    else
        bestScore = {"", 0};
    this->lastKey = IDisplayModule::Keys::DOWN;
    this->lastActualiseKey = IDisplayModule::Keys::DOWN;
    this->actualScore = 0;
    snake.clear();
    snake.push_back({mapSize.first / 2, mapSize.second / 2});
    snake.push_back({mapSize.first / 2, mapSize.second / 2 - 1});
    snake.push_back({mapSize.first / 2, mapSize.second / 2 - 2});
    snake.push_back({mapSize.first / 2, mapSize.second / 2 - 3});
    srand(time(NULL));
    fruit = {rand() % mapSize.first, rand() % mapSize.second};
    while (!isCorrect())
        fruit = {rand() % mapSize.first, rand() % mapSize.second};
}

nibbler::~nibbler()
{

}

bool nibbler::strIsNumber(std::string str)
{
    for (char c: str) {
        if (!isalpha(c))
            return (false);
    }
    return (true);
}

bool nibbler::loadFromFile(const std::string &filepath)
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

bool nibbler::loadFromFile()
{
    return (loadFromFile(SAVE_PATH + libName));
}

bool nibbler::saveToFile(const std::string &filepath) const
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

bool nibbler::saveToFile() const
{
    return (saveToFile(SAVE_PATH + libName));
}

void nibbler::setPlayerName(const std::string &_name)
{
    this->name = _name;
}

std::pair<std::string, int> nibbler::getScore() const
{
    std::pair<std::string, int> p;
    p.first = this->name;
    p.second = this->actualScore;
    return (p);
}

void nibbler::sortScores(void)
{
    scoreListSort.clear();
	std::copy(this->scoreList.begin(), this->scoreList.end(), std::back_inserter<std::vector<score>>(this->scoreListSort));
	std::sort(this->scoreListSort.begin(), this->scoreListSort.end(), [](const score& l, const score& r) {
		if (l.second != r.second)
			return l.second > r.second;
		return l.first < r.first;
	});
}

std::vector<std::pair<std::string, int>> nibbler::getBestScores() const
{
    return (this->scoreListSort);
}

const std::string &nibbler::getLibName() const
{
    return (libName);
}

void nibbler::reset()
{
    loadFromFile();
    sortScores();
    if (scoreListSort.size() != 0)
        bestScore = scoreListSort[0];
    else
        bestScore = {"", 0};
    actualScore = 0;
    state = GAME;
    snake.clear();
    snake.push_back({mapSize.first / 2, mapSize.second / 2});
    snake.push_back({mapSize.first / 2, mapSize.second / 2 - 1});
    snake.push_back({mapSize.first / 2, mapSize.second / 2 - 2});
    snake.push_back({mapSize.first / 2, mapSize.second / 2 - 3});
    direction = {0, 1};
    lastKey = IDisplayModule::DOWN;
    lastActualiseKey = IDisplayModule::Keys::DOWN;
    moveTimer = moveSpeed;
    fruitEaten = false;
    srand(time(NULL));
    fruit = {rand() % mapSize.first, rand() % mapSize.second};
    while (!isCorrect())
        fruit = {rand() % mapSize.first, rand() % mapSize.second};
}

void nibbler::updateKey(const IDisplayModule &lib)
{
    if (lib.isKeyPressedOnce(IDisplayModule::LEFT) && lastActualiseKey != IDisplayModule::LEFT && lastActualiseKey != IDisplayModule::RIGHT) {
        lastKey = IDisplayModule::LEFT;
        direction = {-1, 0};
    }
    if (lib.isKeyPressedOnce(IDisplayModule::RIGHT) && lastActualiseKey != IDisplayModule::LEFT && lastActualiseKey != IDisplayModule::RIGHT) {
        lastKey = IDisplayModule::RIGHT;
        direction = {1, 0};
    }
    if (lib.isKeyPressedOnce(IDisplayModule::UP) && lastActualiseKey != IDisplayModule::UP && lastActualiseKey != IDisplayModule::DOWN) {
        lastKey = IDisplayModule::UP;
        direction = {0, -1};
    }
    if (lib.isKeyPressedOnce(IDisplayModule::DOWN) && lastActualiseKey != IDisplayModule::UP && lastActualiseKey != IDisplayModule::DOWN) {
        lastKey = IDisplayModule::DOWN;
        direction = {0, 1};
    }
}

void nibbler::moveSnake()
{
    lastActualiseKey = lastKey;
    snake.push_front({snake.front().first + direction.first, snake.front().second + direction.second});
}

bool nibbler::isCorrect()
{
    for (auto &&part: snake) {
        if (part.first == fruit.first && part.second == fruit.second) {
            return (false);
        }
    }
    return (true);
}

void nibbler::eatFruit()
{
    if (snake.front().first == fruit.first && snake.front().second == fruit.second) {
        actualScore += 10;
        fruitEaten = true;
        fruit.first = rand() % mapSize.first;
        fruit.second = rand() % mapSize.second;
        while (!isCorrect() && (int) snake.size() != mapSize.first * mapSize.second) {
            fruit.first = rand() % mapSize.first;
            fruit.second = rand() % mapSize.second;
        }
    }
}

void nibbler::endTest()
{
    size_t i = 0;

    if ((int) snake.size() == mapSize.first * mapSize.second) {
        scoreList.push_back(getScore());
        sortScores();
        saveToFile();
        state = WIN;
    }
    for (auto &&part: snake) {
        if (i != 0 && part.first == snake.front().first && part.second == snake.front().second) {
            scoreList.push_back(getScore());
            sortScores();
            saveToFile();
            state = LOSE;
        }
        i++;
    }
    if (snake.front().first < 0 || snake.front().first > mapSize.first || snake.front().second < 0 || snake.front().second > mapSize.second) {
        scoreList.push_back(getScore());
        sortScores();
        saveToFile();
        state = LOSE;
    }
}

void nibbler::removeEndSnake()
{
    if (!fruitEaten)
        snake.pop_back();
    else
        fruitEaten = false;
}

void nibbler::update(const IDisplayModule &lib)
{
    if (state == GAME) {
        updateKey(lib);
        moveTimer -= lib.getDelta();
        if (moveTimer <= 0) {
            moveTimer += moveSpeed;
            moveSnake();
            eatFruit();
            removeEndSnake();
            endTest();
        }
    }
}

void nibbler::renderSnake(IDisplayModule &lib) const
{
    lib.setColor(IDisplayModule::GREEN);
    for (auto &&part: snake) {
        lib.putFillCircle(16 + part.first * 16, 32 + part.second * 16, 8);
    }
}

void nibbler::renderMap(IDisplayModule &lib) const
{
    lib.setColor(IDisplayModule::WHITE);
    lib.putRect(16, 32, 16 * (mapSize.first + 1), 16 * (mapSize.second + 1));
}

void nibbler::renderFruit(IDisplayModule &lib) const
{
    lib.setColor(IDisplayModule::RED);
    lib.putFillCircle(16 + fruit.first * 16, 32 + fruit.second * 16, 8);
}

void nibbler::render(IDisplayModule &lib) const
{
    if (state == GAME) {
        lib.setColor(IDisplayModule::WHITE);
        if (getBestScores().size() == 0)
            lib.putText(std::string("HighScore: 0"), 16, 0, 8);
        else
            lib.putText(std::string("HighScore: ") + std::to_string(getBestScores()[0].second), 16, 0, 8);
        lib.putText(std::string("Score: ") + std::to_string(actualScore), 16, 240, 8);
        renderSnake(lib);
        renderMap(lib);
        renderFruit(lib);
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