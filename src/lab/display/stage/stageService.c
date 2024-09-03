#include "stageService.h"
#include "../map/mapService.h"

struct Stage create_default_stage () {
    struct Stage stage;

    stage.map = map_init(10, 20);

    stage.entities =

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