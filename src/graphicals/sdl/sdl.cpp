/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** sdl
*/

#include <math.h>
#include <memory>
#include "sdl.hpp"
#include "LibsErrors.hpp"

extern "C" std::unique_ptr<IDisplayModule> createLib(void)
{
    return std::make_unique<sdl>();
}



sdl::sdl() : IDisplayModule()
{
    this->_libName = "SDL2";
    this->_window = nullptr;
    createVectors();
}

sdl::~sdl()
{
}

void sdl::createVectors()
{
    for (size_t i = 0; i < keys.size(); i++) {
        _pressed.push_back(false);
        _justPressed.push_back(false);
        _held.push_back(false);
    }
}



void sdl::reset()
{
    close();
    open();
}

void sdl::open()
{
    this->_window = SDL_CreateWindow("Arcade",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT, 0);
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    this->_rend = SDL_CreateRenderer(this->_window, -1, render_flags); 
    SDL_StartTextInput();
    TTF_Init();
    doDelta(2);
}

void sdl::close()
{
    if (this->_rend)
        SDL_DestroyRenderer(this->_rend);
    if (this->_window)
        SDL_DestroyWindow(this->_window);
    SDL_StopTextInput();
    this->_window = nullptr;
    TTF_Quit();
}

bool sdl::isOpen() const
{
    if (this->_window)
        return true;
    return false;
}



bool sdl::switchToNextLib() const
{
    const SDL_Keycode key = SDLK_v;

    for (size_t i = 0; i < keys.size(); i++) {
        if (keys[i] == key)
            return (_pressed[i]);
    }
    return (false);
}

bool sdl::switchToPreviousLib() const
{
    const SDL_Keycode key = SDLK_c;

    for (size_t i = 0; i < keys.size(); i++) {
        if (keys[i] == key)
            return (_pressed[i]);
    }
    return (false);
}

bool sdl::switchToNextGame() const
{
    const SDL_Keycode key = SDLK_n;

    for (size_t i = 0; i < keys.size(); i++) {
        if (keys[i] == key)
            return (_pressed[i]);
    }
    return (false);
}

bool sdl::switchToPreviousGame() const
{
    const SDL_Keycode key = SDLK_b;

    for (size_t i = 0; i < keys.size(); i++) {
        if (keys[i] == key)
            return (_pressed[i]);
    }
    return (false);
}

bool sdl::shouldBeRestarted() const
{
    const SDL_Keycode key = SDLK_r;

    for (size_t i = 0; i < keys.size(); i++) {
        if (keys[i] == key)
            return (_pressed[i]);
    }
    return (false);
}

bool sdl::shouldGoToMenu() const
{
    const SDL_Keycode key = SDLK_m;

    for (size_t i = 0; i < keys.size(); i++) {
        if (keys[i] == key)
            return (_pressed[i]);
    }
    return (false);
}

bool sdl::shouldExit() const
{
    const SDL_Keycode key = SDLK_ESCAPE;

    for (size_t i = 0; i < keys.size(); i++) {
        if (keys[i] == key)
            return (_pressed[i]);
    }
    return (false);
}



void sdl::updateKeys()
{
    for (size_t i = 0; i < keys.size(); i++) {
        if (_justPressed[i] && !_held[i]) {
            _pressed[i] = true;
            _held[i] = true;
        }
        else
            _pressed[i] = false;
        _justPressed[i] = false;
    }
}

void sdl::updateKeysPressed(SDL_Keycode key)
{
    for (size_t i = 0; i < keys.size(); i++) {
        if (keys[i] == key)
            _justPressed[i] = true;
    }
}

void sdl::updateKeysReleased(SDL_Keycode key)
{
    for (size_t i = 0; i < keys.size(); i++) {
        if (keys[i] == key) {
            _held[i] = false;
            _pressed[i] = false;
        }
    }
}

bool sdl::isKeyPressedOnce(IDisplayModule::Keys key) const
{
    return (_pressed[key]);
}

bool sdl::isKeyPressed(IDisplayModule::Keys key) const
{
    return (_held[key]);
}



