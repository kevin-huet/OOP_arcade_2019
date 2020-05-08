    /*
** EPITECH PROJECT, 2020
** a
** File description:
** a
*/

#ifndef SDL_HPP_
#define SDL_HPP_

#include "ArcadeInterfaces.hpp"
#include <SDL2/SDL.h> 
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <string>

const std::vector<SDL_Keycode> keys
{
    SDLK_LEFT,
    SDLK_RIGHT,
    SDLK_UP,
    SDLK_DOWN,
    SDLK_z,
    SDLK_q,
    SDLK_s,
    SDLK_d,
    SDLK_a,
    SDLK_e,
    SDLK_w,
    SDLK_x,
    SDLK_SPACE,
    SDLK_j,
    SDLK_k,
    SDLK_u,
    SDLK_i,
    SDLK_RETURN,
    SDLK_BACKSPACE,
    SDLK_v,
    SDLK_c,
    SDLK_n,
    SDLK_b,
    SDLK_r,
    SDLK_m,
    SDLK_ESCAPE,
};

class sdl : public IDisplayModule
{
    public:
        sdl();
        ~sdl() noexcept;

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
        std::string _playerName;
        IDisplayModule::Colors _color;
        SDL_Window *_window;
        SDL_Renderer *_rend;
        SDL_Event _event;
        std::vector<bool> _held;
        std::vector<bool> _pressed;
        std::vector<bool> _justPressed;
        char _nameChar = '\0';
    protected:
        float doDelta(int flag) const;
        void createVectors();
        void updateKeys();
        void updateKeysPressed(SDL_Keycode key);
        void updateKeysReleased(SDL_Keycode key);
        void updateNameChar();
        SDL_Color convert_color(IDisplayModule::Colors moduleColor) const;
};

#endif /* !SDL_HPP_ */
