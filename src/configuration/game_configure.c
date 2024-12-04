#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "game_configure.h"
#include "../display/map/map_service.h"

ALLEGRO_TIMER* timer;
ALLEGRO_EVENT_QUEUE* queue;
ALLEGRO_DISPLAY* display;
ALLEGRO_FONT* font;
ALLEGRO_BITMAP* action_block_container_bitmap = NULL;

/// <summary>
/// Faz a verificação se o processo do Allegro foi inicializado com sucesso.
/// Caso não tenha, loga uma mensagem personalizada e para a execução do programa.
/// </summary>
/// <param name="test">Valor booleano indicando se a inicialização foi concluída com sucesso.</param>
/// <param name="description">Descrição personalizada sobre "o quê" estava tentando ser inicializado.</param>
void must_init(bool test, const char* description)
{
    if (test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

/// <summary>
/// Método para realizar a inicialização das configurações do Allegro5
/// </summary>
void resolve_dependencies() {
    must_init(al_init(), "TheJorneyOfWindows");
    must_init(al_install_mouse(), "Mouse");
    must_init(al_install_keyboard(), "Keyboard");
    must_init(al_init_primitives_addon(), "primitve addons");
    must_init(al_init_image_addon(), "image addons");

    // Inicializando timer
    timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    // Inicializando fila
    queue = al_create_event_queue();
    must_init(timer, "queue");

    // Inicializando a tela
    display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    must_init(display, "display");
    al_set_window_title(display, "The Journey of Windows");

    // Inicializando um tipo de fonte
    font = al_create_builtin_font();
    must_init(font, "font");

    // Registrando os tipo de eventos na fila
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
}



