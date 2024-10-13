#include <allegro5/allegro.h>
#include "../position/position_service.h"

#ifndef MAPSERVICE_H
#define MAPSERVICE_H

typedef struct GAME_MAP {
    char* name;
    int height_blocks;
    int width_blocks;
    MAP_POSITION** positions;
    ALLEGRO_BITMAP* bitmap;
} GAME_MAP;
	
GAME_MAP map_init(int height, int width, ALLEGRO_BITMAP* stage_bitmap);

MAP_POSITION* get_position(int column_position, int row_position, GAME_MAP* map);

void fill_matrix_positions_in_game_map(GAME_MAP map);

#endif //MAPSERVICE_H
