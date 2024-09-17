#include <stdlib.h>

#include "position_service.h"
#include "../../configuration/game_configure.h"
#include "../map/map_service.h"

MAP_POSITION** create_matrix_position(int height, int width, ALLEGRO_BITMAP* gamemap_bitmap) {
    // Alocando espaço na memória para a coluna da matriz
    MAP_POSITION** positions = (MAP_POSITION*) calloc(height, sizeof(MAP_POSITION*));
    int space_between_blocks = 10;
    int padding_in_map = 10;
    int id = 0;

    for (int i = 0; i < height; i++) {
        // Direcionando uma linha da matriz para cada ponteiro da coluna
        positions[i] = (MAP_POSITION*)calloc(width, sizeof(MAP_POSITION));

        for (int j = 0; j < width; j++) {
            MAP_POSITION position;

            int x_position = j * BLOCK_WIDTH + (space_between_blocks * j) + padding_in_map;
            int y_position = i * BLOCK_HEIGHT + (space_between_blocks * i) + padding_in_map;
            ALLEGRO_BITMAP* position_bitmap = al_create_sub_bitmap(gamemap_bitmap, x_position, y_position, BLOCK_WIDTH, BLOCK_HEIGHT);

            positions[i][j].bitmap = position_bitmap;
            positions[i][j].x_position = x_position;
            positions[i][j].y_position = y_position;

            positions[i][j].grid_column_position = i;
            positions[i][j].grid_row_position = j;
            positions[i][j].id = id++;
        }
    }

    return positions;
}


MAP_POSITION* get_position(int column_position, int row_position, GAME_MAP* map) {
    return &(map->positions[column_position][row_position]);
}