#include "tetris.hpp"
#include "tetrisAI.hpp"
#include <SFML/Graphics.hpp>

void render(Tetromino tet);

int main()
{
    sf::RenderWindow window(sf::VideoMode(840, 840), "Tetris");
    try {
        Tetris tetris(window);
        tetris.run();
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
