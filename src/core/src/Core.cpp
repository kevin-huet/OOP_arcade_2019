/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Core
*/

#include "Core.hpp"

void Core::menuNameGestion(char key)
{
    if (key == '\b' && _name.size() > 0)
        _name.pop_back();
    else if (key != '\0' && key != '\r' && key != '\n' && key != '\b')
        _name.push_back(key);
}

void Core::menuChangeChoosed()
{
    if (_display[_displayIndex]->isKeyPressedOnce(IDisplayModule::UP)) {
        _gameIndex--;
        if (_gameIndex >= _games.size())
            _gameIndex = _games.size() - 1;
    }
    if (_display[_displayIndex]->isKeyPressedOnce(IDisplayModule::DOWN)) {
        _gameIndex++;
        if (_gameIndex >= _games.size())
            _gameIndex = 0;
    }
}

void Core::menuScene()
{
    size_t i = 0;
    _display[_displayIndex]->setColor(IDisplayModule::Colors::WHITE);
    _display[_displayIndex]->putText("ARCADE", 60, WIDTH / 3, 20);
    _display[_displayIndex]->setColor(IDisplayModule::Colors::RED);
    for (std::unique_ptr<IGameModule> &game: _games) {
        _display[_displayIndex]->putText(game->getLibName(), 16, 40, 120 + (i * 16));
        if (i == _gameIndex) {
            _display[_displayIndex]->putCircle(16, 120 + (i * 16), 8);
            if (game->getBestScores().size() == 0)
                _display[_displayIndex]->putText(std::string("Score: ") + std::string("0"), 15, WIDTH / 3, 100);
            else
                _display[_displayIndex]->putText(std::string("Score: ") + std::to_string(game->getBestScores()[0].second), 15, WIDTH / 3, 100);
        }
        i++;
    }
    i = 1;
    for (std::unique_ptr<IDisplayModule> &lib: _display) {
        _display[_displayIndex]->putText(lib->getLibName(), 16, WIDTH - lib->getLibName().size() * 16, HEIGHT - i * 16);
        i++;
    }
    menuChangeChoosed();
    if (_display[_displayIndex]->getKeyCode() != '\0')
        menuNameGestion(_display[_displayIndex]->getKeyCode());
    _display[_displayIndex]->putText("Name: " + _name, 16, WIDTH / 3, 204);
    if (_name.size() == 0)
        _display[_displayIndex]->putText("You must have a name !", 16, WIDTH / 3, 240);
    if (_display[_displayIndex]->isKeyPressedOnce(IDisplayModule::ENTER) && _name.size() != 0) {
        _gameChoosed = true;
        _games[_gameIndex]->setPlayerName(_name);
    }
}

void Core::allMoveInProgram()
{
    if (_display[_displayIndex]->shouldExit())
        _display[_displayIndex]->close();
    if (_display[_displayIndex]->shouldBeRestarted())
        _games[_gameIndex]->reset();
    if (_display[_displayIndex]->shouldGoToMenu() && _gameChoosed) {
        _games[_gameIndex]->reset();
        _gameChoosed = false;
    }
}

void Core::allSwitchs()
{
    if (_display[_displayIndex]->switchToNextLib()) {
        _display[_displayIndex]->close();
        _displayIndex++;
        if (_displayIndex >= _display.size())
            _displayIndex = 0;
        _display[_displayIndex]->open();
    }
    if (_display[_displayIndex]->switchToPreviousLib()) {
        _display[_displayIndex]->close();
        _displayIndex--;
        if (_displayIndex >= _display.size())
            _displayIndex = _display.size() - 1;
        _display[_displayIndex]->open();
    }
    if (_display[_displayIndex]->switchToNextGame()) {
        _games[_gameIndex]->reset();
        _gameIndex++;
        if (_gameIndex >= _games.size())
            _gameIndex = 0;
        _games[_gameIndex]->setPlayerName(_name);
    }
    if (_display[_displayIndex]->switchToPreviousGame()) {
        _games[_gameIndex]->reset();
        _gameIndex--;
        if (_gameIndex >= _games.size())
            _gameIndex = _games.size() - 1;
        _games[_gameIndex]->setPlayerName(_name);
    }
}

void Core::loop()
{
    _display[_displayIndex]->open();
    while (_display[_displayIndex]->isOpen()) {
        _display[_displayIndex]->update();
        _display[_displayIndex]->clear();
        if (!_gameChoosed)
            menuScene();
        else {
            _games[_gameIndex]->update(*(_display[_displayIndex].get()));
            _games[_gameIndex]->render(*(_display[_displayIndex].get()));
            allSwitchs();
        }
        _display[_displayIndex]->render();
        allMoveInProgram();
    }
}