float sdl::doDelta(int flag) const
{
    static size_t lastTime = 0;
    size_t currentTime;
    static float frames = 0;

    if (flag == 1) {
        currentTime = SDL_GetTicks();
        frames = currentTime * 1000 - lastTime * 1000;
        frames /= 100000 / 60;
        lastTime = currentTime;
    }
    if (flag == 2)
        lastTime = SDL_GetTicks();
    return (frames);
}

float sdl::getDelta() const
{
    return (doDelta(0));
}



void sdl::clear() const
{
    SDL_RenderClear(this->_rend);
}

void sdl::update()
{
    doDelta(1);
    _nameChar = '\0';
    while (SDL_PollEvent(&(_event))) {
        if (_event.type == SDL_QUIT)
            this->close();
        if (_event.type == SDL_TEXTINPUT)
            updateNameChar();
        if (_event.type == SDL_KEYDOWN)
            updateKeysPressed(_event.key.keysym.sym);
        if (_event.type == SDL_KEYUP)
            updateKeysReleased(_event.key.keysym.sym);
    }
    updateKeys();
}

void sdl::render() const
{
    SDL_SetRenderDrawColor(this->_rend, 0, 0, 0, 0);
    SDL_RenderPresent(this->_rend);
}



char sdl::getKeyCode() const
{
    for (size_t i = 0; i < keys.size(); i++)
        if (keys[i] == SDLK_BACKSPACE && _held[i] == true)
            return ('\b');
    return (_nameChar);
}

void sdl::updateNameChar()
{
    _nameChar = _event.text.text[0];
}



void sdl::setColor(IDisplayModule::Colors col)
{
    SDL_Color color = this->convert_color(col);
    _color = col;
    SDL_SetRenderDrawColor(this->_rend, color.r, color.g, color.b, color.a);
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
    SDL_Rect rect = {(int) x, (int) y, (int) w, (int) h};
    SDL_RenderDrawRect(this->_rend, &rect);
}

void sdl::putFillRect(float x, float y, float w, float h) const
{
    SDL_FRect rect = {x, y, w, h};
    SDL_RenderFillRectF(this->_rend, &rect);
}

void sdl::putCircle(float x, float y, float rad) const
{
    const int diameter = (rad * 2);
    int xCircle = (rad - 1);
    int yCircle = 0;
    int xCenter = x + rad;
    int yCenter = y + rad;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

    while (xCircle >= yCircle) {
        SDL_RenderDrawPoint(_rend, xCenter + xCircle, yCenter - yCircle);
        SDL_RenderDrawPoint(_rend, xCenter + xCircle, yCenter + yCircle);
        SDL_RenderDrawPoint(_rend, xCenter - xCircle, yCenter - yCircle);
        SDL_RenderDrawPoint(_rend, xCenter - xCircle, yCenter + yCircle);
        SDL_RenderDrawPoint(_rend, xCenter + yCircle, yCenter - xCircle);
        SDL_RenderDrawPoint(_rend, xCenter + yCircle, yCenter + xCircle);
        SDL_RenderDrawPoint(_rend, xCenter - yCircle, yCenter - xCircle);
        SDL_RenderDrawPoint(_rend, xCenter - yCircle, yCenter + xCircle);

        if (error <= 0) {
            yCircle++;
            error += ty;
            ty += 2;
        }

        if (error > 0) {
            xCircle--;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void sdl::putFillCircle(float x0, float y0, float rad) const
{
    std::pair<int, int> center = {x0 + rad, y0 + rad};
    int height;
    int px;
    int py;

    for (int x = -rad; x < rad; x++) {
        height = sqrt(rad * rad - x * x);
        for (int y = -height; y < height; y++) {
            px = x + center.first;
            py = y + center.second;
            if (px < 0)
                px = 0;
            if (py < 0)
                py = 0;
            putPixel(px % 1920, py % 1080);
        }
    }
}

void sdl::putText(const std::string &text, unsigned int size, float x, float y) const
{
    TTF_Font *font = TTF_OpenFont("./assets/arial.ttf", size);
    if (!font)
        throw (NeedAsset("./assets/arial.ttf needed"));
    SDL_Color color = convert_color(this->_color);
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.data(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->_rend, surface);
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    pos.h = surface->h;
    pos.w = surface->w;
    SDL_RenderCopy(this->_rend, texture, NULL, &pos);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}



const std::string &sdl::getLibName() const
{
    return this->_libName;
}   
