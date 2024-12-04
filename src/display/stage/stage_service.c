#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

#include "stage_service.h"
#include "../../configuration/game_configure.h"
#include "../map/map_service.h"
#include "../entity/entity_service.h"
#include "../position/position_service.h"
#include "../../configuration/game_configure.h"
#include "../../utils/array_utils.h"

ALLEGRO_BITMAP* instruction_section = NULL;

bool how_to_play_active = false;

int button_close_popup_how_to_play_position_x = 0;
int button_close_popup_how_to_play_position_y = 0;
ALLEGRO_BITMAP* button_close_how_to_play = NULL;


void on_close_popup_how_to_play(ALLEGRO_EVENT* event, bool* redraw) {
    if (!button_close_how_to_play || !how_to_play_active) return;

    if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event->mouse.button == 1) {
        bool is_x_mouse_in_how_to_play = event->mouse.x >= button_close_popup_how_to_play_position_x && event->mouse.x <= button_close_popup_how_to_play_position_x + al_get_bitmap_width(button_close_how_to_play);
        bool is_y_mouse_in_how_to_play = event->mouse.y >= button_close_popup_how_to_play_position_y && event->mouse.y <= button_close_popup_how_to_play_position_y + al_get_bitmap_height(button_close_how_to_play);

        if (is_x_mouse_in_how_to_play && is_y_mouse_in_how_to_play) {
            how_to_play_active = false;
            *redraw = true;
        }
    }
}


