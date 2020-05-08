/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** ncurses
*/

#include "ncurses.hpp"

extern "C" std::unique_ptr<IDisplayModule> createLib(void)
{
    return std::make_unique<ncurses>();
}



ncurses::ncurses()
{
    this->libname = "ncurses";
    createVectors();
}

ncurses::~ncurses()
{
    if (this->isOpen())
        this->close();
}

void ncurses::createVectors()
{
    for (size_t i = 0; i < keys.size(); i++) {
        _pressed.push_back(false);
        _justPressed.push_back(false);
        _held.push_back(false);
    }
}



void ncurses::reset()
{
    close();
    open();
}

void ncurses::open()
{
    size_t i = 0;
    initscr();
    endwin();
    initscr();
    start_color();
    for (auto &&col: colors) {
        if (col.second != COLOR_BLACK)
            init_pair(i, col.second, COLOR_BLACK);
        else
            init_pair(i, col.second, COLOR_WHITE);
        i++;
    }
    _open = true;
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    doDelta(2);
    curs_set(0);
}

void ncurses::close()
{
    endwin();
    curs_set(1);
    _open = false;
}

bool ncurses::isOpen() const
{
    return (_open);
}



bool ncurses::switchToNextLib() const
{
    const int key = 'v';

    for (size_t i = 0; i < keys.size(); i++) {
        if (keys[i] == key)
            return (_pressed[i]);
    }
    return (false);
}

bool ncurses::switchToPreviousLib() const
{
    const int key = 'c';

    for (size_t i = 0; i < keys.size(); i++) {
        if (keys[i] == key)
            return (_pressed[i]);
    }
    return (false);
}

bool ncurses::switchToNextGame() const
{
    const int key = 'n';

    for (size_t i = 0; i < keys.size(); i++) {
        if (keys[i] == key)
            return (_pressed[i]);
    }
    return (false);
}

bool ncurses::switchToPreviousGame() const
{
    const int key = 'b';

    for (size_t i = 0; i < keys.size(); i++) {
        if (keys[i] == key)
            return (_pressed[i]);
    }
    return (false);
}

bool ncurses::shouldBeRestarted() const
{
    const int key = 'r';

    for (size_t i = 0; i < keys.size(); i++) {
        if (keys[i] == key)
            return (_pressed[i]);
    }
    return (false);
}

bool ncurses::shouldGoToMenu() const
{
    const int key = 'm';

    for (size_t i = 0; i < keys.size(); i++) {
        if (keys[i] == key)
            return (_pressed[i]);
    }
    return (false);
}

bool ncurses::shouldExit() const
{
    const int key = KEY_ESCAPE;

    for (size_t i = 0; i < keys.size(); i++) {
        if (keys[i] == key)
            return (_pressed[i]);
    }
    return (false);
}



void ncurses::updateKeys()
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

void ncurses::updateKeysPressed(int key)
{
    for (size_t i = 0; i < keys.size(); i++) {
        if (keys[i] == key)
            _justPressed[i] = true;
    }
}

void ncurses::updateKeysReleased(int key)
{
    for (size_t i = 0; i < keys.size(); i++) {
        if (keys[i] == key) {
            _held[i] = false;
            _pressed[i] = false;
        }
    }
}

bool ncurses::isKeyPressedOnce(IDisplayModule::Keys key) const
{
    return (_pressed[key]);
}

bool ncurses::isKeyPressed(IDisplayModule::Keys key) const
{
    return (_held[key]);
}



float ncurses::doDelta(int flag) const
{
    static size_t lastTime = 0;
    size_t currentTime;
    static float frames = 0;

    if (flag == 1) {
        currentTime = clock();
        frames = currentTime - lastTime;
        frames /= 100000 / 60;
        lastTime = currentTime;
    }
    if (flag == 2)
        lastTime = clock();
    return (frames);
}

float ncurses::getDelta() const
{
    return (doDelta(0));
}



void ncurses::clear() const
{
    wclear(stdscr);
}

