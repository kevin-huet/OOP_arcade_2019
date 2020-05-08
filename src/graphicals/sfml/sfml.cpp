/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** sfml
*/

#include "sfml.hpp"
#include "LibsErrors.hpp"

extern "C" std::unique_ptr<IDisplayModule> createLib(void)
{
    return std::make_unique<sfml>();
}



sfml::sfml() : IDisplayModule()
{
    this->_libName = "SFML";
    this->_color = DEFAULT;
    createVectors();
}

sfml::~sfml()
{
    if (this->isOpen())
        this->close();
}

void sfml::createVectors()
{
    for (int i = 0; i < (int)IDisplayModule::Keys::KEYS_END; i++) {
        _pressed.push_back(false);
        _held.push_back(false);
    }
}



void sfml::reset()
{
    close();
    open();
}

void sfml::open()
{
    this->_window->create(sf::VideoMode(WIDTH, HEIGHT), "ARCADE");
    this->_window->setFramerateLimit(60);
    doDelta(2);
}

void sfml::close()
{
    this->_window->close();
}

bool sfml::isOpen() const
{
    return (this->_window->isOpen());
}



bool sfml::switchToNextLib() const
{
    static bool press = false;
    static bool held = false;
    sf::Keyboard::Key key = sf::Keyboard::V;

    if (sf::Keyboard::isKeyPressed(key) && !held) {
        press = true;
        held = true;
    }
    else
        press = false;
    if (!sf::Keyboard::isKeyPressed(key)) {
        press = false;
        held = false;
    }
    return (press);
}

bool sfml::switchToPreviousLib() const
{
    static bool press = false;
    static bool held = false;
    sf::Keyboard::Key key = sf::Keyboard::C;

    if (sf::Keyboard::isKeyPressed(key) && !held) {
        press = true;
        held = true;
    }
    else
        press = false;
    if (!sf::Keyboard::isKeyPressed(key)) {
        press = false;
        held = false;
    }
    return (press);
}

bool sfml::switchToNextGame() const
{
    static bool press = false;
    static bool held = false;
    sf::Keyboard::Key key = sf::Keyboard::N;

    if (sf::Keyboard::isKeyPressed(key) && !held) {
        press = true;
        held = true;
    }
    else
        press = false;
    if (!sf::Keyboard::isKeyPressed(key)) {
        press = false;
        held = false;
    }
    return (press);
}

bool sfml::switchToPreviousGame() const
{
    static bool press = false;
    static bool held = false;
    sf::Keyboard::Key key = sf::Keyboard::B;

    if (sf::Keyboard::isKeyPressed(key) && !held) {
        press = true;
        held = true;
    }
    else
        press = false;
    if (!sf::Keyboard::isKeyPressed(key)) {
        press = false;
        held = false;
    }
    return (press);
}

bool sfml::shouldBeRestarted() const
{
    static bool press = false;
    static bool held = false;
    sf::Keyboard::Key key = sf::Keyboard::R;

    if (sf::Keyboard::isKeyPressed(key) && !held) {
        press = true;
        held = true;
    }
    else
        press = false;
    if (!sf::Keyboard::isKeyPressed(key)) {
        press = false;
        held = false;
    }
    return (press);
}

bool sfml::shouldGoToMenu() const
{
    static bool press = false;
    static bool held = false;
    sf::Keyboard::Key key = sf::Keyboard::M;

    if (sf::Keyboard::isKeyPressed(key) && !held) {
        press = true;
        held = true;
    }
    else
        press = false;
    if (!sf::Keyboard::isKeyPressed(key)) {
        press = false;
        held = false;
    }
    return (press);
}

bool sfml::shouldExit() const
{
    static bool press = false;
    static bool held = false;
    sf::Keyboard::Key key = sf::Keyboard::Escape;

    if (sf::Keyboard::isKeyPressed(key) && !held) {
        press = true;
        held = true;
    }
    else
        press = false;
    if (!sf::Keyboard::isKeyPressed(key)) {
        press = false;
        held = false;
    }
    return (press);
}



void sfml::updateKeys()
{
    for (int i = 0; i < (int)IDisplayModule::Keys::KEYS_END; i++) {
        if (sf::Keyboard::isKeyPressed(keys[i]) && !_held[i]) {
            _pressed[i] = true;
            _held[i] = true;
        }
        else
            _pressed[i] = false;
        if (!sf::Keyboard::isKeyPressed(keys[i])) {
            _pressed[i] = false;
            _held[i] = false;
        }
    }
}

