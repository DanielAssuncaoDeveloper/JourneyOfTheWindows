#include <stdlib.h>
#include "entity_service.h"
#include "../position/position_service.h";
#include "../map/map_service.h";
#include "../../utils/array_utils.h";
#include "../game/game_service.h"

/// <summary>
/// Cria um array de GAME_ENTITY com a quantidade de elementos específicadas
/// </summary>
/// <param name="lentgh">Quantidade de elementos presente no Array</param>
/// <returns>Ponteiro do Array criado</returns>
GAME_ENTITY* get_pointer_to_array_entities(int length) {
    GAME_ENTITY* array_entity_pointer = allocate_array(length, sizeof(GAME_ENTITY));
    return array_entity_pointer;
}

/// <summary>
/// Cria a instância de um GAME_ENTITY preenchida com a referência da posição nas cordenadas especificadas
/// </summary>
/// <param name="grid_column_position">Posição na coluna da matriz</param>
/// <param name="grid_row_position">Posição na linha da matriz</param>
/// <param name="positions">Matriz de posições</param>
/// <returns>Instância de GAME_ENTITY</returns>
GAME_ENTITY init_entity(int grid_column_position, int grid_row_position, MAP_POSITION** positions, ALLEGRO_BITMAP* image_bitmap, int entity_type)
{
    GAME_ENTITY entity;
    entity.position = &(positions[grid_column_position][grid_row_position]);
    entity.direction = ENTITY_DIRECTION_RIGHT;
    entity.bitmap = image_bitmap;
    entity.type = entity_type;
    entity.hide = false;

    return entity;
}

void entity_walk_to_position(GAME_ENTITY* entity, MAP_POSITION new_position) 
{
    MAP_POSITION* old_position = entity->position;
    GAME_MAP* map = old_position->map;

    entity->position = get_position(new_position.grid_column_position, new_position.grid_row_position);
    if (!(entity->position)) {
        game.player_colisided = true;

        entity->position = old_position;
        printf("\nPosition is not found, returning to old position.");
        return;
    }

    GAME_ENTITY** entities_on_position = get_entities_on_position(&game.current_stage, entity->position);
    int entities_found = get_array_size(entities_on_position);

    // Verificando se existe um componente na posição desejada
    for (int i = 0; i < entities_found; i++)
    {
        GAME_ENTITY* ptr_loop_entity = entities_on_position[i];

        if (ptr_loop_entity == NULL) continue;
        if (ptr_loop_entity->hide) continue;

        if (ptr_loop_entity->type == ENTITY_TYPE_COMPONENT) {
            game.player_colisided = true;

            entity->position = old_position;
            printf("\nPosition is blocked, returning to old position.");
            return;
        }
    }

}

void entity_change_direction(GAME_ENTITY* entity, int new_direction) 
{
    if (entity->direction + 1 != new_direction && entity->direction - 1 != new_direction) return;

    if (new_direction > ENTITY_DIRECTION_LEFT) new_direction = ENTITY_DIRECTION_UP;
    if (new_direction < ENTITY_DIRECTION_UP) new_direction = ENTITY_DIRECTION_LEFT;

    entity->direction = new_direction;
}
