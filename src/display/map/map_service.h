#include <allegro5/allegro.h>
 
#ifndef MAPSERVICE_H
#define MAPSERVICE_H


typedef struct MAP_POSITION MAP_POSITION;
typedef struct GAME_MAP GAME_MAP;

struct GAME_MAP {
    char* name;
    int height_blocks;
    int width_blocks;
    MAP_POSITION** positions;
    ALLEGRO_BITMAP* bitmap;
};

struct MAP_POSITION {
    int id;

    int grid_column_position;
    int grid_row_position;

    int x_position;
    int y_position;

    GAME_MAP* map;
    ALLEGRO_BITMAP* bitmap;
};

GAME_MAP map_init(int height_blocks, int width_blocks, ALLEGRO_BITMAP* stage_bitmap, int stage_type);
MAP_POSITION* get_position(int column_position, int row_position);

void fill_matrix_positions_in_game_map(GAME_MAP* map);

extern GAME_MAP current_map;

#endif //MAPSERVICE_H
