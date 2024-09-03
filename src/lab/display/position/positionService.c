#include "positionService.h"
#include <stdlib.h>

// Cria uma matriz de posições e retorna um "pointer-to-pointer" das posições adicionadas.
struct Position** create_matrix_position(int height, int width) {
    // Alocando espaço na memória para a coluna da matriz
    struct Position** positions = malloc(height * sizeof(struct Position*));

    for (int i = 0; i < height; i++) {
        // Direcionando uma linha da matriz para cada ponteiro da coluna
        positions[i] = (struct Position *) malloc(width * sizeof(struct Position*));

        for (int j = 0; j < width; j++) {
            positions[i][j].xPosition = i;
            positions[i][j].yPosition  = j;
        }
    }

    return positions;
}