#include "tetromino.hpp"

#include <vector>
#include <ctime>
#include <stdexcept>
#include <algorithm>

#include <SFML/Graphics.hpp>

struct Tile {
    int value;
    sf::Color color;
};

class Tetris {
protected:
    static const int size_x = 10;
    static const int size_y = 20;
    static const int wall_x = 2;
    static const int wall_y = 1;
    static const int space_y = 3;
    static constexpr float outline = 1.0f;

    /*
    The game setting options.
    */
    struct {
        bool debug = false;
        bool hold = false;
        bool hard_drop = true;
        bool hint = true;

    } settings;

    /**
     * The tetris board representation.
     *
     * The data saved in this board is inversed with the actual position on screen,
     * meaning that board[x][y] will mean the piece at (x * grid; y * grid).
     * 
     * The board also include walls and spare space above the playground.
     */
    std::array<std::array<Tile, size_y + wall_y + space_y>, size_x + wall_x> board;
    /**
     * Raw pointer to the current tetromino.
     * 
     * It is advised not to change this pointer except in
     * the constructor (nullptr) and in run().
     * 
     * Typically, this pointer will be pointed to the next pointer,
     * and it's responsible for deleting that memory when done.
     */
    //Tetromino* current;
    /*
    Raw pointer to the next tetromino.

    It is advised to always bind this pointer with the function
    genRandomTetromino() due to how it works.

    Typically, you should never do `delete hint;` except in the destructor.
    The pointer is responsible for allocating memory block, transfer that to
    the current pointer, and is only deleted by the destructor.
    */
    Tetromino* next;
    /*
    Raw pointer to the "hinting" tetromino.

    It is advised to either set this to nullptr (settings.hint = false), or
    allocate a DEEP COPY of `current`.

    Typically, this pointer will be deleted and allocated inside showHint() everytime
    it's called, and can only explicitly delete inside run() (when current is deleted).
    */
    Tetromino* hint;
    std::vector<Tetromino> pieces;
    /*
    The game tick.

    Basically this is the seconds before the tetromino moves down.
    */
    float tick;
    int score;
    /*
    A check to see if the current tetromino can move down or not.
    */
    bool movable;
    bool is_hard_drop;
    bool is_pause;

    sf::RenderWindow& window;
    sf::RectangleShape shape;
    /*
    The color of the current tetromino.
    Usually obtained using getTetrominoColor(current).
    */
    sf::Color current_color;
    /*
    The color of the next tetromino.
    Usually obtained using getTetrominoColor(next).
    */
    sf::Color next_color;
    const int grid;

    sf::Clock render_clock;
    sf::Clock tick_clock;
    sf::Time dt = sf::seconds(1.0f / 60.0f);

    /*
    Generate a random number from 0-6 based on Tetris NES algorithm.
    */
    int genRandomTetromino();
    /*
    Return the color for the tetromino based on its type.
    */
    sf::Color getTetrominoColor(Tetromino const* tetromino);

    /*
    A check to see if the tetromino can move down or not.
    */
    bool isMovable(Tetromino* current);
    enum class CollideOptions {
        Wall,
        Piece,
        All
    };
    /*
    A check to see whether the tetromino collides with wall and/or piece.
    */
    bool isCollide(Tetromino* tetromino, CollideOptions options = CollideOptions::All);

    /*
    Move the tetromino down with collision checking.
    */
    void moveDown(Tetromino* tetromino);
    /*
    Move the tetromino right with collision checking.
    */
    void moveRight(Tetromino* tetromino);
    /*
    Move the tetromino left with collision checking.
    */
    void moveLeft(Tetromino* tetromino);
    /*
    Move the tetromino up.
    */
    void moveUp(Tetromino* tetromino);
    /*
    Rotate the tetromino counterclockwise with collision checking and wall kicking.
    */
    void rotateLeft(Tetromino* tetromino);
    /*
    Rotate the tetromino clockwise with collision checking and wall kicking.
    */
    void rotateRight(Tetromino* tetromino);

    /*
    Update the board with placed tetromino.
    */
    void updateBoard();
    /*
    Clear all the full lines.
    Also increases tick speed.
    */
    void clearLines();
    void incSpeed(int lines);
    virtual void incScore(int lines);

    /*
    Show the hint using the hint pointer.

    It manually manages the hint pointer, so be caution
    when override this.
    */
    void updateHint();
    /*
    An abstract way to delete both the current pointer and
    the hint pointer and set both to nullptr.
    */
    void cleanUpMemory();

    // Debug

    /*
    Display the array to console.
    */
    void print();
    /*
    Draw to window.
    */
    void render();

    virtual void processEvent(sf::Event event);
public:
    /*
    A blocking function that run the game.

    Press ESC or close the window to exit this function.
    */
    virtual int run();
    
    Tetris& setDebug(bool enable_debug = false);
    Tetris& setHint(bool enable_hint = true);
    Tetris& setHardDrop(bool enable_quick_drop = true);
    Tetris& setHold(bool enable_hold = false);

    /*
    Create a Tetris instance that use the window to render.

    Also allocate memory for the next pointer.
    */
    Tetris(sf::RenderWindow& window);
    /*
    The destructor.

    It should be used to delete the next pointer.
    */
    ~Tetris();
};

/*
We generate all possible "end" position for the tetromino,
which is to generate all possible move where isCollide(current) == true.

Then we rank, based on:
- Avoid creating holes (holeCount).
- Avoid stacking up too high (3 should be the max).

*/
class TetrisAI : public Tetris {
public:
    int ai_score;
    int height;
    std::vector<Tetromino> possible_ends;

    int run();
    void incScore(int lines);
    void processEvent(sf::Event event);
    int calculateHeight();
    int calcValue();
    int countHoles();
    int find_max(std::vector<Tetromino>& pe);
    void logic() {
        height = calculateHeight();
        int current_height;
        int max_index = 0;
        for (int i = 0; i < board.size(); ++i) {
            // spawn tetris
            while (current_height > height && !isMovable(hint)) {
                moveDown(hint);
            }

            
            
        }
    }

    void recursion(Tetromino* copy_hint) {
        while (isMovable(hint)) {
            int move = rand() % 4;
            switch (move) {
            case 0: {
                moveLeft(hint);
                break;
            }
            case 1: {
                moveRight(hint);
                break;
            }
            case 2: {
                rotateLeft(hint);
                break;
            }
            case 3: {
                rotateRight(hint);
                break;
            }
            }

            moveDown(hint);
        }

        auto result = std::find_if(possible_ends.begin(), possible_ends.end(), [&](Tetromino& p) {
            return (*hint) == p;
        });

        if (result == possible_ends.end()) {
            possible_ends.push_back(*hint);
        }
        else {
            return;
        }
    }
    
    

    TetrisAI(sf::RenderWindow& window);
};
