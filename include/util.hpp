#include <iostream> // Debug purpose

enum Direction {
    NONE,
    UP,
    RIGHT,
    DOWN,
    LEFT,
    ROTATE_RIGHT,
    ROTATE_LEFT
};

// A relative safe way to delete a pointer.
// Basically it'll delete the pointer and point to nullptr for you.
// It won't delete a null pointer.
template<typename T>
void safe_delete(T* pointer) {
    if (pointer != nullptr) {
        delete pointer;
        pointer = nullptr;
    }
}
