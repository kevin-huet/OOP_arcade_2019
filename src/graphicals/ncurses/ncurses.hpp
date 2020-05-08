/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** ncurses
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include "ArcadeInterfaces.hpp"
#include <ncurses.h>
#include <curses.h>
#include <string>
#include <memory>

class ncurses : public IDisplayModule
{
    public:
        ncurses();
        ~ncurses();

        void reset();
        void open();
        void close();
        bool isOpen() const;

        bool switchToNextLib() const;
        bool switchToPreviousLib() const;
        bool switchToNextGame() const;
        bool switchToPreviousGame() const;
        bool shouldBeRestarted() const;
        bool shouldGoToMenu() const;
        bool shouldExit() const;

        bool isKeyPressed(IDisplayModule::Keys) const;
        bool isKeyPressedOnce(IDisplayModule::Keys) const;

        float getDelta() const;

        void clear() const; 
        void update();
        void render() const;

        char getKeyCode() const;

        void setColor(IDisplayModule::Colors col);
        void putPixel(float x, float y) const;
        void putLine(float x1, float y1, float x2, float y2) const;
        void putRect(float x, float y, float w, float h) const;
        void putFillRect(float x, float y, float w, float h) const;
        void putCircle(float x, float y, [[maybe_unused]]float rad) const;
        void putFillCircle(float x, float y, [[maybe_unused]]float rad) const;
        void putText(const std::string &text, [[maybe_unused]]unsigned int size, float x, float y) const;

        const std::string &getLibName() const;

    private:
        void createVectors();
        void updateKeys();
        void updateKeysPressed(int key);
        void updateKeysReleased(int key);
        float doDelta(int flag) const;

    private:
        int ch;
        bool _open = false;
        std::string libname;
        std::string playerName;
        std::vector<bool> _held;
        std::vector<bool> _pressed;
        std::vector<bool> _justPressed;
        bool _colorSelect = false;
        IDisplayModule::Colors _color;
};

#define KEY_ESCAPE 27
#define ABSOLUE(a) (a < 0 ? a * -1 : a)

const std::vector<int> keys
{
    KEY_LEFT,
    KEY_RIGHT,
    KEY_UP,
    KEY_DOWN,
    'z',
    'q',
    's',
    'd',
    'a',
    'e',
    'w',
    'x',
    ' ',
    'j',
    'k',
    'u',
    'i',
    '\n',
    '\b',
    'v',
    'c',
    'n',
    'b',
    'r',
    'm',
    KEY_ESCAPE,
 };

 const std::vector<std::pair<IDisplayModule::Colors, int>> colors
 {
    {IDisplayModule::DEFAULT, COLOR_BLACK},
    {IDisplayModule::BLACK, COLOR_BLACK},
    {IDisplayModule::RED, COLOR_RED},
    {IDisplayModule::GREEN, COLOR_GREEN},
    {IDisplayModule::YELLOW, COLOR_YELLOW},
    {IDisplayModule::BLUE, COLOR_BLUE},
    {IDisplayModule::MAGENTA, COLOR_MAGENTA},
    {IDisplayModule::CYAN, COLOR_CYAN},
    {IDisplayModule::LIGHT_GRAY, COLOR_WHITE},
    {IDisplayModule::DARK_GRAY, COLOR_BLACK},
    {IDisplayModule::LIGHT_RED, COLOR_RED},
    {IDisplayModule::LIGHT_GREEN, COLOR_GREEN},
    {IDisplayModule::LIGHT_YELLOW, COLOR_YELLOW},
    {IDisplayModule::LIGHT_BLUE, COLOR_BLUE},
    {IDisplayModule::LIGHT_MAGENTA, COLOR_MAGENTA},
    {IDisplayModule::LIGHT_CYAN, COLOR_CYAN},
    {IDisplayModule::WHITE, COLOR_WHITE},
 };

#endif /* !NCURSES_HPP_ */
