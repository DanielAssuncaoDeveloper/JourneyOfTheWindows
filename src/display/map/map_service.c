#include <stdio.h>
#include <stddef.h>
#include <allegro5/allegro.h>

#include "map_service.h"
#include "../position/position_service.h"
#include "../../configuration/game_configure.h"

/// <summary>
/// Faz a inicializa��o da inst�ncia de um mapa
/// </summary>
/// <param name="height_blocks">Quantidade de blocos de altura</param>
/// <param name="width_blocks">Quantidade de blocks de largura</param>
/// <param name="stage_bitmap">Bitmap da fase</param>
/// <returns>Inst�ncia de um mapa</returns>
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
/// Preenche uma matriz de MAP_POSITION na inst�ncia de GAME_MAP informada.
/// </summary>
/// <param name="map">Inst�ncia do mapa onde ser� referenciada as posi��es</param>
void fill_matrix_positions_in_game_map(GAME_MAP map) {
    // Alocando espa�o na mem�ria para uma coluna da matriz
    MAP_POSITION** positions = (MAP_POSITION*)calloc(map.height_blocks, sizeof(MAP_POSITION*));

    // Respons�veis pela manipula��o da posi��o GR�FICA dos bitmaps
    int space_between_blocks = 10;
    int padding_in_map = 10;

    // Repons�vel pela identifica��o e ordena��o l�gica de cada posi��o
    int order_position = 0;

    for (int i = 0; i < map.height_blocks; i++) {
        // Para cada elemento do Array de coluna, faz a cria��o de um novo array, e o define como elemento
        positions[i] = (MAP_POSITION*)calloc(map.width_blocks, sizeof(MAP_POSITION));

        // Para cada elemento da Linha da matriz, instancia um MAP_POSITION e atribui a posi��o da itera��o
        for (int j = 0; j < map.width_blocks; j++) {
            MAP_POSITION position;

            // Definindo a posi��o GR�FICA de cada bitmap
            int x_position = j * BLOCK_WIDTH + (space_between_blocks * j) + padding_in_map;
            int y_position = i * BLOCK_HEIGHT + (space_between_blocks * i) + padding_in_map;

            // Criando um bitmap de posi��o, como "filho" do bitmap do Mapa nas posi��es especificadas
            ALLEGRO_BITMAP* position_bitmap = al_create_sub_bitmap(map.bitmap, x_position, y_position, BLOCK_WIDTH, BLOCK_HEIGHT);

            // Atribuindo os valores nas propriedades de MAP_POSITION
            position.bitmap = position_bitmap;
            position.x_position = x_position;
            position.y_position = y_position;

            position.grid_column_position = i;
            position.grid_row_position = j;
            position.order = order_position++;

            // Atribuindo a posi��o criada como elemento da matriz
            positions[i][j] = position;
        }
    }

    // Definindo a matriz de posi��es na inst�ncia de GAME_MAP
    map.positions = positions;
}