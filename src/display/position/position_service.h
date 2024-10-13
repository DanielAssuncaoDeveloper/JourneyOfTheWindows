#include <allegro5/allegro.h>

#ifndef POSITIONSERVICE_H
#define POSITIONSERVICE_H

typedef struct MAP_POSITION {
    int order;

    int grid_column_position;
    int grid_row_position;

    int x_position;
    int y_position;

    ALLEGRO_BITMAP* bitmap;
} MAP_POSITION;

MAP_POSITION** fill_matrix_positions_in_game_map(int height, int width, ALLEGRO_BITMAP* gamemap_bitmap);

#endif //POSITIONSERVICE_H
