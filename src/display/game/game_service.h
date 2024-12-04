#include "../stage/stage_service.h"
#include "../action_block/action_blocks_service.h"

#ifndef GAMESERVICE_H
#define GAMESERVICE_H

typedef struct GAME {
	GAME_STAGE current_stage;
	ACTION_BLOCK* instantiated_blocks;
	int action_order;
	int items_collected;

	bool player_colisided;
	bool executing_actions;
	bool game_end;
	bool win;
} GAME;

extern GAME game;

void game_print(GAME* game);
bool is_start_action(ALLEGRO_EVENT* event);
bool is_how_to_play_button(ALLEGRO_EVENT* event);
void execute_action(GAME* game);

#endif //GAMESERVICE_H