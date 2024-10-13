#include <stdlib.h>

#include "position_service.h"
#include "../../configuration/game_configure.h"
#include "../map/map_service.h"

/// <summary>
/// Preenche uma matriz de MAP_POSITION na instância de GAME_MAP informada.
/// </summary>
/// <param name="map">Instância do mapa onde será referenciada as posições</param>
void fill_matrix_positions_in_game_map(GAME_MAP map) {
    // Alocando espaço na memória para uma coluna da matriz
    MAP_POSITION** positions = (MAP_POSITION*) calloc(map.height_blocks, sizeof(MAP_POSITION*));
    
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

/// <summary>
/// Obtem a posição do mapa nas cordenadas especificadas
/// </summary>
/// <param name="column_position">Posição da coluna</param>
/// <param name="row_position">Posição da linha</param>
/// <param name="map">Referência do mapa</param>
/// <returns></returns>
MAP_POSITION* get_position(int column_position, int row_position, GAME_MAP* map) {
    return &(map->positions[column_position][row_position]);
}