
#ifndef ENTITYSERVICE_H
#define ENTITYSERVICE_H

enum Direction {
    NONE,   // -
    UP,     // ^
    RIGHT,  // >
    DOWN,   // v
    LEFT    // <
};

struct Entity {
    enum Direction direction;
    struct Position* position;
};


#endif //ENTITYSERVICE_H
