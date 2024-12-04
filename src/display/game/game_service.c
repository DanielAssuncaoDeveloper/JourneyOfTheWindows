#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

#include "game_service.h"
#include "../../utils/array_utils.h"
#include "../../configuration/game_configure.h"

ALLEGRO_BITMAP* game_screen = NULL;
ALLEGRO_BITMAP* start_button = NULL;
ALLEGRO_BITMAP* button_how_to_play = NULL;
GAME game;

int start_button_position_x = 0;
int start_button_position_y = 0;

int button_how_to_play_position_x = 0;
int button_how_to_play_position_y = 0;

void load_game() {
	if (game_screen == NULL || start_button == NULL) {
		game_screen = al_load_bitmap("game_screen.png");
		start_button = al_load_bitmap("start_button.png");
		button_how_to_play = al_load_bitmap("button_how_to_play.png");
	}

	start_button_position_x = DISPLAY_WIDTH / 2 - al_get_bitmap_width(start_button) / 2;
	start_button_position_y = 112;
	
	button_how_to_play_position_x = 1282;
	button_how_to_play_position_y = 112;

	al_set_target_bitmap(al_get_backbuffer(display));
	al_draw_bitmap(game_screen, 1, 0, 0);	
	al_draw_bitmap(start_button, start_button_position_x, start_button_position_y, 0);
	al_draw_bitmap(button_how_to_play, button_how_to_play_position_x, button_how_to_play_position_y, 0);
}

void execute_action(GAME* game) {
	int blocks_lenght = get_array_size(game->instantiated_blocks);
	if (game->action_order >= blocks_lenght) {
		game->executing_actions = false;
		game->game_end = true;
		
		if (game->items_collected == game->current_stage.items_to_collect) {
			game->win = true;
		}
		else {
			al_set_target_bitmap(al_get_backbuffer(display));
			al_draw_bitmap(al_load_bitmap("information_popup_items_not_collected.png"), 0, 0, 0);

			al_flip_display();
			al_rest(3);
		}

		return;
	}

	GAME_ENTITY* ptr_player = &(game->current_stage.entities[0]);
	ACTION_BLOCK current_block = game->instantiated_blocks[game->action_order];

	current_block.ptr_action(ptr_player);
	game->action_order++;
}

bool is_start_action(ALLEGRO_EVENT* event) {
	if (!start_button) return false;

	if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event->mouse.button == 1) {
		bool is_x_mouse_in_start = event->mouse.x >= start_button_position_x && event->mouse.x <= start_button_position_x + al_get_bitmap_width(start_button);
		bool is_y_mouse_in_start = event->mouse.y >= start_button_position_y && event->mouse.y <= start_button_position_y + al_get_bitmap_height(start_button);

		if (is_x_mouse_in_start && is_y_mouse_in_start) {
			return true;
		}
	}

	return false;
}

bool is_how_to_play_button(ALLEGRO_EVENT* event) {
	if (!button_how_to_play) return false;

	if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event->mouse.button == 1) {
		bool is_x_mouse_in_how_to_play = event->mouse.x >= button_how_to_play_position_x && event->mouse.x <= button_how_to_play_position_x + al_get_bitmap_width(start_button);
		bool is_y_mouse_in_how_to_play = event->mouse.y >= button_how_to_play_position_y && event->mouse.y <= button_how_to_play_position_y + al_get_bitmap_height(start_button);

		if (is_x_mouse_in_how_to_play && is_y_mouse_in_how_to_play) {
			return true;
		}
	}

	return false;
}





void game_print() {
	al_set_target_bitmap(al_get_backbuffer(display));
	al_clear_to_color(al_map_rgb(0, 0, 0));

	load_game();

	int instantiated_blocks_lenght = get_array_size(game.instantiated_blocks);
	int template_blocks_lenght = get_array_size(game.current_stage.templates_blocks);

	// Exibição dos blocos 
	if (action_block_container_bitmap != NULL) {
		al_destroy_bitmap(action_block_container_bitmap);
		action_block_container_bitmap = NULL;
	}

	action_block_container_bitmap = al_create_bitmap(628, 468);

	al_set_target_bitmap(action_block_container_bitmap);
	al_clear_to_color(al_map_rgb(101, 85, 97));

	for (int i = 0; i < instantiated_blocks_lenght; i++) {
		ACTION_BLOCK* current_block = &game.instantiated_blocks[i];

		al_set_target_bitmap(action_block_container_bitmap);
		al_draw_bitmap(current_block->bitmap, current_block->position_x, current_block->position_y, 0);
	}

	al_set_target_bitmap(al_get_backbuffer(display));
	al_draw_bitmap(action_block_container_bitmap, ACTION_BLOCK_CONTAINER_POSITION_X, ACTION_BLOCK_CONTAINER_POSITION_Y, 0);

	if (game.current_stage.is_started) {
		stage_print(&game.current_stage);
	}

	al_flip_display();
}