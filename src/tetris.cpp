#ifndef TETRISV3_TETRIS_CPP
#define TETRISV3_TETRIS_CPP

#include "tetris.hpp"

Tetris::Tetris(sf::RenderWindow& window) :
window(window),
grid(40),
grid_offset(2),
outline(grid_offset / 2),
movable(false),
is_pause(true),
tick(0.5f)
{
    srand(time(NULL));

    // Init board
    for (auto& i : board)
        for (auto& j : i) {
            j.value = 0;
            j.color = sf::Color::Transparent;
        }

    // Init walls
    for (int j = 0; j < board[0].size(); ++j) {
        board[0][j].value = -1;
        board[0][j].color = sf::Color::White;
        board[size_x + 1][j].value = -1;
        board[size_x + 1][j].color = sf::Color::White;
    }
    for (int i = 0; i < board.size(); ++i) {
        board[i][size_y + space_y].value = -1;
        board[i][size_y + space_y].color = sf::Color::White;
    }

    // current
    tetrominoes.emplace_back();
    // hint
    tetrominoes.emplace_back();
    // next
    tetrominoes.emplace_back(static_cast<Tetromino::Type>(genRandomTetromino()));
    next_color = getTetrominoColor(tetrominoes[2]);
}
Tetris::~Tetris()
{
}

int Tetris::genRandomTetromino() {
    // We use NES Tetris random algorithm here.
    // Basically roll an 8-sided dice, 1-7 being the 7 pieces,
    // and 8 means reroll.
    // If the first roll has the same number as previous piece OR 8,
    // it'll do a reroll. The reroll is final.

    int value = rand() % 8;
    if (static_cast<int>(tetrominoes[0].getType()) == value || value == 7) {
        value = rand() % 7;
    }

    return value;
}
sf::Color Tetris::getTetrominoColor(Tetromino const& tetromino) {
    switch (tetromino.getType()) {
    case Tetromino::Type::I: {
        return sf::Color::Cyan;
    }
    case Tetromino::Type::J: {
        return sf::Color::Blue;
    }
    case Tetromino::Type::L: {
        return sf::Color(255, 189, 51);
    }
    case Tetromino::Type::N: {
        return sf::Color::Red;
    }
    case Tetromino::Type::O: {
        return sf::Color::Yellow;
    }
    case Tetromino::Type::S: {
        return sf::Color::Green;
    }
    case Tetromino::Type::T: {
        return sf::Color(142, 68, 173);
    }
    }
}

/*
Algorithm: iterate through all pieces in the tetromino and check
if any of them are either out of bound, or its position on the board
is wall/piece (depending on the option).
*/
bool Tetris::isCollide(Tetromino& tetromino, CollideOptions options) {
    Array5x5 const& pieces = tetromino.getCurrentRotation();
    for (int i = 0; i < pieces.size(); ++i) {
        for (int j = 0; j < pieces[i].size(); ++j) {
            if (pieces[i][j] == 1) {
                sf::Vector2i const& current_pos = tetromino.getPos();
                int x = current_pos.x + (i - 2);
                int y = current_pos.y + (j - 2);
                if (
                    x < 0 || x >= board.size() ||
                    y < 0 || y >= board[0].size()
                )
                    return true;
                
                int temp = board[x][y].value;
                if (options == CollideOptions::Piece && temp == 1) {
                    return true;
                }
                else if (options == CollideOptions::Wall && temp == -1) {
                    return true;
                }
                else if (options == CollideOptions::All)
                    if (temp == 1 || temp == -1)
                        return true;
            }
        }
    }
    return false;
}
bool Tetris::isMovable(Tetromino& tetromino) {
    bool result = false;

    moveDown(tetromino);
    if (isCollide(tetromino)) {
        result = false;
    }
    else
        result = true;
    
    moveUp(tetromino);
    return result;
}

void Tetris::moveDown(Tetromino& tetromino) {
    tetromino.moveDown();
}
void Tetris::moveRight(Tetromino& tetromino) {
    tetromino.moveRight();
    if (isCollide(tetromino))
        tetromino.moveLeft();
}
void Tetris::moveLeft(Tetromino& tetromino) {
    tetromino.moveLeft();
    if (isCollide(tetromino))
        tetromino.moveRight();
}
void Tetris::moveUp(Tetromino& tetromino) {
    tetromino.moveUp();
}

