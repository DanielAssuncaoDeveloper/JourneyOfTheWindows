#include "../position/position_service.h"

#ifndef ENTITYSERVICE_H
#define ENTITYSERVICE_H

typedef struct GAME_ENTITY {
    enum ENTITY_DIRECTION direction;
    enum ENTITY_TYPE type;

    bool hide;
    MAP_POSITION* position;
    ALLEGRO_BITMAP* bitmap;
} GAME_ENTITY;

typedef enum ENTITY_DIRECTION {
    ENTITY_DIRECTION_UP,     // ^
    ENTITY_DIRECTION_RIGHT,  // >
    ENTITY_DIRECTION_DOWN,   // v
    ENTITY_DIRECTION_LEFT    // <
} ENTITY_DIRECTION;

typedef enum ENTITY_TYPE {
    ENTITY_TYPE_PLAYER,     
    ENTITY_TYPE_COLLECTABLE,
    ENTITY_TYPE_COMPONENT  
} ENTITY_TYPE;

GAME_ENTITY* get_pointer_to_array_entities(int lentgh);

GAME_ENTITY init_entity(int x_position, int y_position, MAP_POSITION** positions, ALLEGRO_BITMAP* image_bitmap, int entity_type);

void entity_change_direction(GAME_ENTITY* entity, int new_direction);

void entity_walk_to_position(GAME_ENTITY* entity, MAP_POSITION new_position);

#endif //ENTITYSERVICE_H
