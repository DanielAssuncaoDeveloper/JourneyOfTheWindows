#include "stageService.h"
#include "../map/mapService.h"
#include "../entity/entityService.h"
#include "../position/positionService.h"

struct Entity init_entity(int xPosition, int yPosition, struct Map* map) {
    struct Entity entity;

    for (int x = 0; x < map->width; x++) {
        if (x != xPosition)
            continue;

        for (int y = 0; y < map->height; y++) {
            if (y != yPosition)
                continue;

            entity.position = &(map->positions[x][y]);
            map->positions[x][y].entity = &entity;
        }
    }

    return entity;
}

struct Stage create_default_stage () {
    struct Stage stage;

    stage.map = map_init(10, 20);
    stage.entities = get_pointer_to_array_entities(5);

    stage.entities[0] = init_entity(1, 2, &stage.map);
    stage.entities[1] = init_entity(3, 5, &stage.map);
    stage.entities[2] = init_entity(4, 6, &stage.map);
    stage.entities[3] = init_entity(3, 5, &stage.map);
    stage.entities[4] = init_entity(2, 7, &stage.map);

    return stage;
}

struct Stage stage_init (enum StageType type) {
    struct Stage stage;
    switch (type) {
        case DEFAULT:
            stage = create_default_stage();
            break;
    }

    return stage;
}