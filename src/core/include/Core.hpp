/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Core
*/

#ifndef GAME_CORE_HPP_
#define GAME_CORE_HPP_

#include <vector>
#include <memory>
#include "DLLoader.hpp"
#include "ArcadeInterfaces.hpp"

class Core {
    public:
        Core(char *libName)
        {
            _display = DLLoader<IDisplayModule>::getAllLibs("./lib", libName);
            _games = DLLoader<IGameModule>::getAllLibs("./games", nullptr);
        }
        ~Core()
        {
        }

        void loop();

    private:
        void menuScene();
        void menuNameGestion(char key);
        void menuChangeChoosed();
        void allSwitchs();
        void allMoveInProgram(); 

    private:
        std::vector<std::unique_ptr<IDisplayModule>> _display;
        std::vector<std::unique_ptr<IGameModule>> _games;
        size_t _displayIndex = 0;
        size_t _gameIndex = 0;
        std::string _name = "";
        bool _gameChoosed = false;
};

#endif /* !CORE_HPP_ */
