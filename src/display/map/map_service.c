#include <stdio.h>
#include <stddef.h>
#include <allegro5/allegro.h>

#include "map_service.h"
#include "../position/position_service.h"
#include "../../configuration/game_configure.h"

/// <summary>
/// Faz a inicialização da instância de um mapa
/// </summary>
/// <param name="height_blocks">Quantidade de blocos de altura</param>
/// <param name="width_blocks">Quantidade de blocks de largura</param>
/// <param name="stage_bitmap">Bitmap da fase</param>
/// <returns>Instância de um mapa</returns>
GAME_MAP map_init(int height_blocks, int width_blocks, ALLEGRO_BITMAP* stage_bitmap) {
    GAME_MAP map;

    map.bitmap = al_create_sub_bitmap(stage_bitmap, 0, 0, DISPLAY_WIDTH, 700);
    map.width_blocks = width_blocks;
    map.height_blocks = height_blocks;
    map.name = "DEFAULT MAP";
    
    map.positions = fill_matrix_positions_in_game_map(height_blocks, width_blocks, map.bitmap);
    return map;
}


