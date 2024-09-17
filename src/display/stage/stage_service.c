#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

#include "stage_service.h"
#include "../map/map_service.h"
#include "../entity/entity_service.h"
#include "../position/position_service.h"
#include "../../configuration/game_configure.h"

GAME_STAGE create_default_stage () {
    struct GAME_STAGE stage;

    stage.bitmap = al_create_bitmap(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    stage.map = map_init(5, 22, stage.bitmap);

    stage.name = "DEFAULT STAGE";
    stage.entities = get_pointer_to_array_entities(1);
    stage.entities[0] = init_entity(0, 0, stage.map.positions);

    al_set_target_bitmap(stage.bitmap);
    al_clear_to_color(al_map_rgb(255, 255, 255));

    return stage;
}

GAME_STAGE stage_init (enum GAME_STAGE_TYPE type) {
    GAME_STAGE stage;

    switch (type) {
        case STAGETYPE_DEFAULT:
            stage = create_default_stage();
            break;
    }

    stage.is_started = true;
    return stage;
}

GAME_ENTITY* get_entity_on_position(GAME_STAGE* stage ,MAP_POSITION* position) {
    GAME_ENTITY* entity_return = NULL;
    int entities_lenght = sizeof(stage->entities) / sizeof(GAME_ENTITY*);
    
    for (int i = 0; i < entities_lenght; i++)
    {
        GAME_ENTITY* entity = &(stage->entities[i]);

        if (position->id == entity->position->id)
        {
            entity_return = &(stage->entities[i]);
            break;
        }
    }

    return entity_return;
}


void stage_print(GAME_STAGE* stage) {
    GAME_MAP* map = &(stage->map);

    al_set_target_bitmap(map->bitmap);
    al_clear_to_color(al_map_rgb(255, 255, 255));

    MAP_POSITION** positions = map->positions;

    for (int i = 0; i < map->vertical_blocks; i++)
    {
        for (int j = 0; j < map->horizontal_blocks; j++)
        {
            MAP_POSITION position = positions[i][j];

            al_set_target_bitmap(position.bitmap);
            al_clear_to_color(al_map_rgb(255, 0, 0));

            GAME_ENTITY* entity = get_entity_on_position(stage, &position);
            if (entity) 
            {
                al_draw_text(font, al_map_rgb(255, 255, 255), BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2, 0, "W");
            }

            // TODO: RESOLVE A IMAGE LOAD
            
            //ALLEGRO_BITMAP* tmp_windows_bitmap = al_create_sub_bitmap(position.bitmap, BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2, BLOCK_HEIGHT, BLOCK_WIDTH);
            //al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
            //ALLEGRO_BITMAP* image_windows_bitmap = al_load_bitmap("windows-profile.png");
            //al_set_target_bitmap(tmp_windows_bitmap);
            //al_draw_bitmap(image_windows_bitmap, 0, 0, 0);
        }
    }

    al_set_target_bitmap(al_get_backbuffer(display));

    al_draw_bitmap(stage->bitmap, 0, 0, 0);
    al_flip_display();
}