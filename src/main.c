#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "configuration/game_configure.h"
#include "display/stage/stage_service.h"

int main(void) {
    resolve_dependencies();

    ALLEGRO_EVENT event;
    GAME_STAGE stage;
    stage.is_started = false;
    bool redraw = true;

    al_start_timer(timer);
    while (1)
    {
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_KEY_UP) 
        {
            MAP_POSITION position = *(stage.entities[0].position);

            switch (event.keyboard.keycode)
            {
                case ALLEGRO_KEY_RIGHT:
                    stage.entities[0].position = get_position(position.grid_column_position, position.grid_row_position + 1, &stage.map);
                    break;
                case ALLEGRO_KEY_DOWN:
                    stage.entities[0].position = get_position(position.grid_column_position + 1, position.grid_row_position, &stage.map);
                    break;
                case ALLEGRO_KEY_LEFT:
                    stage.entities[0].position = get_position(position.grid_column_position, position.grid_row_position - 1, &stage.map);
                    break;
                case ALLEGRO_KEY_UP:
                    stage.entities[0].position = get_position(position.grid_column_position - 1, position.grid_row_position, &stage.map);
                    break;

            default:
                break;
            }

        }

        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            if (!(stage.is_started)) {
                stage = stage_init(STAGETYPE_DEFAULT);
            }
            redraw = true;
        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

        if (redraw && al_is_event_queue_empty(queue)) 
        {
            stage_print(&stage);
            redraw = false;
        }
    }

    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
