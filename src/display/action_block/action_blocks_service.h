#include <allegro5/allegro.h>
#include <stdbool.h>
#include "../../action/funcion_action_service.h"

#ifndef BLOCKS_SERVICE_H
#define BLOCKS_SERVICE_H

typedef struct ACTION_BLOCK {
	int position_x, position_y;
	int width, height;
	ALLEGRO_BITMAP* bitmap;
	ACTION_TYPE action_type;
	void (*ptr_action)(GAME_ENTITY*);
} ACTION_BLOCK;

ACTION_BLOCK create_block(ALLEGRO_BITMAP* bitmap, int position_x, int position_y, ACTION_TYPE action_type);

void draw_block(ACTION_BLOCK* block);

void on_handle_mouse_event(ALLEGRO_EVENT* event, ACTION_BLOCK* instantiated_blocks_list);
ACTION_BLOCK* on_deleting_block(ALLEGRO_EVENT* event, ACTION_BLOCK* instantiated_blocks, bool* redraw);
ACTION_BLOCK* on_intantiating_block(ALLEGRO_EVENT* event, ACTION_BLOCK* blocks_template, ACTION_BLOCK* instantiated_blocks, bool* redraw);

#endif