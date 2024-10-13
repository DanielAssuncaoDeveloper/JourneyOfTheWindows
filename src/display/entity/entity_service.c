#include <stdlib.h>
#include "entity_service.h"
#include "../position/position_service.h";

/// <summary>
/// Cria um array de GAME_ENTITY com a quantidade de elementos espec�ficadas
/// </summary>
/// <param name="lentgh">Quantidade de elementos presente no Array</param>
/// <returns>Ponteiro do Array criado</returns>
GAME_ENTITY* get_pointer_to_array_entities(int length) {
    GAME_ENTITY* array_entity_pointer = calloc(length, sizeof(GAME_ENTITY));
    return array_entity_pointer;
}

/// <summary>
/// Cria a inst�ncia de um GAME_ENTITY preenchida com a refer�ncia da posi��o nas cordenadas especificadas
/// </summary>
/// <param name="grid_column_position">Posi��o na coluna da matriz</param>
/// <param name="grid_row_position">Posi��o na linha da matriz</param>
/// <param name="positions">Matriz de posi��es</param>
/// <returns>Inst�ncia de GAME_ENTITY</returns>
GAME_ENTITY init_entity(int grid_column_position, int grid_row_position, MAP_POSITION** positions)
{
    GAME_ENTITY entity;
    entity.position = &(positions[grid_column_position][grid_row_position]);

    return entity;
}
