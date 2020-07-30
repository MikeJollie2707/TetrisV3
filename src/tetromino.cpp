#include "tetromino.hpp"

Tetromino::Tetromino(Tetromino::Type type) :
type(type) {
    for (auto& i : tetromino)
        for (auto& j : i)
            for (auto& k : j)
                k = 0;
    /*
    The following comments are there
    to help visualize the ARRAY of the tetromino.
    When drawing to window, the image will be
    REFLECTED diagonally, meaning the ARRAY of L
    will actually be a J tetromino, and N will actually
    be a mirror N tetromino, and vice versa.
    */
    switch (type) {
    case Tetromino::Type::I: {
        /*
        0 0 0 0 0
        0 0 1 0 0
        0 0 1 0 0
        0 0 1 0 0
        0 0 1 0 0
        */
        tetromino[0][2][2] = 1;
        tetromino[0][1][2] = 1;
        tetromino[0][3][2] = 1;
        tetromino[0][4][2] = 1;

        /*
        0 0 0 0 0
        0 0 0 0 0
        1 1 1 1 0
        0 0 0 0 0
        0 0 0 0 0
        */
        tetromino[1][2][2] = 1;
        tetromino[1][2][0] = 1;
        tetromino[1][2][1] = 1;
        tetromino[1][2][3] = 1;

        /*
        0 0 1 0 0
        0 0 1 0 0
        0 0 1 0 0
        0 0 1 0 0
        0 0 0 0 0
        */
       tetromino[2][2][2] = 1;
       tetromino[2][0][2] = 1;
       tetromino[2][1][2] = 1;
       tetromino[2][3][2] = 1;

       /*
       0 0 0 0 0
       0 0 0 0 0
       0 1 1 1 1
       0 0 0 0 0
       0 0 0 0 0
       */
       tetromino[3][2][2] = 1;
       tetromino[3][2][1] = 1;
       tetromino[3][2][3] = 1;
       tetromino[3][2][4] = 1;

       break;
    }
    case Tetromino::Type::J: {
        /*
        0 0 0 0 0
        0 0 1 0 0
        0 0 1 0 0
        0 0 1 1 0
        0 0 0 0 0
        */
        tetromino[0][2][2] = 1;
        tetromino[0][1][2] = 1;
        tetromino[0][3][2] = 1;
        tetromino[0][3][3] = 1;

        /*
        0 0 0 0 0
        0 0 0 0 0
        0 1 1 1 0
        0 1 0 0 0
        0 0 0 0 0
        */
        tetromino[1][2][2] = 1;
        tetromino[1][3][1] = 1;
        tetromino[1][2][1] = 1;
        tetromino[1][2][3] = 1;

        /*
        0 0 0 0 0
        0 1 1 0 0
        0 0 1 0 0
        0 0 1 0 0
        0 0 0 0 0
        */
        tetromino[2][2][2] = 1;
        tetromino[2][1][2] = 1;
        tetromino[2][1][1] = 1;
        tetromino[2][3][2] = 1;

        /*
        0 0 0 0 0
        0 0 0 1 0
        0 1 1 1 0
        0 0 0 0 0
        0 0 0 0 0
        */
        tetromino[3][2][2] = 1;
        tetromino[3][2][1] = 1;
        tetromino[3][2][3] = 1;
        tetromino[3][1][3] = 1;

        break;
    }
    case Tetromino::Type::L: {
        /*
        0 0 0 0 0
        0 0 1 0 0
        0 0 1 0 0
        0 1 1 0 0
        0 0 0 0 0
        */
        tetromino[0][2][2] = 1;
        tetromino[0][1][2] = 1;
        tetromino[0][3][2] = 1;
        tetromino[0][3][1] = 1;

        /*
        0 0 0 0 0
        0 1 0 0 0
        0 1 1 1 0
        0 0 0 0 0
        0 0 0 0 0
        */
        tetromino[1][2][2] = 1;
        tetromino[1][1][1] = 1;
        tetromino[1][2][1] = 1;
        tetromino[1][2][3] = 1;

        /*
        0 0 0 0 0
        0 0 1 1 0
        0 0 1 0 0
        0 0 1 0 0
        0 0 0 0 0
        */
        tetromino[2][2][2] = 1;
        tetromino[2][1][2] = 1;
        tetromino[2][1][3] = 1;
        tetromino[2][3][2] = 1;

        /*
        0 0 0 0 0
        0 0 0 0 0
        0 1 1 1 0
        0 0 0 1 0
        0 0 0 0 0
        */
        tetromino[3][2][2] = 1;
        tetromino[3][2][1] = 1;
        tetromino[3][2][3] = 1;
        tetromino[3][3][3] = 1;

        break;
    }
    case Tetromino::Type::N: {
        /*
        0 0 0 0 0
        0 1 0 0 0
        0 1 1 0 0
        0 0 1 0 0
        0 0 0 0 0
        */
        tetromino[0][2][2] = 1;
        tetromino[0][3][2] = 1;
        tetromino[0][2][1] = 1;
        tetromino[0][1][1] = 1;

        /*
        0 0 0 0 0
        0 0 1 1 0
        0 1 1 0 0
        0 0 0 0 0
        0 0 0 0 0
        */
        tetromino[1][2][2] = 1;
        tetromino[1][1][3] = 1;
        tetromino[1][1][2] = 1;
        tetromino[1][2][1] = 1;

        /*
        0 0 0 0 0
        0 0 1 0 0
        0 0 1 1 0
        0 0 0 1 0
        0 0 0 0 0
        */
        tetromino[2][2][2] = 1;
        tetromino[2][1][2] = 1;
        tetromino[2][2][3] = 1;
        tetromino[2][3][3] = 1;

        /*
        0 0 0 0 0
        0 0 0 0 0
        0 0 1 1 0
        0 1 1 0 0
        0 0 0 0 0
        */
        tetromino[3][2][2] = 1;
        tetromino[3][2][3] = 1;
        tetromino[3][3][2] = 1;
        tetromino[3][3][1] = 1;

        break;
    }
    case Tetromino::Type::O: {
        /*
        0 0 0 0 0
        0 1 1 0 0
        0 1 1 0 0
        0 0 0 0 0
        0 0 0 0 0
        */
        tetromino[0][2][2] = 1;
        tetromino[0][1][1] = 1;
        tetromino[0][1][2] = 1;
        tetromino[0][2][1] = 1;

        /*
        0 0 0 0 0
        0 1 1 0 0
        0 1 1 0 0
        0 0 0 0 0
        0 0 0 0 0
        */
        tetromino[1][2][2] = 1;
        tetromino[1][1][1] = 1;
        tetromino[1][1][2] = 1;
        tetromino[1][2][1] = 1;

        /*
        0 0 0 0 0
        0 1 1 0 0
        0 1 1 0 0
        0 0 0 0 0
        0 0 0 0 0
        */
        tetromino[2][2][2] = 1;
        tetromino[2][1][1] = 1;
        tetromino[2][1][2] = 1;
        tetromino[2][2][1] = 1;

        /*
        0 0 0 0 0
        0 1 1 0 0
        0 1 1 0 0
        0 0 0 0 0
        0 0 0 0 0
        */
        tetromino[3][2][2] = 1;
        tetromino[3][1][1] = 1;
        tetromino[3][1][2] = 1;
        tetromino[3][2][1] = 1;

        break;
    }
    case Tetromino::Type::S: {
        /*
        0 0 0 0 0
        0 0 1 0 0
        0 1 1 0 0
        0 1 0 0 0
        0 0 0 0 0
        */
        tetromino[0][2][2] = 1;
        tetromino[0][1][2] = 1;
        tetromino[0][2][1] = 1;
        tetromino[0][3][1] = 1;

        /*
        0 0 0 0 0
        0 1 1 0 0
        0 0 1 1 0
        0 0 0 0 0
        0 0 0 0 0
        */
        tetromino[1][2][2] = 1;
        tetromino[1][1][1] = 1;
        tetromino[1][1][2] = 1;
        tetromino[1][2][3] = 1;

        /*
        0 0 0 0 0
        0 0 0 1 0
        0 0 1 1 0
        0 0 1 0 0
        0 0 0 0 0
        */
        tetromino[2][2][2] = 1;
        tetromino[2][1][3] = 1;
        tetromino[2][2][3] = 1;
        tetromino[2][3][2] = 1;

        /*
        0 0 0 0 0
        0 0 0 0 0
        0 1 1 0 0
        0 0 1 1 0
        0 0 0 0 0
        */
        tetromino[3][2][2] = 1;
        tetromino[3][2][1] = 1;
        tetromino[3][3][2] = 1;
        tetromino[3][3][3] = 1;

        break;
    }
    case Tetromino::Type::T: {
        /*
        0 0 0 0 0
        0 0 1 0 0
        0 0 1 1 0
        0 0 1 0 0
        0 0 0 0 0
        */
        tetromino[0][2][2] = 1;
        tetromino[0][1][2] = 1;
        tetromino[0][3][2] = 1;
        tetromino[0][2][3] = 1;

        /*
        0 0 0 0 0
        0 0 0 0 0
        0 1 1 1 0
        0 0 1 0 0
        0 0 0 0 0
        */
        tetromino[1][2][2] = 1;
        tetromino[1][2][1] = 1;
        tetromino[1][2][3] = 1;
        tetromino[1][3][2] = 1;

        /*
        0 0 0 0 0
        0 0 1 0 0
        0 1 1 0 0
        0 0 1 0 0
        0 0 0 0 0
        */
        tetromino[2][2][2] = 1;
        tetromino[2][1][2] = 1;
        tetromino[2][2][1] = 1;
        tetromino[2][3][2] = 1;

        /*
        0 0 0 0 0
        0 0 1 0 0
        0 1 1 1 0
        0 0 0 0 0
        0 0 0 0 0
        */
        tetromino[3][2][2] = 1;
        tetromino[3][1][2] = 1;
        tetromino[3][2][1] = 1;
        tetromino[3][2][3] = 1;

        break;
    }
    }

    toDefaultPos();

    rotation_index = 0;
}
Tetromino::Tetromino(Tetromino const& obj) :
tetromino(obj.tetromino),
type(obj.type),
pos(obj.pos),
rotation_index(obj.rotation_index)
{

}
Tetromino& Tetromino::operator=(Tetromino const& obj) {
    tetromino = obj.tetromino;
    type = obj.type;
    pos = obj.pos;
    rotation_index = obj.rotation_index;
}

