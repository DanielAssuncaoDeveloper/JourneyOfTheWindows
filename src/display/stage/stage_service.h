#include <stdbool.h>
#include <allegro5/allegro.h>
#include "../map/map_service.h"
#include "../entity/entity_service.h"

#ifndef STAGESERVICE_H
#define STAGESERVICE_H

/// <summary>
/// Enum para as telas do game
/// </summary>
enum GAME_STAGE_TYPE {
    STAGETYPE_DEFAULT
};


/// <summary>
/// Estrutura de fase que contém as principais entidades do game
/// </summary>
typedef struct GAME_STAGE {
    char* name;
    bool is_started;
    enum GAME_STAGE_TYPE type;
    GAME_MAP map;
    GAME_ENTITY* entities;
    ALLEGRO_BITMAP* bitmap; 
} GAME_STAGE;


GAME_STAGE stage_init(enum GAME_STAGE_TYPE type);

void stage_print(GAME_STAGE* stage);

#endif //STAGESERVICE_H
