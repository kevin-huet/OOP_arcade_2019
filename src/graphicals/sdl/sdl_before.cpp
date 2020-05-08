/*
** EPITECH PROJECT, 2020
** a
** File description:
** a
*/

#include "sdl.hpp"
#include <math.h>
#include <memory>

extern "C" std::unique_ptr<IDisplayModule> createLib(void)
{
    return std::make_unique<sdl>();
}

sdl::sdl() : IDisplayModule()
{
    TTF_Init();
    this->_libName = "SDL2";
}

sdl::~sdl()
{

}

void sdl::close()
{
    SDL_DestroyWindow(this->_window);
    SDL_DestroyRenderer(this->_rend);
    TTF_Quit();
}

void sdl::open()
{
    this->_window = SDL_CreateWindow("Arcade",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 
        WIDTH, HEIGHT, 0);
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    this->_rend = SDL_CreateRenderer(this->_window, -1, render_flags); 
}

bool sdl::isOpen() const
{
    if (this->_window)
        return true;
    return false;
}

bool sdl::switchToNextLib() const
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

bool sdl::switchToPreviousLib() const
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

bool sdl::switchToNextGame() const
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

bool sdl::switchToPreviousGame() const
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

bool sdl::shouldBeRestarted() const
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

bool sdl::shouldGoToMenu() const
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

bool sdl::shouldExit() const
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

float sdl::getDelta() const
{
}

void sdl::reset()
{

}

bool sdl::isKeyPressed(IDisplayModule::Keys key) const
{
    if (_event.type == keys[(int)(key)])
        return true;
    return false;
}

bool sdl::isKeyPressedOnce(IDisplayModule::Keys key) const
{
    if (_event.type == keys[(int)(key)])
        return true;
    return false;
}

void sdl::clear() const
{
    SDL_RenderClear(this->_rend);
}

void sdl::update()
{
    SDL_RenderClear(this->_rend);
}

char sdl::getKeyCode() const
{

}

SDL_Color sdl::convert_color(IDisplayModule::Colors moduleColor) const
{
    SDL_Color color = {255, 255, 255, 255};
    
    switch (moduleColor) {
    case WHITE:
        break;
    case RED: color = {204, 0, 0, 255};
        break;
    case BLUE: color = {0, 102, 204, 255};
        break;
    case CYAN: color = {0, 255, 255, 255};
        break;
    case BLACK: color = {0, 0, 0, 255};
        break;
    case MAGENTA: color = {255, 0, 255, 255};
        break;
    case YELLOW: color = {255, 255, 0, 255};
        break;
    case GREEN: color = {0, 204, 0, 255};
        break;
    default:
        break;
    }
    return (color);
}

void sdl::render() const
{
    SDL_RenderPresent(this->_rend);
}

void sdl::setColor(IDisplayModule::Colors col)
{
    SDL_Color color = this->convert_color(col);
    SDL_SetRenderDrawColor(this->_rend, color.r, color.g, color.b, color.a);

}

void sdl::putPixel(float x, float y) const
{
    SDL_RenderDrawPoint(this->_rend, x, y);
}

void sdl::putLine(float x1, float y1, float x2, float y2) const
{
    SDL_RenderDrawLine(this->_rend, x1, y1, x2, y2);
}

void sdl::putRect(float x, float y, float w, float h) const
{
    SDL_FRect rect = {x, y, w, h};
    SDL_RenderDrawRectF(this->_rend, &rect);
}

void sdl::putFillRect(float x, float y, float w, float h) const
{
    SDL_FRect rect = {x, y, w, h};
    SDL_RenderFillRectF(this->_rend, &rect);
}

void sdl::putCircle(float x, float y, float rad) const
{
    int new_x = 0;
    int new_y = 0;
    int old_x =  x + rad;
    int old_y = y + rad;
    float step = (M_PI * 2) / 50; 

    for (float theta = 0; theta <= (M_PI * 2); theta += step)
    {
        new_x = x + (rad * cos ( theta ));
        new_y = y - (rad * sin ( theta ));   

        SDL_RenderDrawLine (this->_rend, old_x, old_y, new_x, new_y );

        old_x = new_x;
        old_y = new_y;
    }
    new_x =  x + (rad * cos(0));
    new_y =  y - (rad * sin(0));  
    SDL_RenderDrawLine(this->_rend, old_x, old_y, new_x, new_y);
}

void sdl::putFillCircle(float x, float y, float rad) const
{

}

void sdl::putText(const std::string &text, unsigned int size, float x, float y) const
{
    TTF_Font *font = TTF_OpenFont("./assets/arial.ttf", size);
    SDL_Color color = convert_color(this->_color);
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->_rend, surface);
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    pos.h = 0;
    pos.w = 0;
    SDL_RenderCopy(this->_rend, texture, NULL, &pos);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}

const std::string &sdl::getLibName() const
{
    return this->_libName;
}