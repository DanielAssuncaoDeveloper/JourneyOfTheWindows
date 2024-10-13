#include <stdlib.h>

#include "position_service.h"
#include "../../configuration/game_configure.h"
#include "../map/map_service.h"

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