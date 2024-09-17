#include <stdlib.h>
#include "entity_service.h"
#include "../position/position_service.h";

GAME_ENTITY* get_pointer_to_array_entities(int lentgh) {
    GAME_ENTITY* array_entity_pointer = calloc(lentgh, sizeof(GAME_ENTITY));
    return array_entity_pointer;
}

GAME_ENTITY init_entity(int grid_column_position, int grid_row_position, MAP_POSITION** positions)
{
    GAME_ENTITY entity;
    entity.position = &(positions[grid_column_position][grid_row_position]);

    return entity;
}
