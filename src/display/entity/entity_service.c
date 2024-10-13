#include <stdlib.h>
#include "entity_service.h"
#include "../position/position_service.h";

/// <summary>
/// Cria um array de GAME_ENTITY com a quantidade de elementos específicadas
/// </summary>
/// <param name="lentgh">Quantidade de elementos presente no Array</param>
/// <returns>Ponteiro do Array criado</returns>
GAME_ENTITY* get_pointer_to_array_entities(int lentgh) {
    GAME_ENTITY* array_entity_pointer = calloc(lentgh, sizeof(GAME_ENTITY));
    return array_entity_pointer;
}

/// <summary>
/// Cria a instância de um GAME_ENTITY preenchida com a referência da posição nas cordenadas especificadas
/// </summary>
/// <param name="grid_column_position"></param>
/// <param name="grid_row_position"></param>
/// <param name="positions"></param>
/// <returns></returns>
GAME_ENTITY init_entity(int grid_column_position, int grid_row_position, MAP_POSITION** positions)
{
    GAME_ENTITY entity;
    entity.position = &(positions[grid_column_position][grid_row_position]);

    return entity;
}
