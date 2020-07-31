#ifndef TETRISV3_TETROMINO_HPP
#define TETRISV3_TETROMINO_HPP

#include <array>
#include <SFML/System/Vector2.hpp>

using Array5x5 = std::array<std::array<int, 5>, 5>;

class Tetromino {
public:
    /*
    The Tetromino type.
    It is strongly-typed, so Tetromino::... is required.
    */
    enum class Type {
        I,
        J,
        L,
        N,
        O,
        S,
        T
    };
private:
    /*
    The array representation of a tetromino.
    The size it occupies is 4 * 5 * 5 * sizeof(int).
    
    See also the note in the definition of the constructor.
    */
    std::array<Array5x5, 4> tetromino;
    /*
    The position of the center piece of the tetromino.
    The position is relative to the tetris board's position.
    */
    sf::Vector2i pos;
    /*
    The rotation index used to determine what rotation is the tetromino on.
    Basically, it's the index of the tetromino array.
    */
    int rotation_index;

    Tetromino::Type type;

    void setType(Tetromino::Type const& type);
public:
    /*
    Get the type of the tetromino.
    */
    Tetromino::Type const& getType() const;
    /*
    Return a const ref to 5 x 5 array represents the current "form" of the tetromino.
    Basically it returns tetromino[rotation_index].
    */
    Array5x5 const& getCurrentRotation() const;
    /*
    Return the pivot's position relative to the board.
    */
    sf::Vector2i const& getPos() const;

    /*
    Set the pivot's position.
    This function should not be used other than to set the next piece's position.
    */
    void setPos(int const& x, int const& y);
    /*
    Set the pivot's position to default's position based on the type of the tetromino.
    */
    void toDefaultPos();

    /*
    Move the tetromino down.
    This action is done regardless of the collision.
    */
    void moveDown();
    /*
    Move the tetromino right.
    This action is done regardless of the collision.
    */
    void moveRight();
    /*
    Move the tetromino left.
    This action is done regardless of the collision.
    */
    void moveLeft();
    /*
    Move the tetromino up.
    This action is done regardless of the collision.
    This function should only be called to test possible movement.
    */
    void moveUp();

    /*
    Rotate the tetromino clockwise.
    This action is done regardless of the collision.
    */
    void rotateRight();
    /*
    Rotate the tetromino counterclockwise.
    This action is done regardless of the collision.
    */
    void rotateLeft();

    Tetromino() = default;
    /*
    Create a Tetromino.

    Param:
    - type: the Tetromino::Type you want it to be.
    */
    Tetromino(Tetromino::Type type);
    Tetromino(Tetromino const& obj);

    Tetromino& operator=(Tetromino const& obj);
    friend bool operator==(Tetromino const& lhs, Tetromino const& rhs);
};

#endif