Tetromino::Type const& Tetromino::getType() const {
    return type;
}

void Tetromino::setType(Tetromino::Type const& type) {
    this->type = type;
}

bool operator==(Tetromino const& lhs, Tetromino const& rhs) {
    return (
        lhs.type == rhs.type &&
        lhs.pos == rhs.pos &&
        lhs.rotation_index == rhs.rotation_index
    );
}

void Tetromino::toDefaultPos() {
    switch (type) {
    case Tetromino::Type::I: {
        pos.x = 5;
        pos.y = 3;
        break;
    }
    case Tetromino::Type::J: {
        pos.x = 5;
        pos.y = 4;
        break;
    }
    case Tetromino::Type::L: {
        pos.x = 5;
        pos.y = 4;
        break;
    }
    case Tetromino::Type::N: {
        pos.x = 5;
        pos.y = 4;
        break;
    }
    case Tetromino::Type::O: {
        pos.x = 5;
        pos.y = 4;
        break;
    }
    case Tetromino::Type::S: {
        pos.x = 5;
        pos.y = 4;
        break;
    }
    case Tetromino::Type::T: {
        pos.x = 5;
        pos.y = 4;
        break;
    }
    }
}
void Tetromino::setPos(int const& x, int const& y) {
    pos.x = x; 
    pos.y = y;
}
sf::Vector2i const& Tetromino::getPos() const {
    return pos;
}

void Tetromino::moveDown() {
    pos.y++;
}
void Tetromino::moveRight() {
    pos.x++;
}
void Tetromino::moveLeft() {
    if (pos.x > 0) {
        pos.x--;
    }
}
void Tetromino::moveUp() {
    if (pos.y > 0) {
        pos.y--;
    }
}

void Tetromino::rotateLeft() {
    if (++rotation_index > 3) {
        rotation_index = 0;
    }
}
void Tetromino::rotateRight() {
    if (--rotation_index < 0) {
        rotation_index = 3;
    }
}

Array5x5 const& Tetromino::getCurrentRotation() const {
    return tetromino[rotation_index];
}
