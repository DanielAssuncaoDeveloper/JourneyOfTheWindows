#include "funcion_action_service.h"
#include "../display/game/game_service.h"

void action_walk(GAME_ENTITY* entity) {
	ENTITY_DIRECTION direction = entity->direction;
	MAP_POSITION old_position = *(entity->position);

	MAP_POSITION new_position = {
		.grid_column_position = old_position.grid_column_position,
		.grid_row_position = old_position.grid_row_position
	};

	switch (direction)
	{
		case ENTITY_DIRECTION_UP:
			new_position.grid_column_position = old_position.grid_column_position - 1;
			break;

		case ENTITY_DIRECTION_RIGHT:
			new_position.grid_row_position = old_position.grid_row_position + 1;
			break;
			
		case ENTITY_DIRECTION_DOWN:
			new_position.grid_column_position = old_position.grid_column_position + 1;
			break;

		case ENTITY_DIRECTION_LEFT:
			new_position.grid_row_position = old_position.grid_row_position - 1;
			break;

		default:
			break;
	}

	entity_walk_to_position(entity, new_position);
}

void action_rotate_clockwise(GAME_ENTITY* entity) {
	int new_direction = entity->direction - 1;
	entity_change_direction(entity, new_direction);
}

void action_rotate_counterclockwise(GAME_ENTITY* entity) {
	int new_direction = entity->direction + 1;
	entity_change_direction(entity, new_direction);
}

void action_collect(GAME_ENTITY* entity) {
	GAME_ENTITY** entities_on_position = get_entities_on_position(&game.current_stage, entity->position);

	int entities_found = get_array_size(entities_on_position);
	GAME_ENTITY* collectable_entity = NULL;
	
	for (int i = 0; i < entities_found; i++)
	{
		GAME_ENTITY* loop_entity = entities_on_position[i];

		if (loop_entity == NULL) continue;
		if (loop_entity->hide) continue;

		if (loop_entity->type == ENTITY_TYPE_COLLECTABLE) {
			collectable_entity = entities_on_position[i];
			continue;
		}
	}

	if (collectable_entity) {
		collectable_entity->hide = true;
		game.items_collected++;
	}
}

