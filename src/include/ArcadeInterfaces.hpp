/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <iostream>
#include <vector>

#define SAVE_PATH "games/.saves/"
#define WIDTH 640
#define HEIGHT 480

class IDisplayModule {
    public:
        virtual ~IDisplayModule() = default;

        // Limited to the bash color codes in case colors aren't handled by a library
        enum Colors {
            DEFAULT,
            BLACK,
            RED,
            GREEN,
            YELLOW,
            BLUE,
            MAGENTA,
            CYAN,
            LIGHT_GRAY,
            DARK_GRAY,
            LIGHT_RED,
            LIGHT_GREEN,
            LIGHT_YELLOW,
            LIGHT_BLUE,
            LIGHT_MAGENTA,
            LIGHT_CYAN,
            WHITE,
            COLORS_END
        };

        // Keys you have to implement, there are enough keys to have multiple keyboard configurations for every game
        // You only need 6 keys for the core and 6 for the games.
        enum Keys {
            LEFT,
            RIGHT,
            UP,
            DOWN,
            Z,
            Q,
            S,
            D,
            A,
            E,
            W,
            X,
            SPACE,
            J,
            K,
            U,
            I,
            ENTER,
            BACKSPACE,
            KEYS_END
        };

        // For the core
        // Reset the library
        virtual void reset() = 0;
        // Opens / inits the window
        virtual void open() = 0;
        // Closes / destroys the window
        virtual void close() = 0;
        // Check if the window is open
        virtual bool isOpen() const = 0;

        // Handle switching libs & games (the names are explicit)
        // Those are all key presses
        // Those must be different than the keys listed in the Keys enum.
        // The keys enum only lists keys used by games, not special keys to switch libraries.
        virtual bool switchToNextLib() const = 0;
        virtual bool switchToPreviousLib() const = 0;
        virtual bool switchToNextGame() const = 0;
        virtual bool switchToPreviousGame() const = 0;
        // From the pdf
        virtual bool shouldBeRestarted() const = 0;
        virtual bool shouldGoToMenu() const = 0;
        virtual bool shouldExit() const = 0;

        // Handle Inputs & Events
        virtual bool isKeyPressed(IDisplayModule::Keys) const = 0;
        virtual bool isKeyPressedOnce(IDisplayModule::Keys) const = 0;
        // Get the number of frames that passed between two calls to this function
        // The games should not be frame dependant!! That's why this is here.
        virtual float getDelta() const = 0;

        // Handle Loop
        virtual void clear() const = 0;
        virtual void update() = 0;
        virtual void render() const = 0;
        // You don't need all three of them, only one should be enough but we added the three of them
        // in case some of you want to seperate each step
        // Your core (or games) should nonetheless call all of these functions in this specific order :
        // clear -> update -> render

        // Handle Text Input
        // We need to ask for the player's name (check the pdf before complaining and asking about this function)
        // Get key Presses.
        // returns \n if enter was pressed & \0 if nothing was pressed.
        // it returns \b if backspace was pressed (to delete a character from the name).
        virtual char getKeyCode() const = 0;

        // Display Stuff
        // Sets the color for all the following draw functions.
        // everything you display after this will have the selected color
        virtual void setColor(IDisplayModule::Colors col) = 0;
        // Display a pixel
        virtual void putPixel(float x, float y) const = 0;
        // Display a line
        virtual void putLine(float x1, float y1, float x2, float y2) const = 0;
        // Display an empty rectangle
        virtual void putRect(float x, float y, float w, float h) const = 0;
        // Display a full rectangle
        virtual void putFillRect(float x, float y, float w, float h) const = 0;
        // Display an empty circle
        virtual void putCircle(float x, float y, float rad) const = 0;
        // Display a full circle
        virtual void putFillCircle(float x, float y, float rad) const = 0;
        // Display some text
        virtual void putText(const std::string &text, unsigned int size, float x, float y) const = 0;

        // We chose not to display images because some library can't and it would cause other problems
        // You can still parse a file and display pixel art images by displaying pixels manually if you want.

        virtual const std::string &getLibName() const = 0;
};

class IGameModule {
    public:
        virtual ~IGameModule() = default;

        // For the core

        // Reset game at any moment
        virtual void reset() = 0;

        // Load highscores from file and return wether it worked or not
        virtual bool loadFromFile(const std::string &filepath) = 0; // with filename
        virtual bool loadFromFile() = 0; // default filename

        // save highscores to file return wether it worked or not
        virtual bool saveToFile(const std::string &filepath) const = 0; // with filename
        virtual bool saveToFile() const = 0; // default filename
    
        // Highscores are stored as such :
        // "name:value\n
        // name2:value2\nEOF"

        // Set the player's name for the highscore
        virtual void setPlayerName(const std::string &name) = 0;
        // get the current score
        virtual std::pair<std::string, int> getScore() const = 0;
        // get the 16 best scores
        virtual std::vector<std::pair<std::string, int>> getBestScores() const = 0;

        // Handle Game
        // update game
        virtual void update(const IDisplayModule &lib) = 0;
        // display stuff using the lib given as an argument.
        virtual void render(IDisplayModule &lib) const = 0;
        virtual const std::string &getLibName() const = 0;
};

// Good luck and have fun.
// If you have a problem with the interface or a question send me a message :
// discord         : Zikoure#0963
// microsoft teams : ghassane.sebai@epitech.eu

#endif /* !ARCADE_INTERFACES_HPP_ */