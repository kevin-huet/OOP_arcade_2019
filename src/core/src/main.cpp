/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** main
*/

#include <iostream>
#include "DLLoader.hpp"
#include "ArcadeInterfaces.hpp"
#include "Core.hpp"
#include "CoreErrors.hpp"
#include "LibsErrors.hpp"

int main(int ac, char **av)
{
    try {
        if (ac != 2)
            throw (BadArguments("./arcade FirstLib"));
        Core core(av[1]);
        core.loop();
        return (0);
    } catch (const CoreError e) {
        std::cerr << e.what() << std::endl;
        std::cerr << e.type() << std::endl;
        return (84);
    } catch (const LibsError e) {
        std::cerr << e.what() << std::endl;
        std::cerr << e.type() << std::endl;
        return (84);
    } catch (const std::exception e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }
}
