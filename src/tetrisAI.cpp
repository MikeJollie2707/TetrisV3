#include "tetris.hpp"

TetrisAI::TetrisAI(sf::RenderWindow& window) :
Tetris(window) {

}

int TetrisAI::run() {
    while (window.isOpen()) {
        sf::Time elapsed = render_clock.getElapsedTime();

        if (!movable)
        {
            current = next;
            current->toDefaultPos();

            if (settings.hint) {
                hint = new Tetromino(*current);
                //updateHint();
            }

            // Losing condition
            if (isCollide(current, CollideOptions::Piece)) {
                cleanUpMemory();
                break;
            }

            next = new Tetromino(static_cast<Tetromino::Type>(genRandomTetromino()));
            next->setPos(14, 3);

            current_color = next_color;
            next_color = getTetrominoColor(next);

            movable = true;
        }

        is_hard_drop = false;

        while (elapsed < dt) {
            sf::Event event;
            if (window.pollEvent(event)) {
                // we do some logic here
                processEvent(event);
            }

            elapsed = render_clock.getElapsedTime();    
        }

        if (tick_clock.getElapsedTime().asSeconds() >= tick || is_hard_drop) {
            if (!is_hard_drop) {
                movable = isMovable(current);
                if (movable && !is_pause) {
                    moveDown(current);
                }
            }

            tick_clock.restart();
            is_hard_drop = false;
        }

        this->render();
        render_clock.restart();

        if (!movable) {
            //updateBoard();
            cleanUpMemory();

            if (settings.debug) {
                print();
            }
        }
    }

    return score;
}

void TetrisAI::processEvent(sf::Event event) {
    sf::Event::EventType type = event.type;
    if (type == sf::Event::Closed) {
        window.close();
        movable = false;
    }
    else if (type == sf::Event::KeyPressed) {
        auto key = event.key.code;
        switch (key) {
        case sf::Keyboard::Escape: {
            window.close();
            movable = false;
            break;
        }
        }
    }
    /*
    height = max(height)
    for col in column
        spawn tetris
        while current_height > height and !isCollide()
            moveDown()
        
        while movable
            random(moveLeft, moveRight, rotateLeft, rotateRight)
            moveDown()
        result = find(possible_ends.begin(), possible_ends.end(), [](Tetromino& p) {
            return (hint == p);
        })
        if (!result)
            possible_ends.append(hint)
            find_max(possible_ends) // based on rules
        
        goto while movable
    */
}
void TetrisAI::incScore(int lines) {
    score += 100 * (lines + 1);
}
