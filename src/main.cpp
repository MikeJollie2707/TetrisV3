#include "tetris.hpp"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({840, 840}), "Tetris");
    try {
        Tetris tetris(window);
        tetris.setInitSpeed(0.5f)
            .setGrid(30)
            .setOutlineThickness(3);

        tetris.setDebug(false)
            .setHardDrop(true)
            .setHint(true)
            .setHold(true);

        int final_score = tetris.run();
        std::cout << "Final score: " << final_score << '\n';
    }
    catch (std::bad_alloc& ba) {
        std::cerr << "Failed to allocate memory to play." << '\n';
    }

    /*
    TODO:
    - AI
    */

    return 0;
}
