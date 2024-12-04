#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "configuration/game_configure.h"
#include "display/stage/stage_service.h"
#include "display/game/game_service.h"
#include "display/action_block/action_blocks_service.h"
#include "utils/array_utils.h"

int main(void) {
    // Resolvendo dependencias do Allegro
    // (Inicializando addons; Registrando fila de eventos; Atribuindo variáveis públicas)
    resolve_dependencies();

    ALLEGRO_EVENT event;
    GAME init_game = {
        .instantiated_blocks = allocate_array(0, sizeof(ACTION_BLOCK)),
        .items_collected = 0
    };

    game = init_game;

    ALLEGRO_BITMAP* background_main_screen = al_load_bitmap("main_screen.png");

    ALLEGRO_BITMAP* button_connect = al_load_bitmap("button_connect.png");
    int connect_width = al_get_bitmap_width(button_connect),
        connect_height = al_get_bitmap_height(button_connect);

    int connect_x = DISPLAY_WIDTH / 2 - connect_width / 2,
        connect_y = DISPLAY_HEIGHT / 2 - 100;

    ALLEGRO_BITMAP* button_quit = al_load_bitmap("button_quit.png");
    int quit_width = al_get_bitmap_width(button_quit), quit_height = al_get_bitmap_height(button_quit);
    int quit_x = DISPLAY_WIDTH / 2 - quit_width / 2,
        quit_y = DISPLAY_HEIGHT / 2 - 50;

    game.current_stage.is_started = false;

    bool in_game = false;
    bool redraw = true;

    //int current_stage_type = STAGETYPE_COLLECT_FOLDERS;
    //int current_stage_type = STAGETYPE_COLLECT_DRIVERS;
    int current_stage_type = STAGETYPE_COLLECT_THERMAL_NOODLES;

    al_start_timer(timer);
    while (1)
    {
        al_wait_for_event(queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

        if (in_game) {

            if (event.type == ALLEGRO_EVENT_TIMER)
            {
                if (!(game.current_stage.is_started)) {
                    game.current_stage = stage_init(current_stage_type);
                    stage_print(&game.current_stage);
                    redraw = true;
                }
            }

            if (is_start_action(&event)) {
                game.executing_actions = true;
            }

            if (game.executing_actions) {
                execute_action(&game);
                redraw = true;
            }

            if (redraw)
            {
                game_print(&game);
                if (game.executing_actions) {
                    al_rest(0.25);
                }

                redraw = false;
            }

            if (is_how_to_play_button(&event)) {
                how_to_play_active = true;
                redraw = true;
            }

            on_close_popup_how_to_play(&event, &redraw);

            game.instantiated_blocks = on_intantiating_block(&event, game.current_stage.templates_blocks, game.instantiated_blocks, &redraw);
            game.instantiated_blocks = on_deleting_block(&event, game.instantiated_blocks, &redraw);

            if (game.player_colisided) {

                al_set_target_bitmap(al_get_backbuffer(display));
                al_draw_bitmap(al_load_bitmap("information_popup_player_colided.png"), 0, 0, 0);

                al_flip_display();
                al_rest(3);

                game.game_end = true;
                game.win = false;
            }

            if (game.game_end) {

                if (game.win) {
                    al_set_target_bitmap(al_get_backbuffer(display));
                    al_draw_bitmap(al_load_bitmap("information_popup_win.png"), 0, 0, 0);

                    al_flip_display();
                    al_rest(3);

                    current_stage_type++;
                    if (current_stage_type > STAGETYPE_COLLECT_THERMAL_NOODLES) {
                        current_stage_type = 0;
                        in_game = false;
                    }
                }

                game = init_game;
                game.instantiated_blocks = allocate_array(0, sizeof(ACTION_BLOCK));
                game.items_collected = 0;
            }

        }
        else {

            // Escreve o bitmap da fase no display e troca a exbição dos bitmaps no display
            al_set_target_bitmap(al_get_backbuffer(display));
            al_draw_bitmap(background_main_screen, 0, 0, 0);

            al_set_target_bitmap(background_main_screen);
            al_draw_bitmap(button_connect, connect_x, connect_y, 0);
            al_draw_bitmap(button_quit, quit_x, quit_y, 0);

            bool is_x_mouse_in_connect = event.mouse.x >= connect_x && event.mouse.x <= connect_x + connect_width;
            bool is_y_mouse_in_connect = event.mouse.y >= connect_y && event.mouse.y <= connect_y + connect_height;

            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if (is_x_mouse_in_connect && is_y_mouse_in_connect) {
                    in_game = true;

                    //al_destroy_bitmap(button_connect);
                    //al_destroy_bitmap(button_quit);
                    //al_destroy_bitmap(background_main_screen);
                }
            }

            al_flip_display();
        }
    }

    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    return 0;
}