/*
The general algorithm for wall kicking is:
try to rotate, and then move to the right 2 times,
then to the left 2 times. If at any point (5 points in total)
the piece isn't collide with any piece AND isn't collide with any wall,
then the rotation and position will be at that point. Otherwise,
it fails to rotate.
*/
void Tetris::rotateLeft(Tetromino& tetromino) {
    tetromino.rotateLeft();

    bool result = isCollide(tetromino);
    int move = 0;
    
    if (!result)
        return;
    
    bool fail = false;
    while (move < 3) {
        tetromino.moveRight();
        ++move;

        if (isCollide(tetromino, CollideOptions::Piece)) {
            // Move back to old position
            for (int i = 0; i < move; ++i)
                tetromino.moveLeft();
            fail = true;
            break;
        }
        else if (!isCollide(tetromino, CollideOptions::Wall)) {
            break;
        }
    }

    if (!fail)
        return;
    
    move = 0;
    while (move < 3) {
        tetromino.moveLeft();
        ++move;

        if (isCollide(tetromino, CollideOptions::Piece)) {
            // Move back to old position
            for (int i = 0; i < move; ++i)
                tetromino.moveRight();
            
            // At this point, rotation failed so rotate back to old form.
            tetromino.rotateRight();
            fail = true;
            break;
        }
        else if (!isCollide(tetromino, CollideOptions::Wall)) {
            break;
        }
    }
}
void Tetris::rotateRight(Tetromino& tetromino) {
    tetromino.rotateRight();

    bool result = isCollide(tetromino, CollideOptions::Wall);
    int move = 0;
    
    if (!result)
        return;
    bool fail = false;
    while (move < 3) {
        tetromino.moveLeft();
        ++move;

        if (isCollide(tetromino, CollideOptions::Piece)) {
            // Move back to old position
            for (int i = 0; i < move; ++i)
                tetromino.moveRight();
            fail = true;
            break;
        }
        else if (!isCollide(tetromino, CollideOptions::Wall)) {
            break;
        }
    }

    if (!fail)
        return;
    
    move = 0;
    while (move < 3) {
        tetromino.moveRight();
        ++move;

        if (isCollide(tetromino, CollideOptions::Piece)) {
            // Move back to old position
            for (int i = 0; i < move; ++i)
                tetromino.moveLeft();
            
            // At this point, rotation failed so rotate back to old form.
            tetromino.rotateLeft();
            fail = true;
            break;
        }
        else if (!isCollide(tetromino, CollideOptions::Wall)) {
            break;
        }
    }
}

void Tetris::updateBoard() {
    if (!isMovable(tetrominoes[0])) {
        Array5x5 const& pieces = tetrominoes[0].getCurrentRotation();
        for (int i = 0; i < pieces.size(); ++i) {
            for (int j = 0; j < pieces[i].size(); ++j) {
                if (pieces[i][j] == 1) {
                    sf::Vector2i const& current_pos = tetrominoes[0].getPos();
                    int x = current_pos.x + (i - 2);
                    int y = current_pos.y + (j - 2);
                    board[x][y].value = 1;
                    board[x][y].color = current_color;
                }
            }
        }
        clearLines();
    }
}
void Tetris::clearLines() {
    int rows[4]; // maximum clear lines in one go is 4
    int index = 0;

    for (int b_col = 0; b_col < board[0].size() - wall_y; ++b_col) {
        bool isFull = true;
        for (int b_row = 0; b_row < board.size(); ++b_row) {
            if (board[b_row][b_col].value == 0) {
                isFull = false;
                break;
            }
        }

        if (isFull) {
            rows[index++] = b_col;
        }
    }

    for (int iter = 0; iter < index; ++iter) {
        for (int i = 0; i < board.size(); ++i) {
            for (int j = rows[iter]; j > 0; --j) {
                board[i][j] = board[i][j - 1];
            }
        }
    }

    incSpeed(index);
    incScore(index);
}
void Tetris::incSpeed(int lines) {
    if (lines > 0 && tick > 0.1)
        tick -= 0.0005;
}
void Tetris::incScore(int lines) {
    if (lines > 0 && lines < 4) {
        score += 100 * (lines);
        std::cout << "Score: " << score << '\n';
    }
    else if (lines == 4) {
        score += 800;
        std::cout << "Score: " << score << '\n';
    }
}

void Tetris::updateHint() {
    if (settings.hint) {
        tetrominoes[1] = tetrominoes[0];

        while (isMovable(tetrominoes[1])) {
            moveDown(tetrominoes[1]);
        }
    }
}

