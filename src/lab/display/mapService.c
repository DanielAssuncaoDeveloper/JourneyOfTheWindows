#include <stdlib.h>
#include <stdio.h>

#include "mapService.h"
#include "structs/Map.h"
#include "structs/Entity.h"

struct Map map;

struct Position** map_create(int height, int width, struct EntityMapper* mapper) {
    struct Position** positions = (struct Position**) malloc(height * sizeof(struct Position*));
    //struct Entity* entities = malloc(sizeof(mapper) / sizeof(struct Entity) );

    for (int i = 0; i < height; i++) {
        positions[i] = (struct Position *) malloc(width * sizeof(struct Position*));

        for (int j = 0; j < width; j++) {
            positions[i][j].xPosition = i;
            positions[i][j].yPosition  = j;
        }
    }

    printf("%l", sizeof(positions));
    return positions;
}

void map_init(int height, int width, struct EntityMapper mapper[]) {
    map.height = height;
    map.width = width;

    map.positions = map_create(height, width, mapper);
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


