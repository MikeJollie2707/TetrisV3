#include "tetris.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(270, 315), "Tetris");
    try {
        Tetris tetris(window);
        tetris.setInitSpeed(0.5f)
              .setGrid(15)
              .setOutlineThickness(1);
        
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
    - Music
    */

    return 0;
}
