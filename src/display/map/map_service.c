#include <stdio.h>
#include <stddef.h>
#include <allegro5/allegro.h>

#include "map_service.h"
#include "../position/position_service.h"
#include "../../configuration/game_configure.h"

GAME_MAP map_init(int vertical_blocks, int horizontal_blocks, ALLEGRO_BITMAP* stage_bitmap) {
    GAME_MAP map;

    // TODO: Definir a altura do mapa como a mesma do Stage
    map.bitmap = al_create_sub_bitmap(stage_bitmap, 0, 0, DISPLAY_WIDTH, 700);
    map.positions = create_matrix_position(vertical_blocks, horizontal_blocks, map.bitmap);
    map.horizontal_blocks = horizontal_blocks;
    map.vertical_blocks = vertical_blocks;
    map.name = "DEFAULT MAP";
    
    return map;
}


