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
    
    fill_matrix_positions_in_game_map(map);
    return map;
}


/// <summary>
/// Preenche uma matriz de MAP_POSITION na instância de GAME_MAP informada.
/// </summary>
/// <param name="map">Instância do mapa onde será referenciada as posições</param>
void fill_matrix_positions_in_game_map(GAME_MAP map) {
    // Alocando espaço na memória para uma coluna da matriz
    MAP_POSITION** positions = (MAP_POSITION*)calloc(map.height_blocks, sizeof(MAP_POSITION*));

    // Responsáveis pela manipulação da posição GRÁFICA dos bitmaps
    int space_between_blocks = 10;
    int padding_in_map = 10;

    // Reponsável pela identificação e ordenação lógica de cada posição
    int order_position = 0;

    for (int i = 0; i < map.height_blocks; i++) {
        // Para cada elemento do Array de coluna, faz a criação de um novo array, e o define como elemento
        positions[i] = (MAP_POSITION*)calloc(map.width_blocks, sizeof(MAP_POSITION));

        // Para cada elemento da Linha da matriz, instancia um MAP_POSITION e atribui a posição da iteração
        for (int j = 0; j < map.width_blocks; j++) {
            MAP_POSITION position;

            // Definindo a posição GRÁFICA de cada bitmap
            int x_position = j * BLOCK_WIDTH + (space_between_blocks * j) + padding_in_map;
            int y_position = i * BLOCK_HEIGHT + (space_between_blocks * i) + padding_in_map;

            // Criando um bitmap de posição, como "filho" do bitmap do Mapa nas posições especificadas
            ALLEGRO_BITMAP* position_bitmap = al_create_sub_bitmap(map.bitmap, x_position, y_position, BLOCK_WIDTH, BLOCK_HEIGHT);

            // Atribuindo os valores nas propriedades de MAP_POSITION
            position.bitmap = position_bitmap;
            position.x_position = x_position;
            position.y_position = y_position;

            position.grid_column_position = i;
            position.grid_row_position = j;
            position.order = order_position++;

            // Atribuindo a posição criada como elemento da matriz
            positions[i][j] = position;
        }
    }

    // Definindo a matriz de posições na instância de GAME_MAP
    map.positions = positions;
}