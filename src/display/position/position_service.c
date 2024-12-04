#include <stdlib.h>

#include "position_service.h"
#include "../../configuration/game_configure.h"
#include "../map/map_service.h"
#include "../../utils/array_utils.h"

/// <summary>
/// Obtem a posição do mapa nas cordenadas especificadas
/// </summary>
/// <param name="column_position">Posição da coluna</param>
/// <param name="row_position">Posição da linha</param>
/// <param name="map">Referência do mapa</param>
/// <returns>Ponteiro de MAP_POSITION</returns>
MAP_POSITION* get_position(int column_position, int row_position) {

    if (column_position >= current_map.height_blocks || column_position < 0) return NULL;
    if (row_position >= current_map.width_blocks || row_position < 0) return NULL;

    return &(current_map.positions[column_position][row_position]);
}