void ncurses::update()
{
    int chtmp = '\0';
    int chtmp2;

    doDelta(1);
    for (auto &&key: keys)
        updateKeysReleased(key);
    while (1) {
        if ((chtmp2 = getch()) != ERR) {
            updateKeysPressed(chtmp2);
            chtmp = chtmp2;
        }
        else
            break;
    }
    updateKeys();
    ch = chtmp;
}

void ncurses::render() const
{
    if (LINES < HEIGHT / 16 || COLS < WIDTH / 8)
        mvwprintw(stdscr, 0, 0, "Too small !");
    wrefresh(stdscr);
}



char ncurses::getKeyCode() const
{
    if (ch != ERR) {
        if (ch == KEY_BACKSPACE)
            return ('\b');
        if (ch == KEY_ENTER)
            return ('\n');
        if (std::isgraph(ch))
            return (ch);
    }
    return ('\0');
}



void ncurses::setColor(IDisplayModule::Colors col)
{
    size_t i = 0;
    if (_colorSelect) {
        for (auto &&color: colors) {
            if (color.first == col) {
                attroff(COLOR_PAIR(i));
                _colorSelect = true;
                _color = color.first;
            }
        i++;
        }
    }
    i = 0;
    for (auto &&color: colors) {
        if (color.first == col) {
            attron(COLOR_PAIR(i));
            _colorSelect = true;
            _color = color.first;
        }
        i++;
    }
}

void ncurses::putPixel(float x, float y) const
{
    x /= 8;
    y /= 16;
    mvwprintw(stdscr, y, x, "*");
}

void ncurses::putLine(float x1, float y1, float x2, float y2) const
{
    x1 /= 8;
    y1 /= 16;
    x2 /= 8;
    y2 /= 16;
    
    if (x1 == x2 && y1 == y2) {
        mvwprintw(stdscr, y1, x1, "*");
        return;
    }
    mvwprintw(stdscr, y1, x1, "*");
    for (float x = x1, y = y1; x != x2 && y != y2;) {
        if (x < x2 && ABSOLUE(x - x2) > ABSOLUE(y - y2))
            x++;
        else if (x > x2 && ABSOLUE(x - x2) > ABSOLUE(y - y2))
            x--;
        else if (y < y2)
            y++;
        else
            y--;
        mvwprintw(stdscr, y, x, "*");
    }
}

void ncurses::putRect(float x, float y, float w, float h) const
{
    w /= 8;
    h /= 16;
    x /= 8;
    y /= 16;

    h++;
    for (float i = x; i < x + w; i++) {
        mvwprintw(stdscr, y, i, "-");
        mvwprintw(stdscr, y + h, i, "-");
    }
    for (float i = y + 1; i < y + h; i++) {
        mvwprintw(stdscr, i, x, "|");
        mvwprintw(stdscr, i, x + w, "|");
    }
}

void ncurses::putFillRect(float x, float y, float w, float h) const
{
    w /= 8;
    h /= 16;
    x /= 8;
    y /= 16;

    h--;
    for (float i = x; i < x + w; i++) {
        mvwprintw(stdscr, y, i, "-");
        mvwprintw(stdscr, y + h, i, "-");
    }
    for (float i = y + 1; i < y + h; i++) {
        mvwprintw(stdscr, i, x, "|");
        mvwprintw(stdscr, i, x + w, "|");
    }
}

void ncurses::putCircle(float x, float y, [[maybe_unused]]float rad) const
{
    std::string tmp = "";

    x /= 8;
    y /= 16;
    mvwprintw(stdscr, y, x, "o");
}

void ncurses::putFillCircle(float x, float y, [[maybe_unused]]float rad) const
{
    std::string tmp = "";

    x /= 8;
    y /= 16;
    mvwprintw(stdscr, y, x, "o");
}

void ncurses::putText(const std::string &text, [[maybe_unused]]unsigned int size, float x, float y) const
{
    x /= 8;
    y /= 16;
    mvwaddstr(stdscr, y, x, text.data());
}



const std::string &ncurses::getLibName() const
{
    return this->libname;
}