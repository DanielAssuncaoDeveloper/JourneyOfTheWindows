#include "../position/position_service.h"

#ifndef ENTITYSERVICE_H
#define ENTITYSERVICE_H

typedef struct GAME_ENTITY {
    enum ENTITY_DIRECTION direction;
    MAP_POSITION* position;
} GAME_ENTITY;

enum ENTITY_DIRECTION {
    ENTITY_DIRECTION_NONE,   // -
    ENTITY_DIRECTION_UP,     // ^
    ENTITY_DIRECTION_RIGHT,  // >
    ENTITY_DIRECTION_DOWN,   // v
    ENTITY_DIRECTION_LEFT    // <
};

GAME_ENTITY* get_pointer_to_array_entities(int lentgh);

GAME_ENTITY init_entity(int x_position, int y_position, MAP_POSITION** positions);

#endif //ENTITYSERVICE_H