bool sfml::isKeyPressedOnce(IDisplayModule::Keys key) const
{
    return (_pressed[key]);
}

bool sfml::isKeyPressed(IDisplayModule::Keys key) const
{
    return (_held[key]);
}



float sfml::doDelta(int flag) const
{
    static sf::Time old;
    static float frames = 0;
    sf::Time current;
    static sf::Clock clock;

    if (flag == 1) {
        current = clock.getElapsedTime();
        frames = current.asMicroseconds() - old.asMicroseconds();
        frames /= 100000 / 60;
        old += sf::microseconds(frames * 100000 / 60);
    }
    if (flag == 2)
        old = clock.getElapsedTime();
    return (frames);
}

float sfml::getDelta() const
{
    return (doDelta(0));
}



void sfml::clear() const
{
    this->_window->clear();
}

void sfml::update()
{
    doDelta(1);
    _nameChar = '\0';
    while (_window->pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            this->close();
        if (_event.type == sf::Event::TextEntered)
            updateNameChar();
    }
    updateKeys();
}

void sfml::render() const
{
    this->_window->display();
}



char sfml::getKeyCode() const
{
    return (_nameChar);
}

void sfml::updateNameChar()
{
    if ((char) _event.text.unicode != '\0')
        _nameChar = (char) _event.text.unicode;
    else 
        _nameChar = '\0';
}



void sfml::setColor(IDisplayModule::Colors col)
{
    this->_color = col;
}

sf::Color sfml::convertColor(IDisplayModule::Colors moduleColor) const
{
    sf::Color color = sf::Color::White;
    switch (moduleColor) {
    case WHITE:
        break;
    case RED: color = sf::Color::Red;
        break;
    case BLUE: color = sf::Color::Blue;
        break;
    case CYAN: color = sf::Color::Cyan;
        break;
    case BLACK: color = sf::Color::Black;
        break;
    case MAGENTA: color = sf::Color::Magenta;
        break;
    case YELLOW: color = sf::Color::Yellow;
        break;
    case GREEN: color = sf::Color::Green;
        break;
    default:
        break;
    }
    return (color);
}

void sfml::putPixel(float x, float y) const
{
    sf::RectangleShape rect(sf::Vector2f(1, 1));
    rect.setFillColor(sf::Color(convertColor(this->_color)));
    rect.setPosition(sf::Vector2f(x, y));
    this->_window->draw(rect);
}

void sfml::putLine(float x1, float y1, float x2, float y2) const
{
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(x1, y1)),
        sf::Vertex(sf::Vector2f(x2, y2))
    };

    line[0].color = convertColor(this->_color);
    line[1].color = convertColor(this->_color);
    this->_window->draw(line, 2, sf::Lines);
}

void sfml::putRect(float x, float y, float w, float h) const
{
    sf::RectangleShape shape(sf::Vector2f(w, h));
    shape.setPosition(sf::Vector2f(x, y));
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color(convertColor(this->_color)));
    this->_window->draw(shape);
}

void sfml::putFillRect(float x, float y, float w, float h) const
{
    sf::RectangleShape shape(sf::Vector2f(w, h));
    shape.setPosition(sf::Vector2f(x, y));
    shape.setFillColor(convertColor(this->_color));
    this->_window->draw(shape);
}

void sfml::putCircle(float x, float y, float rad) const
{
    sf::CircleShape circle(rad);
    circle.setPosition(sf::Vector2f(x, y));
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(1);
    circle.setOutlineColor(sf::Color(convertColor(this->_color)));
    this->_window->draw(circle);
}

void sfml::putFillCircle(float x, float y, float rad) const
{
    sf::CircleShape circle(rad);
    circle.setPosition(sf::Vector2f(x, y));
    circle.setFillColor(sf::Color(convertColor(this->_color)));
    this->_window->draw(circle);
}

void sfml::putText(const std::string &text, unsigned int size, float x, float y) const
{
    sf::Text txt;
    sf::Font font;

    if (!font.loadFromFile("./assets/arial.ttf"))
        throw (NeedAsset("./assets/arial.ttf needed"));
    txt.setFont(font);
    txt.setString(text);
    txt.setCharacterSize(size);
    txt.setPosition(sf::Vector2f(x, y));
    txt.setFillColor(sf::Color(convertColor(this->_color)));
    this->_window->draw(txt);
}



const std::string &sfml::getLibName() const
{
    return this->_libName;
}   
