#include <stdio.h>

#include "mapService.h"
#include "../position/positionService.h"

// Inicializa uma instância de Mapa, e preenche suas propriedades
struct Map map_init(int height, int width) {
    struct Map map;
    map.height = height;
    map.width = width;

    map.positions = create_matrix_position(height, width);
    return map;
}

void map_print(){
    struct Position** positions = map.positions;

    for (int i = 0; i < map.height; i++) {
        for (int j = 0; j < map.width; j++) {
            printf("| ^ ");
        }
        printf("|\n");
    }
}


