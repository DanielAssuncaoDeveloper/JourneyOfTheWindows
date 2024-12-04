#include "../display/entity/entity_service.h"
#include "../display/map/map_service.h"

#ifndef FUNCTIONACTIONSERVICE_H
#define FUNCTIONACTIONSERVICE_H

void action_walk(GAME_ENTITY* entity);
void action_rotate_clockwise(GAME_ENTITY* entity);
void action_rotate_counterclockwise(GAME_ENTITY* entity);
void action_collect(GAME_ENTITY* entity);

typedef enum ACTION_TYPE {
	ACTION_WALK,
	ACTION_ROTATE_CLOCKWISE,
	ACTION_ROTATE_COUNTERCLOCKWISE,
	ACTION_COLLECT
} ACTION_TYPE;

#endif
