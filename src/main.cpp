#include "tetris.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(840, 840), "Tetris");
    try {
        Tetris tetris(window);
        tetris.setInitSpeed(0.3f)
              .setGrid(40)
              .setOutlineThickness(4);
        
        tetris.setDebug(false)
              .setHardDrop(true)
              .setHint(false)
              .setHold(false);

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
