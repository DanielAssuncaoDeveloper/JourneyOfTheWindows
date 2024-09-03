#ifndef STAGESERVICE_H
#define STAGESERVICE_H

#include "../map/mapService.h"

enum StageType {
    DEFAULT
};

struct Stage {
    char name[];
    enum StageType type;
    struct Map map;
    struct Entity entities[];
};

#endif //STAGESERVICE_H
