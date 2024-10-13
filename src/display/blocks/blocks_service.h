#include <allegro5/allegro.h>
#include <stdbool.h>

#ifndef BLOCKS_SERVICE_H
#define BLOCKS_SERVICE_H

typedef struct Block {
	int position_x, position_y;
	int width, height;
	ALLEGRO_BITMAP* bitmap;
	void (*func)();
} Block;

Block* create_block(ALLEGRO_BITMAP*, int position_x, int position_y, int width, int height, void (*func)());

void draw_block(Block* block);

void handle_mouse_event(ALLEGRO_EVENT* event, Block** head);

#endif