#include <stdbool.h>
#include <allegro5/allegro.h>
#include "../map/map_service.h"
#include "../entity/entity_service.h"
#include "../action_block/action_blocks_service.h"

#ifndef STAGESERVICE_H
#define STAGESERVICE_H

/// <summary>
/// Enum para as telas do game
/// </summary>
enum GAME_STAGE_TYPE {
    STAGETYPE_COLLECT_FOLDERS,
    STAGETYPE_COLLECT_DRIVERS,
    STAGETYPE_COLLECT_THERMAL_NOODLES
};

/// <summary>
/// Estrutura de fase que contém as principais entidades do game
/// </summary>
typedef struct GAME_STAGE {
    char* name;
    bool is_started;
    int items_to_collect;

    enum GAME_STAGE_TYPE type;
    GAME_MAP map;
    GAME_ENTITY* entities;
    ACTION_BLOCK* templates_blocks;
    ALLEGRO_BITMAP* bitmap;
} GAME_STAGE;


extern bool how_to_play_active;

GAME_STAGE stage_init(enum GAME_STAGE_TYPE type);
GAME_ENTITY** get_entities_on_position(GAME_STAGE* stage, MAP_POSITION* position);
ACTION_BLOCK* action_blocks_init(ALLEGRO_BITMAP* stage_bitmap, ACTION_TYPE action_type_list[]);

void on_close_popup_how_to_play(ALLEGRO_EVENT* event, bool* redraw);
void stage_print(GAME_STAGE* stage);

#endif //STAGESERVICE_H
