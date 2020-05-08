/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** sfml
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ArcadeInterfaces.hpp"

const sf::Keyboard::Key keys[] {
    sf::Keyboard::Key::Left,
    sf::Keyboard::Key::Right,
    sf::Keyboard::Key::Up,
    sf::Keyboard::Key::Down,
    sf::Keyboard::Key::Z,
    sf::Keyboard::Key::Q,
    sf::Keyboard::Key::S,
    sf::Keyboard::Key::D,
    sf::Keyboard::Key::A,
    sf::Keyboard::Key::E,
    sf::Keyboard::Key::W,
    sf::Keyboard::Key::X,
    sf::Keyboard::Key::Space,
    sf::Keyboard::Key::J,
    sf::Keyboard::Key::K,
    sf::Keyboard::Key::U,
    sf::Keyboard::Key::I,
    sf::Keyboard::Key::Enter,
    sf::Keyboard::Key::BackSpace,
};

class sfml : public IDisplayModule
{
    public:
        sfml();
        ~sfml() noexcept;

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
        void putCircle(float x, float y, float rad) const;
        void putFillCircle(float x, float y, float rad) const;
        void putText(const std::string &text, unsigned int size, float x, float y) const;

        const std::string &getLibName() const;

    private:
        std::string _libName;
        sf::RenderWindow *_window = new sf::RenderWindow;
        IDisplayModule::Colors _color;
        sf::Event _event;
        std::vector<bool> _held;
        std::vector<bool> _pressed;
        char _nameChar = '\0';
    protected:
        float doDelta(int flag) const;
        void createVectors();
        void updateKeys();
        void updateNameChar();
        sf::Color convertColor(IDisplayModule::Colors moduleColor) const;
};

#endif
