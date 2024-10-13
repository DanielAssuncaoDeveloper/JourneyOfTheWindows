#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

#include "stage_service.h"
#include "../map/map_service.h"
#include "../entity/entity_service.h"
#include "../position/position_service.h"
#include "../../configuration/game_configure.h"

/// <summary>
/// Faz a criação da fase padrão do game
/// </summary>
/// <returns>A instância de um GAME_STAGE</returns>
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

/// <summary>
/// Com base no tipo de fase, realiza a instância do objeto respectivo a fase
/// </summary>
/// <param name="type">Tipo de fase que será instânciada</param>
/// <returns>Instância da fase</returns>
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

/// <summary>
/// Com base em uma posição da fase, informada, verifica se existe alguma entidade nela
/// </summary>
/// <param name="stage">Fase respectiva</param>
/// <param name="position">Posição que deseja verificar</param>
/// <returns>Caso encontre alguma entidade nesta posição, retorna-a</returns>
GAME_ENTITY* get_entity_on_position(GAME_STAGE* stage ,MAP_POSITION* position) {
    GAME_ENTITY* entity_return = NULL;
    // Obtendo o tamanho do array de entidades
    int entities_lenght = sizeof(stage->entities) / sizeof(GAME_ENTITY*);
    
    for (int i = 0; i < entities_lenght; i++)
    {
        // Obtendo a entidade na posição de iteração
        GAME_ENTITY* entity = &(stage->entities[i]);

        // Verificando se a ordem da posição informada, é a mesma presente na posição da entidade da iteração
        if (position->order == entity->position->order)
        {
            // Preenche a entidade para retorno e para e execução do for
            entity_return = entity;
            break;
        }
    }

    return entity_return;
}

/// <summary>
/// Faz a exibição da fase no display
/// </summary>
/// <param name="stage">Ponteiro de GAME_STAGE que será exibido</param>
void stage_print(GAME_STAGE* stage) {
    GAME_MAP* map = &(stage->map);

    // Coloca o bitmap do mapa em evidência, e adiciona uma coloração a ele
    al_set_target_bitmap(map->bitmap);
    al_clear_to_color(al_map_rgb(255, 255, 255));

    // Percorrendo a matriz de posições
    MAP_POSITION** positions = map->positions;
    for (int i = 0; i < map->height_blocks; i++)
    {
        for (int j = 0; j < map->width_blocks; j++)
        {
            // Pegando a posição atual e definindo uma coloração para o seu bitmap
            MAP_POSITION position = positions[i][j];
            al_set_target_bitmap(position.bitmap);
            al_clear_to_color(al_map_rgb(255, 0, 0));

            // Verificando se existe alguma entidade na posição da iteração atual
            // caso exita, escreve sua representação no bloco respectivo
            GAME_ENTITY* entity = get_entity_on_position(stage, &position);
            if (entity) 
            {
                al_draw_text(font, al_map_rgb(255, 255, 255), BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2, 0, "W");
            }
        }
    }

    // Coloca o bitmap do display principal em evidência
    al_set_target_bitmap(al_get_backbuffer(display));

    // Escreve o bitmap da fase no display e troca a exbição dos bitmaps no display
    al_draw_bitmap(stage->bitmap, 0, 0, 0);
    al_flip_display();
}