/// <summary>
/// Faz a criação da fase padrão do game
/// </summary>
/// <returns>A instância de um GAME_STAGE</returns>
GAME_STAGE create_default_stage () {
    GAME_STAGE stage;

    stage.bitmap = al_create_bitmap(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    stage.map = map_init(15, 20, stage.bitmap, STAGETYPE_COLLECT_FOLDERS);

    // ISSO É FULL GO-HORSE NA VEIA
    current_map = stage.map; // TODO: REMOVER E ENTENDER O POR QUE DA POSIÇÃO DA ENTIDADE PERDER A REFERENCIA COM O MAPA

    stage.name = "DEFAULT STAGE";
    stage.entities = get_pointer_to_array_entities(47);
    
    instruction_section = al_load_bitmap("instruction_stage_one.png");

    // Player init
    ALLEGRO_BITMAP* player_bitmap = al_load_bitmap("player_windows_right.png");
    stage.entities[0] = init_entity(2, 3, stage.map.positions, player_bitmap, ENTITY_TYPE_PLAYER);

    // SSD Components init
    ALLEGRO_BITMAP* sdd_component_part_one = al_load_bitmap("ssd_component_part_one.png");
    ALLEGRO_BITMAP* sdd_component_part_two = al_load_bitmap("ssd_component_part_two.png");
    ALLEGRO_BITMAP* sdd_component_part_three = al_load_bitmap("ssd_component_part_three.png");
    ALLEGRO_BITMAP* sdd_component_part_four = al_load_bitmap("ssd_component_part_four.png");

    stage.entities[1] = init_entity(3, 4, stage.map.positions, sdd_component_part_one, ENTITY_TYPE_COMPONENT);
    stage.entities[2] = init_entity(3, 5, stage.map.positions, sdd_component_part_two, ENTITY_TYPE_COMPONENT);
    stage.entities[3] = init_entity(3, 6, stage.map.positions, sdd_component_part_three, ENTITY_TYPE_COMPONENT);
    stage.entities[4] = init_entity(3, 7, stage.map.positions, sdd_component_part_four, ENTITY_TYPE_COMPONENT);

    stage.entities[5] = init_entity(5, 4, stage.map.positions, sdd_component_part_one, ENTITY_TYPE_COMPONENT);
    stage.entities[6] = init_entity(5, 5, stage.map.positions, sdd_component_part_two, ENTITY_TYPE_COMPONENT);
    stage.entities[7] = init_entity(5, 6, stage.map.positions, sdd_component_part_three, ENTITY_TYPE_COMPONENT);
    stage.entities[8] = init_entity(5, 7, stage.map.positions, sdd_component_part_four, ENTITY_TYPE_COMPONENT);

    // Screw components init
    ALLEGRO_BITMAP* screw_component = al_load_bitmap("screw_component.png");

    stage.entities[9] = init_entity(1, 1, stage.map.positions, screw_component, ENTITY_TYPE_COMPONENT);
    stage.entities[10] = init_entity(13, 1, stage.map.positions, screw_component, ENTITY_TYPE_COMPONENT);
    stage.entities[11] = init_entity(1, 18, stage.map.positions, screw_component, ENTITY_TYPE_COMPONENT);
    stage.entities[12] = init_entity(13, 18, stage.map.positions, screw_component, ENTITY_TYPE_COMPONENT);
    
    // Colored batery components
    ALLEGRO_BITMAP* colered_batery_component = al_load_bitmap("colered_batery_component.png");

    stage.entities[13] = init_entity(2, 9, stage.map.positions, colered_batery_component, ENTITY_TYPE_COMPONENT);
    stage.entities[14] = init_entity(2, 10, stage.map.positions, colered_batery_component, ENTITY_TYPE_COMPONENT);

    // Memory RAM Components  
    ALLEGRO_BITMAP* memory_ram_component_part_one = al_load_bitmap("memory_ram_component_part_one.png");
    ALLEGRO_BITMAP* memory_ram_component_part_two = al_load_bitmap("memory_ram_component_part_two.png");
    ALLEGRO_BITMAP* memory_ram_component_part_three = al_load_bitmap("memory_ram_component_part_three.png");

    stage.entities[15] = init_entity(2, 13, stage.map.positions, memory_ram_component_part_one, ENTITY_TYPE_COMPONENT);
    stage.entities[16] = init_entity(3, 13, stage.map.positions, memory_ram_component_part_two, ENTITY_TYPE_COMPONENT);
    stage.entities[17] = init_entity(4, 13, stage.map.positions, memory_ram_component_part_three, ENTITY_TYPE_COMPONENT);
    
    stage.entities[18] = init_entity(5, 13, stage.map.positions, memory_ram_component_part_one, ENTITY_TYPE_COMPONENT);
    stage.entities[19] = init_entity(6, 13, stage.map.positions, memory_ram_component_part_two, ENTITY_TYPE_COMPONENT);
    stage.entities[20] = init_entity(7, 13, stage.map.positions, memory_ram_component_part_three, ENTITY_TYPE_COMPONENT);

    stage.entities[21] = init_entity(2, 15, stage.map.positions, memory_ram_component_part_one, ENTITY_TYPE_COMPONENT);
    stage.entities[22] = init_entity(3, 15, stage.map.positions, memory_ram_component_part_two, ENTITY_TYPE_COMPONENT);
    stage.entities[23] = init_entity(4, 15, stage.map.positions, memory_ram_component_part_three, ENTITY_TYPE_COMPONENT);
                                        
    stage.entities[24] = init_entity(5, 15, stage.map.positions, memory_ram_component_part_one, ENTITY_TYPE_COMPONENT);
    stage.entities[25] = init_entity(6, 15, stage.map.positions, memory_ram_component_part_two, ENTITY_TYPE_COMPONENT);
    stage.entities[26] = init_entity(7, 15, stage.map.positions, memory_ram_component_part_three, ENTITY_TYPE_COMPONENT);

    // CPU Components
    ALLEGRO_BITMAP* cpu_component_part_one = al_load_bitmap("cpu_component_part_one.png");
    ALLEGRO_BITMAP* cpu_component_part_two = al_load_bitmap("cpu_component_part_two.png");
    ALLEGRO_BITMAP* cpu_component_part_three = al_load_bitmap("cpu_component_part_three.png");
    ALLEGRO_BITMAP* cpu_component_part_four = al_load_bitmap("cpu_component_part_four.png");

    stage.entities[27] = init_entity(8, 9, stage.map.positions, cpu_component_part_one, ENTITY_TYPE_COMPONENT);
    stage.entities[28] = init_entity(8, 10, stage.map.positions, cpu_component_part_two, ENTITY_TYPE_COMPONENT);
    stage.entities[29] = init_entity(9, 9, stage.map.positions, cpu_component_part_three, ENTITY_TYPE_COMPONENT);
    stage.entities[30] = init_entity(9, 10, stage.map.positions, cpu_component_part_four, ENTITY_TYPE_COMPONENT);

    // Microchip Component
    ALLEGRO_BITMAP* microchip_component = al_load_bitmap("microchip_component.png");

    stage.entities[31] = init_entity(12, 10, stage.map.positions, microchip_component, ENTITY_TYPE_COMPONENT);
    stage.entities[32] = init_entity(12, 12, stage.map.positions, microchip_component, ENTITY_TYPE_COMPONENT);
    stage.entities[33] = init_entity(12, 14, stage.map.positions, microchip_component, ENTITY_TYPE_COMPONENT);

    // Cabe components
    ALLEGRO_BITMAP* horizontal_cabe_component = al_load_bitmap("horizontal_cabe_component.png");
    ALLEGRO_BITMAP* head_cabe_component = al_load_bitmap("head_cabe_component.png");
    ALLEGRO_BITMAP* turn_cabe_component = al_load_bitmap("turn_cabe_component.png");
    ALLEGRO_BITMAP* vertical_cabe_component = al_load_bitmap("vertical_cabe_component.png");

    stage.entities[34] = init_entity(7, 3, stage.map.positions, head_cabe_component, ENTITY_TYPE_COMPONENT);
    stage.entities[35] = init_entity(8, 3, stage.map.positions, vertical_cabe_component, ENTITY_TYPE_COMPONENT);
    stage.entities[36] = init_entity(9, 3, stage.map.positions, vertical_cabe_component, ENTITY_TYPE_COMPONENT);
    stage.entities[37] = init_entity(10, 3, stage.map.positions, vertical_cabe_component, ENTITY_TYPE_COMPONENT);
    stage.entities[38] = init_entity(11, 3, stage.map.positions, turn_cabe_component, ENTITY_TYPE_COMPONENT);
    stage.entities[39] = init_entity(11, 4, stage.map.positions, horizontal_cabe_component, ENTITY_TYPE_COMPONENT);
    stage.entities[40] = init_entity(11, 5, stage.map.positions, horizontal_cabe_component, ENTITY_TYPE_COMPONENT);
    stage.entities[41] = init_entity(11, 6, stage.map.positions, head_cabe_component, ENTITY_TYPE_COMPONENT);

    // Collectables init
    ALLEGRO_BITMAP* collectable_folder_bitmap = al_load_bitmap("collectable_folder.png");
    
    stage.entities[42] = init_entity(4, 3, stage.map.positions, collectable_folder_bitmap, ENTITY_TYPE_COLLECTABLE);
    stage.entities[43] = init_entity(4, 7, stage.map.positions, collectable_folder_bitmap, ENTITY_TYPE_COLLECTABLE);
    stage.entities[44] = init_entity(2, 8, stage.map.positions, collectable_folder_bitmap, ENTITY_TYPE_COLLECTABLE);
    stage.entities[45] = init_entity(2, 5, stage.map.positions, collectable_folder_bitmap, ENTITY_TYPE_COLLECTABLE);
    stage.entities[46] = init_entity(2, 14, stage.map.positions, collectable_folder_bitmap, ENTITY_TYPE_COLLECTABLE);

    ACTION_TYPE block_types[] = { ACTION_WALK, ACTION_ROTATE_CLOCKWISE, ACTION_ROTATE_COUNTERCLOCKWISE, ACTION_COLLECT };
    stage.templates_blocks = action_blocks_init(stage.bitmap, &block_types);
    stage.items_to_collect = 5;

    return stage;
}

GAME_STAGE create_drivers_stage() {
    GAME_STAGE stage;

    stage.bitmap = al_create_bitmap(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    stage.map = map_init(15, 20, stage.bitmap, STAGETYPE_COLLECT_DRIVERS);

    current_map = stage.map;

    stage.name = "DRIVERS STAGE";
    stage.entities = get_pointer_to_array_entities(68);

    instruction_section = al_load_bitmap("instruction_stage_two.png");

    // Player init
    ALLEGRO_BITMAP* player_bitmap = al_load_bitmap("player_windows_right.png");
    stage.entities[0] = init_entity(3, 14, stage.map.positions, player_bitmap, ENTITY_TYPE_PLAYER);
    stage.entities[0].direction = ENTITY_DIRECTION_LEFT;

    // Screw components init
    ALLEGRO_BITMAP* screw_component = al_load_bitmap("screw_component.png");

    stage.entities[1] = init_entity(1, 1, stage.map.positions, screw_component, ENTITY_TYPE_COMPONENT);
    stage.entities[2] = init_entity(13, 1, stage.map.positions, screw_component, ENTITY_TYPE_COMPONENT);
    stage.entities[3] = init_entity(1, 18, stage.map.positions, screw_component, ENTITY_TYPE_COMPONENT);
    stage.entities[4] = init_entity(13, 18, stage.map.positions, screw_component, ENTITY_TYPE_COMPONENT);

    // SSD Components init
    ALLEGRO_BITMAP* sdd_component_part_one = al_load_bitmap("ssd_component_part_one.png");
    ALLEGRO_BITMAP* sdd_component_part_two = al_load_bitmap("ssd_component_part_two.png");
    ALLEGRO_BITMAP* sdd_component_part_three = al_load_bitmap("ssd_component_part_three.png");
    ALLEGRO_BITMAP* sdd_component_part_four = al_load_bitmap("ssd_component_part_four.png");

    stage.entities[5] = init_entity(9, 4, stage.map.positions, sdd_component_part_one, ENTITY_TYPE_COMPONENT);
    stage.entities[6] = init_entity(9, 5, stage.map.positions, sdd_component_part_two, ENTITY_TYPE_COMPONENT);
    stage.entities[7] = init_entity(9, 6, stage.map.positions, sdd_component_part_three, ENTITY_TYPE_COMPONENT);
    stage.entities[8] = init_entity(9, 7, stage.map.positions, sdd_component_part_four, ENTITY_TYPE_COMPONENT);

    stage.entities[9] = init_entity(11, 4, stage.map.positions, sdd_component_part_one, ENTITY_TYPE_COMPONENT);
    stage.entities[10] = init_entity(11, 5, stage.map.positions, sdd_component_part_two, ENTITY_TYPE_COMPONENT);
    stage.entities[11] = init_entity(11, 6, stage.map.positions, sdd_component_part_three, ENTITY_TYPE_COMPONENT);
    stage.entities[12] = init_entity(11, 7, stage.map.positions, sdd_component_part_four, ENTITY_TYPE_COMPONENT);
    
    // Microchip Component
    ALLEGRO_BITMAP* microchip_component = al_load_bitmap("microchip_component.png");

    stage.entities[13] = init_entity(9, 3, stage.map.positions, microchip_component, ENTITY_TYPE_COMPONENT);
    stage.entities[14] = init_entity(10, 4, stage.map.positions, microchip_component, ENTITY_TYPE_COMPONENT);
    stage.entities[15] = init_entity(11, 3, stage.map.positions, microchip_component, ENTITY_TYPE_COMPONENT);

    // Colored batery components
    ALLEGRO_BITMAP* colered_batery_component = al_load_bitmap("colered_batery_component.png");

    stage.entities[16] = init_entity(2, 4, stage.map.positions, colered_batery_component, ENTITY_TYPE_COMPONENT);
    stage.entities[17] = init_entity(3, 4, stage.map.positions, colered_batery_component, ENTITY_TYPE_COMPONENT);
    
    stage.entities[18] = init_entity(2, 6, stage.map.positions, colered_batery_component, ENTITY_TYPE_COMPONENT);
    stage.entities[19] = init_entity(3, 6, stage.map.positions, colered_batery_component, ENTITY_TYPE_COMPONENT);
    
    stage.entities[20] = init_entity(2, 8, stage.map.positions, colered_batery_component, ENTITY_TYPE_COMPONENT);
    stage.entities[21] = init_entity(3, 8, stage.map.positions, colered_batery_component, ENTITY_TYPE_COMPONENT);
    
    // Orange batery components
    ALLEGRO_BITMAP* orange_batery_component = al_load_bitmap("orange_batery_component.png");

    stage.entities[22] = init_entity(5, 7, stage.map.positions, orange_batery_component, ENTITY_TYPE_COMPONENT);
    stage.entities[23] = init_entity(6, 7, stage.map.positions, orange_batery_component, ENTITY_TYPE_COMPONENT);
    
    stage.entities[24] = init_entity(5, 9, stage.map.positions, orange_batery_component, ENTITY_TYPE_COMPONENT);
    stage.entities[25] = init_entity(6, 9, stage.map.positions, orange_batery_component, ENTITY_TYPE_COMPONENT);
    
    stage.entities[26] = init_entity(5, 11, stage.map.positions, orange_batery_component, ENTITY_TYPE_COMPONENT);
    stage.entities[27] = init_entity(6, 11, stage.map.positions, orange_batery_component, ENTITY_TYPE_COMPONENT);
    
    stage.entities[28] = init_entity(4, 14, stage.map.positions, orange_batery_component, ENTITY_TYPE_COMPONENT);
    stage.entities[29] = init_entity(5, 14, stage.map.positions, orange_batery_component, ENTITY_TYPE_COMPONENT);
    
    // Memory RAM Components  
    ALLEGRO_BITMAP* memory_ram_component_part_one = al_load_bitmap("memory_ram_component_part_one.png");
    ALLEGRO_BITMAP* memory_ram_component_part_two = al_load_bitmap("memory_ram_component_part_two.png");
    ALLEGRO_BITMAP* memory_ram_component_part_three = al_load_bitmap("memory_ram_component_part_three.png");

    stage.entities[30] = init_entity(2, 17, stage.map.positions, memory_ram_component_part_one, ENTITY_TYPE_COMPONENT);
    stage.entities[31] = init_entity(3, 17, stage.map.positions, memory_ram_component_part_two, ENTITY_TYPE_COMPONENT);
    stage.entities[32] = init_entity(4, 17, stage.map.positions, memory_ram_component_part_three, ENTITY_TYPE_COMPONENT);

    stage.entities[33] = init_entity(6, 17, stage.map.positions, memory_ram_component_part_one, ENTITY_TYPE_COMPONENT);
    stage.entities[34] = init_entity(7, 17, stage.map.positions, memory_ram_component_part_two, ENTITY_TYPE_COMPONENT);
    stage.entities[35] = init_entity(8, 17, stage.map.positions, memory_ram_component_part_three, ENTITY_TYPE_COMPONENT);

    stage.entities[36] = init_entity(2, 19, stage.map.positions, memory_ram_component_part_one, ENTITY_TYPE_COMPONENT);
    stage.entities[37] = init_entity(3, 19, stage.map.positions, memory_ram_component_part_two, ENTITY_TYPE_COMPONENT);
    stage.entities[38] = init_entity(4, 19, stage.map.positions, memory_ram_component_part_three, ENTITY_TYPE_COMPONENT);
                                        
    stage.entities[39] = init_entity(6, 19, stage.map.positions, memory_ram_component_part_one, ENTITY_TYPE_COMPONENT);
    stage.entities[40] = init_entity(7, 19, stage.map.positions, memory_ram_component_part_two, ENTITY_TYPE_COMPONENT);
    stage.entities[41] = init_entity(8, 19, stage.map.positions, memory_ram_component_part_three, ENTITY_TYPE_COMPONENT);
    
    // CPU Components
    ALLEGRO_BITMAP* cpu_component_part_one = al_load_bitmap("cpu_component_part_one.png");
    ALLEGRO_BITMAP* cpu_component_part_two = al_load_bitmap("cpu_component_part_two.png");
    ALLEGRO_BITMAP* cpu_component_part_three = al_load_bitmap("cpu_component_part_three.png");
    ALLEGRO_BITMAP* cpu_component_part_four = al_load_bitmap("cpu_component_part_four.png");

    stage.entities[42] = init_entity(12, 13, stage.map.positions, cpu_component_part_one, ENTITY_TYPE_COMPONENT);
    stage.entities[43] = init_entity(12, 14, stage.map.positions, cpu_component_part_two, ENTITY_TYPE_COMPONENT);
    stage.entities[44] = init_entity(13, 13, stage.map.positions, cpu_component_part_three, ENTITY_TYPE_COMPONENT);
    stage.entities[45] = init_entity(13, 14, stage.map.positions, cpu_component_part_four, ENTITY_TYPE_COMPONENT);

    // Cabe components
    ALLEGRO_BITMAP* horizontal_cabe_component = al_load_bitmap("horizontal_cabe_component.png");
    ALLEGRO_BITMAP* head_cabe_component = al_load_bitmap("head_cabe_component.png");
    ALLEGRO_BITMAP* turn_cabe_component = al_load_bitmap("turn_cabe_component.png");
    ALLEGRO_BITMAP* vertical_cabe_component = al_load_bitmap("vertical_cabe_component.png");

    stage.entities[46] = init_entity(14, 9, stage.map.positions, vertical_cabe_component, ENTITY_TYPE_COMPONENT);
    stage.entities[47] = init_entity(13, 9, stage.map.positions, vertical_cabe_component, ENTITY_TYPE_COMPONENT);
    stage.entities[48] = init_entity(12, 9, stage.map.positions, vertical_cabe_component, ENTITY_TYPE_COMPONENT);
    stage.entities[49] = init_entity(10, 9, stage.map.positions, vertical_cabe_component, ENTITY_TYPE_COMPONENT);

    stage.entities[50] = init_entity(9, 9, stage.map.positions, head_cabe_component, ENTITY_TYPE_COMPONENT);

    stage.entities[51] = init_entity(9, 10, stage.map.positions, horizontal_cabe_component, ENTITY_TYPE_COMPONENT);
    stage.entities[52] = init_entity(9, 11, stage.map.positions, horizontal_cabe_component, ENTITY_TYPE_COMPONENT);
    stage.entities[53] = init_entity(9, 12, stage.map.positions, horizontal_cabe_component, ENTITY_TYPE_COMPONENT);
    stage.entities[54] = init_entity(9, 13, stage.map.positions, horizontal_cabe_component, ENTITY_TYPE_COMPONENT);

    stage.entities[55] = init_entity(9, 14, stage.map.positions, head_cabe_component, ENTITY_TYPE_COMPONENT);

    stage.entities[56] = init_entity(8, 14, stage.map.positions, vertical_cabe_component, ENTITY_TYPE_COMPONENT);
    stage.entities[57] = init_entity(7, 14, stage.map.positions, vertical_cabe_component, ENTITY_TYPE_COMPONENT);
    stage.entities[58] = init_entity(6, 14, stage.map.positions, vertical_cabe_component, ENTITY_TYPE_COMPONENT);
    stage.entities[59] = init_entity(5, 14, stage.map.positions, vertical_cabe_component, ENTITY_TYPE_COMPONENT);

    stage.entities[60] = init_entity(4, 14, stage.map.positions, head_cabe_component, ENTITY_TYPE_COMPONENT);

    stage.entities[61] = init_entity(9, 15, stage.map.positions, horizontal_cabe_component, ENTITY_TYPE_COMPONENT);
    stage.entities[62] = init_entity(9, 16, stage.map.positions, horizontal_cabe_component, ENTITY_TYPE_COMPONENT);
    stage.entities[63] = init_entity(9, 17, stage.map.positions, horizontal_cabe_component, ENTITY_TYPE_COMPONENT);

    stage.entities[64] = init_entity(9, 19, stage.map.positions, head_cabe_component, ENTITY_TYPE_COMPONENT);

    // Collectables init
    ALLEGRO_BITMAP* collectable_graphic = al_load_bitmap("collectable_graphic.png");
    ALLEGRO_BITMAP* collectable_headset = al_load_bitmap("collectable_headset.png");
    ALLEGRO_BITMAP* collectable_keyboard = al_load_bitmap("collectable_keyboard.png");

    stage.entities[65] = init_entity(10, 6, stage.map.positions, collectable_graphic, ENTITY_TYPE_COLLECTABLE);
    stage.entities[66] = init_entity(11, 9, stage.map.positions, collectable_headset, ENTITY_TYPE_COLLECTABLE);
    stage.entities[67] = init_entity(5, 18, stage.map.positions, collectable_keyboard, ENTITY_TYPE_COLLECTABLE);

    ACTION_TYPE block_types[] = { ACTION_WALK, ACTION_ROTATE_CLOCKWISE, ACTION_ROTATE_COUNTERCLOCKWISE, ACTION_COLLECT };
    stage.templates_blocks = action_blocks_init(stage.bitmap, &block_types);
    stage.items_to_collect = 3;

    return stage;
}

GAME_STAGE create_thermal_noodles_stage() {
    GAME_STAGE stage;

    stage.bitmap = al_create_bitmap(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    stage.map = map_init(15, 20, stage.bitmap, STAGETYPE_COLLECT_THERMAL_NOODLES);

    current_map = stage.map;
    instruction_section = al_load_bitmap("instruction_stage_three.png");

    stage.name = "THERMAL NOODLES STAGE";
    stage.entities = get_pointer_to_array_entities(58);

    // Player init
    ALLEGRO_BITMAP* player_bitmap = al_load_bitmap("player_windows_right.png");
    stage.entities[0] = init_entity(7, 12, stage.map.positions, player_bitmap, ENTITY_TYPE_PLAYER);
    stage.entities[0].direction = ENTITY_DIRECTION_LEFT;
    
    // Screw components init
    ALLEGRO_BITMAP* screw_component = al_load_bitmap("screw_component.png");

    stage.entities[1] = init_entity(1, 1, stage.map.positions, screw_component, ENTITY_TYPE_COMPONENT);
    stage.entities[2] = init_entity(13, 1, stage.map.positions, screw_component, ENTITY_TYPE_COMPONENT);
    stage.entities[3] = init_entity(1, 18, stage.map.positions, screw_component, ENTITY_TYPE_COMPONENT);
    stage.entities[4] = init_entity(13, 18, stage.map.positions, screw_component, ENTITY_TYPE_COMPONENT);

    // SSD Components init
    ALLEGRO_BITMAP* sdd_component_part_one = al_load_bitmap("ssd_component_part_one.png");
    ALLEGRO_BITMAP* sdd_component_part_two = al_load_bitmap("ssd_component_part_two.png");
    ALLEGRO_BITMAP* sdd_component_part_three = al_load_bitmap("ssd_component_part_three.png");
    ALLEGRO_BITMAP* sdd_component_part_four = al_load_bitmap("ssd_component_part_four.png");

    stage.entities[5] = init_entity(7, 8, stage.map.positions, sdd_component_part_one, ENTITY_TYPE_COMPONENT);
    stage.entities[6] = init_entity(7, 9, stage.map.positions, sdd_component_part_two, ENTITY_TYPE_COMPONENT);
    stage.entities[7] = init_entity(7, 10, stage.map.positions, sdd_component_part_three, ENTITY_TYPE_COMPONENT);
    stage.entities[8] = init_entity(7, 11, stage.map.positions, sdd_component_part_four, ENTITY_TYPE_COMPONENT);

    stage.entities[9] =  init_entity(7, 13, stage.map.positions, sdd_component_part_one, ENTITY_TYPE_COMPONENT);
    stage.entities[10] = init_entity(7, 14, stage.map.positions, sdd_component_part_two, ENTITY_TYPE_COMPONENT);
    stage.entities[11] = init_entity(7, 15, stage.map.positions, sdd_component_part_three, ENTITY_TYPE_COMPONENT);
    stage.entities[12] = init_entity(7, 16, stage.map.positions, sdd_component_part_four, ENTITY_TYPE_COMPONENT);

    // CPU Components
    ALLEGRO_BITMAP* cpu_component_part_one = al_load_bitmap("cpu_component_part_one.png");
    ALLEGRO_BITMAP* cpu_component_part_two = al_load_bitmap("cpu_component_part_two.png");
    ALLEGRO_BITMAP* cpu_component_part_three = al_load_bitmap("cpu_component_part_three.png");
    ALLEGRO_BITMAP* cpu_component_part_four = al_load_bitmap("cpu_component_part_four.png");

    stage.entities[13] = init_entity(7, 3, stage.map.positions, cpu_component_part_one, ENTITY_TYPE_COMPONENT);
    stage.entities[14] = init_entity(7, 4, stage.map.positions, cpu_component_part_two, ENTITY_TYPE_COMPONENT);
    stage.entities[15] = init_entity(8, 3, stage.map.positions, cpu_component_part_three, ENTITY_TYPE_COMPONENT);
    stage.entities[16] = init_entity(8, 4, stage.map.positions, cpu_component_part_four, ENTITY_TYPE_COMPONENT);

    // Colored batery components
    ALLEGRO_BITMAP* colered_batery_component = al_load_bitmap("colered_batery_component.png");

    stage.entities[17] = init_entity(3, 3, stage.map.positions, colered_batery_component, ENTITY_TYPE_COMPONENT);
    stage.entities[18] = init_entity(3, 5, stage.map.positions, colered_batery_component, ENTITY_TYPE_COMPONENT);
    stage.entities[19] = init_entity(5, 3, stage.map.positions, colered_batery_component, ENTITY_TYPE_COMPONENT);
    stage.entities[20] = init_entity(5, 5, stage.map.positions, colered_batery_component, ENTITY_TYPE_COMPONENT);

    stage.entities[21] = init_entity(10, 3, stage.map.positions, colered_batery_component, ENTITY_TYPE_COMPONENT);
    stage.entities[22] = init_entity(10, 5, stage.map.positions, colered_batery_component, ENTITY_TYPE_COMPONENT);
    stage.entities[23] = init_entity(12, 3, stage.map.positions, colered_batery_component, ENTITY_TYPE_COMPONENT);
    stage.entities[24] = init_entity(12, 5, stage.map.positions, colered_batery_component, ENTITY_TYPE_COMPONENT);

    // Cabe components
    ALLEGRO_BITMAP* head_cabe_component = al_load_bitmap("head_cabe_component.png");
    ALLEGRO_BITMAP* vertical_cabe_component = al_load_bitmap("vertical_cabe_component.png");

    stage.entities[25] = init_entity(9, 7, stage.map.positions, head_cabe_component, ENTITY_TYPE_COMPONENT);

    stage.entities[26] = init_entity(10, 7, stage.map.positions, vertical_cabe_component, ENTITY_TYPE_COMPONENT);
    stage.entities[27] = init_entity(11, 7, stage.map.positions, vertical_cabe_component, ENTITY_TYPE_COMPONENT);
    stage.entities[28] = init_entity(12, 7, stage.map.positions, vertical_cabe_component, ENTITY_TYPE_COMPONENT);
    stage.entities[29] = init_entity(13, 7, stage.map.positions, vertical_cabe_component, ENTITY_TYPE_COMPONENT);
    stage.entities[30] = init_entity(14, 7, stage.map.positions, vertical_cabe_component, ENTITY_TYPE_COMPONENT);
    
    // Memory RAM Components  
    ALLEGRO_BITMAP* memory_ram_component_part_one = al_load_bitmap("memory_ram_component_part_one.png");
    ALLEGRO_BITMAP* memory_ram_component_part_two = al_load_bitmap("memory_ram_component_part_two.png");
    ALLEGRO_BITMAP* memory_ram_component_part_three = al_load_bitmap("memory_ram_component_part_three.png");

    stage.entities[31] = init_entity(2, 9, stage.map.positions, memory_ram_component_part_one, ENTITY_TYPE_COMPONENT);
    stage.entities[32] = init_entity(3, 9, stage.map.positions, memory_ram_component_part_two, ENTITY_TYPE_COMPONENT);
    stage.entities[33] = init_entity(4, 9, stage.map.positions, memory_ram_component_part_three, ENTITY_TYPE_COMPONENT);

    stage.entities[34] = init_entity(3, 14, stage.map.positions, memory_ram_component_part_one, ENTITY_TYPE_COMPONENT);
    stage.entities[35] = init_entity(4, 14, stage.map.positions, memory_ram_component_part_two, ENTITY_TYPE_COMPONENT);
    stage.entities[36] = init_entity(5, 14, stage.map.positions, memory_ram_component_part_three, ENTITY_TYPE_COMPONENT);

    stage.entities[37] = init_entity(10, 9, stage.map.positions, memory_ram_component_part_one, ENTITY_TYPE_COMPONENT);
    stage.entities[38] = init_entity(11, 9, stage.map.positions, memory_ram_component_part_two, ENTITY_TYPE_COMPONENT);
    stage.entities[39] = init_entity(12, 9, stage.map.positions, memory_ram_component_part_three, ENTITY_TYPE_COMPONENT);

    stage.entities[40] = init_entity(10, 14, stage.map.positions, memory_ram_component_part_one, ENTITY_TYPE_COMPONENT);
    stage.entities[41] = init_entity(11, 14, stage.map.positions, memory_ram_component_part_two, ENTITY_TYPE_COMPONENT);
    stage.entities[42] = init_entity(12, 14, stage.map.positions, memory_ram_component_part_three, ENTITY_TYPE_COMPONENT);

    // Orange batery components
    ALLEGRO_BITMAP* orange_batery_component = al_load_bitmap("orange_batery_component.png");

    stage.entities[43] = init_entity(1, 11, stage.map.positions, orange_batery_component, ENTITY_TYPE_COMPONENT);
    stage.entities[44] = init_entity(1, 12, stage.map.positions, orange_batery_component, ENTITY_TYPE_COMPONENT);

    stage.entities[45] = init_entity(13, 11, stage.map.positions, orange_batery_component, ENTITY_TYPE_COMPONENT);
    stage.entities[46] = init_entity(13, 12, stage.map.positions, orange_batery_component, ENTITY_TYPE_COMPONENT);

    stage.entities[47] = init_entity(5, 18, stage.map.positions, orange_batery_component, ENTITY_TYPE_COMPONENT);
    stage.entities[48] = init_entity(7, 18, stage.map.positions, orange_batery_component, ENTITY_TYPE_COMPONENT);
    stage.entities[49] = init_entity(9, 18, stage.map.positions, orange_batery_component, ENTITY_TYPE_COMPONENT);

    // Microchip Component
    ALLEGRO_BITMAP* microchip_component = al_load_bitmap("microchip_component.png");

    stage.entities[50] = init_entity(3, 11, stage.map.positions, microchip_component, ENTITY_TYPE_COMPONENT);
    stage.entities[51] = init_entity(4, 12, stage.map.positions, microchip_component, ENTITY_TYPE_COMPONENT);
    stage.entities[52] = init_entity(11, 11, stage.map.positions, microchip_component, ENTITY_TYPE_COMPONENT);
    stage.entities[53] = init_entity(10, 12, stage.map.positions, microchip_component, ENTITY_TYPE_COMPONENT);

    // Collectables init
    ALLEGRO_BITMAP* collectable_thermal_noodles = al_load_bitmap("collectable_thermal_noodles.png");
    
    stage.entities[54] = init_entity(4, 4, stage.map.positions, collectable_thermal_noodles, ENTITY_TYPE_COLLECTABLE);
    stage.entities[55] = init_entity(6, 7, stage.map.positions, collectable_thermal_noodles, ENTITY_TYPE_COLLECTABLE);
    stage.entities[56] = init_entity(9, 9, stage.map.positions, collectable_thermal_noodles, ENTITY_TYPE_COLLECTABLE);
    stage.entities[57] = init_entity(10, 11, stage.map.positions, collectable_thermal_noodles, ENTITY_TYPE_COLLECTABLE);

    ACTION_TYPE block_types[] = { ACTION_WALK, ACTION_ROTATE_CLOCKWISE, ACTION_ROTATE_COUNTERCLOCKWISE, ACTION_COLLECT };
    stage.templates_blocks = action_blocks_init(stage.bitmap, &block_types);
    stage.items_to_collect = 4;

    return stage;
}



/// <summary>
/// Com base no tipo de fase, realiza a instância do objeto respectivo a fase
/// </summary>
/// <param name="type">Tipo de fase que será instânciada</param>
/// <returns>Instância da fase</returns>
GAME_STAGE stage_init(enum GAME_STAGE_TYPE type) {
    GAME_STAGE stage;

    switch (type) {
    case STAGETYPE_COLLECT_FOLDERS:
        stage = create_default_stage();
        stage.type = STAGETYPE_COLLECT_FOLDERS;

        break;
    case STAGETYPE_COLLECT_DRIVERS:
        stage = create_drivers_stage();
        stage.type = STAGETYPE_COLLECT_DRIVERS;
        break;

    case STAGETYPE_COLLECT_THERMAL_NOODLES:
        stage = create_thermal_noodles_stage();
        stage.type = STAGETYPE_COLLECT_THERMAL_NOODLES;
        break;
    }

    stage.is_started = true;
    return stage;
}


ACTION_BLOCK* action_blocks_init(ALLEGRO_BITMAP* stage_bitmap, int* action_type_list) {
    int list_lenght = 4;
    ACTION_BLOCK* list_template_blocks = allocate_array(list_lenght, sizeof(ACTION_BLOCK));

    ALLEGRO_BITMAP* block_templates_bitmap = al_create_sub_bitmap(stage_bitmap, ACTION_BLOCK_CONTAINER_POSITION_X, ACTION_BLOCK_CONTAINER_POSITION_Y, 640, 80);

    ACTION_BLOCK last_action_block = { .position_x = 0, .width = 0 };
    for (int i = 0; i < list_lenght; i++)
    {
        int x_position = (i * last_action_block.width + (10 * i) + 15);
        int y_position = 10;

        last_action_block = create_block(block_templates_bitmap, x_position, y_position, action_type_list[i]);
        list_template_blocks[i] = last_action_block;

        ALLEGRO_BITMAP* btm_buffer = al_create_sub_bitmap(block_templates_bitmap, x_position, y_position, last_action_block.width, last_action_block.height);
        al_set_target_bitmap(btm_buffer);
        al_draw_bitmap(last_action_block.bitmap, 0, 0, 0);
    }

    return list_template_blocks;
}

/// <summary>
/// Com base em uma posição da fase, informada, verifica se existe alguma entidade nela
/// </summary>
/// <param name="stage">Fase respectiva</param>
/// <param name="position">Posição que deseja verificar</param>
/// <returns>Caso encontre alguma entidade nesta posição, retorna-a</returns>
GAME_ENTITY** get_entities_on_position(GAME_STAGE* stage ,MAP_POSITION* position) {
    GAME_ENTITY** entity_return = NULL;
    int entities_found = 0;

    // Obtendo o tamanho do array de entidades
    int entities_lenght = get_array_size(stage->entities);
    
    for (int i = 0; i < entities_lenght; i++)
    {
        // Obtendo a entidade na posição de iteração
        GAME_ENTITY* entity = &(stage->entities[i]);

        // Verificando se a ordem da posição informada, é a mesma presente na posição da entidade da iteração
        if (position->id == entity->position->id)
        {
            entities_found++;

            if (entities_found == 1) {
                entity_return = allocate_array(entities_found, sizeof(GAME_ENTITY*));
            }
            else {
                GAME_ENTITY* tmp_entity = entity_return[0];
                entity_return = allocate_array(entities_found, sizeof(GAME_ENTITY*));
                entity_return[0] = tmp_entity;
            }

            // Preenche a entidade para retorno e para e execução do for
            entity_return[entities_found - 1] = entity;
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

    if (map->bitmap != NULL) {
        al_destroy_bitmap(map->bitmap);
        map->bitmap = NULL;
    }

    switch (stage->type)
    {
    case STAGETYPE_COLLECT_FOLDERS:
        map->bitmap = al_load_bitmap("background_map_stage_one.png");    
        break;
    case STAGETYPE_COLLECT_DRIVERS:
        map->bitmap = al_load_bitmap("background_map_stage_two.png");
        break;
    case STAGETYPE_COLLECT_THERMAL_NOODLES:
        map->bitmap = al_load_bitmap("background_map_stage_three.png");
        break;
    }

    al_set_target_bitmap(map->bitmap);

    // Percorrendo a matriz de posições
    MAP_POSITION** positions = map->positions;
    for (int i = 0; i < map->height_blocks; i++)
    {
        for (int j = 0; j < map->width_blocks; j++)
        {
            // Pegando a posição atual e definindo uma coloração para o seu bitmap
            MAP_POSITION* position = &(positions[i][j]);

            position->bitmap = al_create_sub_bitmap(map->bitmap, position->x_position, position->y_position, BLOCK_WIDTH, BLOCK_HEIGHT);

            // Verificando se existe alguma entidade na posição da iteração atual
            // caso exista, escreve sua representação no bloco respectivo
            GAME_ENTITY** entities_on_position = get_entities_on_position(stage, position);
            if (entities_on_position)
            {
                int entities_found = get_array_size(entities_on_position);
                GAME_ENTITY* player_entity = NULL;
                GAME_ENTITY* any_entity = NULL;

                for (int i = 0; i < entities_found; i++)
                {
                    GAME_ENTITY* loop_entity = entities_on_position[i];
                    
                    if (loop_entity == NULL) continue;
                    if (loop_entity->hide) continue;

                    if (loop_entity->type == ENTITY_TYPE_PLAYER) {
                        player_entity = loop_entity;
                        continue;
                    }

                    any_entity = loop_entity;
                }

                ALLEGRO_BITMAP* btm_buffer = al_create_sub_bitmap(position->bitmap, 0, 0, BLOCK_WIDTH, BLOCK_HEIGHT);

                if (any_entity) {
                    al_set_target_bitmap(btm_buffer);

                    if (al_get_bitmap_width(any_entity->bitmap) == 16) 
                        al_draw_bitmap(any_entity->bitmap, 8, 8, 0);
                    else
                        al_draw_bitmap(any_entity->bitmap, 0, 0, 0);

                }

                if (player_entity) {
                    al_set_target_bitmap(btm_buffer);
                    
                    ALLEGRO_BITMAP* player_windows_bitmap = NULL;
                    
                    switch (player_entity->direction)
                    {
                    case ENTITY_DIRECTION_RIGHT:
                        player_windows_bitmap = al_load_bitmap("player_windows_right.png");
                        break;
                    case ENTITY_DIRECTION_DOWN:
                        player_windows_bitmap = al_load_bitmap("player_windows_down.png");
                        break;
                    case ENTITY_DIRECTION_LEFT:
                        player_windows_bitmap = al_load_bitmap("player_windows_left.png");
                        break;
                    case ENTITY_DIRECTION_UP:
                        player_windows_bitmap = al_load_bitmap("player_windows_up.png");
                        break;

                    default:
                        player_windows_bitmap = player_entity->bitmap;
                        break;
                    }
                    
                    al_draw_bitmap(player_windows_bitmap, 0, -10, 0);
                }

                al_set_target_bitmap(position->bitmap);
                al_draw_bitmap(btm_buffer, 0, 0, 0);
            }
        }
    }

    // Coloca o bitmap do mapa em evidência, e adiciona uma coloração a ele
    al_set_target_bitmap(stage->bitmap);

    al_draw_bitmap(map->bitmap, 32, 160, 0);

    // Coloca o bitmap do display principal em evidência
    al_set_target_bitmap(al_get_backbuffer(display));

    if (instruction_section != NULL) {
        al_draw_bitmap(instruction_section, 32, 664, 0);
    }

    // Escreve o bitmap da fase no display e troca a exbição dos bitmaps no display
    al_draw_bitmap(stage->bitmap, 0, 0, 0);

    if (how_to_play_active) {
        al_set_target_bitmap(al_get_backbuffer(display));
        al_draw_bitmap(al_load_bitmap("help_popup.png"), 0, 0, 0);

        button_close_how_to_play = al_load_bitmap("button_close.png");
        button_close_popup_how_to_play_position_x = 886;
        button_close_popup_how_to_play_position_y = 280;

        al_draw_bitmap(button_close_how_to_play, button_close_popup_how_to_play_position_x, button_close_popup_how_to_play_position_y, 0);
    }
}