void Tetris::render() {
    window.clear();

    // Draw the entire board
    shape.setSize(sf::Vector2f(grid - grid_offset, grid - grid_offset));
    shape.setOutlineColor(sf::Color(52, 73, 64));
    shape.setOutlineThickness(outline);

    for (int i = 0; i < board.size(); ++i) {
        for (int j = space_y; j < board[i].size(); ++j) {
            {
                shape.setFillColor(board[i][j].color);
                shape.setPosition(sf::Vector2f(
                    (i) * grid,
                    (j - space_y) * grid
                ));
                window.draw(shape);
            }
        }
    }

    // Draw next piece
    shape.setFillColor(next_color);

    Array5x5 const& render_next = tetrominoes[2].getCurrentRotation();
    for (int i = 0; i < render_next.size(); ++i) {
        for (int j = 0; j < render_next[i].size(); ++j) {
            if (render_next[i][j] == 1) {
                sf::Vector2i const& current_pos = tetrominoes[2].getPos();
                shape.setPosition(sf::Vector2f(
                    (current_pos.x + (i - 2)) * grid,
                    (current_pos.y + (j - 2)) * grid
                ));
                window.draw(shape);
            }
        }
    }

    // Draw hint
    if (settings.hint) {
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(getTetrominoColor(tetrominoes[1]));
        shape.setOutlineThickness(outline);

        Array5x5 const& render_hint = tetrominoes[1].getCurrentRotation();
        for (int i = 0; i < render_hint.size(); ++i) {
            for (int j = 0; j < render_hint[i].size(); ++j) {
                if (render_hint[i][j] == 1) {
                    sf::Vector2i const& current_pos = tetrominoes[1].getPos();
                    shape.setPosition(sf::Vector2f(
                        (current_pos.x + (i - 2)) * grid,
                        (current_pos.y + (j - 2) - space_y) * grid
                    ));
                    window.draw(shape);
                }
            }
        }
    }

    // Draw current piece
    shape.setFillColor(current_color);
    shape.setOutlineColor(sf::Color(52, 73, 64));
    shape.setOutlineThickness(outline);
    
    Array5x5 const& render = tetrominoes[0].getCurrentRotation();
    for (int i = 0; i < render.size(); ++i) {
        for (int j = 0; j < render[i].size(); ++j) {
            if (render[i][j] == 1) {
                sf::Vector2i const& current_pos = tetrominoes[0].getPos();
                shape.setPosition(sf::Vector2f(
                    (current_pos.x + (i - 2)) * grid,
                    (current_pos.y + (j - 2) - space_y) * grid
                ));
                window.draw(shape);
            }
        }
    }
    
    window.display();
}
void Tetris::processEvent(sf::Event event) {
    sf::Event::EventType type = event.type;

    if (type == sf::Event::Closed) {
        window.close();
        movable = false;
    }
    else if (type == sf::Event::KeyPressed) {
        //...
        auto key = event.key.code;
        switch (key) {
        case sf::Keyboard::Escape: {
            window.close();
            break;
        }
        case sf::Keyboard::D: {
            if (!is_pause)
                moveRight(tetrominoes[0]);
            break;
        }
        case sf::Keyboard::A: {
            if (!is_pause)
                moveLeft(tetrominoes[0]);
            break;
        }
        case sf::Keyboard::Left: {
            if (!is_pause)
                rotateLeft(tetrominoes[0]);
            break;
        }
        case sf::Keyboard::Right: {
            if (!is_pause)
                rotateRight(tetrominoes[0]);
            break;
        }
        case sf::Keyboard::Space: {
            if (settings.hard_drop && !is_pause) {
                while (isMovable(tetrominoes[0]))
                    moveDown(tetrominoes[0]);
                is_hard_drop = true;
                movable = false;
            }
            break;
        }
        case sf::Keyboard::P: {
            is_pause = !is_pause;
            break;
        }
        
        }

        // We update hint every input from player.
        updateHint();
    }
}

void Tetris::print() {
    for (auto const& i : board) {
        for (auto const& j : i) {
            std::cout << j.value << ' ';
        }
        std::cout << '\n';
    }

    std::cout << "Debug: " << (int) settings.debug << '\n';
}

Tetris& Tetris::setDebug(bool is_debug) {
    settings.debug = is_debug;
    return *this;
}
Tetris& Tetris::setHardDrop(bool is_hard_drop) {
    settings.hard_drop = is_hard_drop;
    return *this;
}
Tetris& Tetris::setHint(bool is_hint) {
    settings.hint = is_hint;
    return *this;
}
Tetris& Tetris::setHold(bool is_hold) {
    settings.hold = is_hold;
    return *this;
}
Tetris& Tetris::setInitSpeed(float speed) {
    tick = speed;
}
Tetris& Tetris::setGrid(int grid) {
    this->grid = grid;
}
Tetris& Tetris::setOutlineThickness(int outline) {
    this->outline = outline;
    grid_offset = outline * 2;
}

int Tetris::run() {
    while (window.isOpen()) {
        sf::Time elapsed = render_clock.getElapsedTime();

        if (!movable)
        {
            tetrominoes[0] = std::move(tetrominoes[2]);
            tetrominoes[0].toDefaultPos();

            if (settings.hint) {
                tetrominoes[1] = tetrominoes[0];
                updateHint();
            }

            // Losing condition
            if (isCollide(tetrominoes[0], CollideOptions::Piece)) {
                break;
            }

            tetrominoes[2] = std::move(Tetromino(static_cast<Tetromino::Type>(genRandomTetromino())));
            tetrominoes[2].setPos(14, 3);

            current_color = next_color;
            next_color = getTetrominoColor(tetrominoes[2]);

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
                movable = isMovable(tetrominoes[0]);
                if (movable && !is_pause) {
                    moveDown(tetrominoes[0]);
                }
            }

            tick_clock.restart();
            is_hard_drop = false;
        }

        this->render();
        render_clock.restart();

        if (!movable) {
            updateBoard();

            if (settings.debug) {
                print();
            }
        }
    }

    return score;
}

#endif
