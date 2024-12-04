#include <stdlib.h>
#include "action_blocks_service.h"
#include "../../action/funcion_action_service.h"
#include "../game/game_service.h"
#include "../../configuration/game_configure.h"
#include "../../utils/array_utils.h"

// Variável global para manter o bloco selecionado ao arrastar
static ACTION_BLOCK* selected_block = NULL;

/// <summary>
/// Função para realizar a criação de cada bloco
/// </summary>
/// <param name="position_x">Recebe a posição horizontal do bloco em tela</param>
/// <param name="position_y">Recebe a posição vertical do bloco em tela</param>
/// <param name="func">Função a qual o bloco será responsável por executar</param>
/// <returns>Retorna o bloco criado</returns>
ACTION_BLOCK create_block(ALLEGRO_BITMAP* bitmap_parent, int position_x, int position_y, ACTION_TYPE action_type) {
    ACTION_BLOCK block;
	
	block.position_x = position_x;
	block.position_y = position_y;
    block.action_type = action_type;

    ALLEGRO_BITMAP* btm_buffer = NULL;

    switch (action_type)
    {
    case ACTION_WALK:
        block.ptr_action = action_walk;
        btm_buffer = al_load_bitmap("walk_button.png");

        break;
    case ACTION_ROTATE_CLOCKWISE:
        block.ptr_action = action_rotate_clockwise;
        btm_buffer = al_load_bitmap("turn_left_button.png");

        break;
    case ACTION_ROTATE_COUNTERCLOCKWISE:
        block.ptr_action = action_rotate_counterclockwise;
        btm_buffer = al_load_bitmap("turn_rigth_button.png");

        break;
    case ACTION_COLLECT:
        block.ptr_action = action_collect;
        btm_buffer = al_load_bitmap("collect_button.png");

        break;
    default:
        break;
    }

    block.height = al_get_bitmap_height(btm_buffer);
    block.width = al_get_bitmap_width(btm_buffer);
    block.bitmap = btm_buffer;

	return block;
}

/// <summary>
/// Realiza o desenho do bloco em tela
/// </summary>
/// <param name="block">Nome do bloco a ser renderizado</param>
void draw_block(ACTION_BLOCK* block) {
    if (block == NULL || block->bitmap == NULL) return;

    // Desenha o bitmap do bloco
    al_draw_bitmap(block->bitmap, block->position_x, block->position_y, 0);
}

bool is_mouse_in_action_block(ALLEGRO_MOUSE_EVENT mouse, ACTION_BLOCK block) {

    int block_x_position = block.position_x + ACTION_BLOCK_CONTAINER_POSITION_X;
    int block_y_position = block.position_y + ACTION_BLOCK_CONTAINER_POSITION_Y;

    // Verificando se a posição do mouse está entre as extremidades do bloco iterado
    bool is_x_mouse_in_block = mouse.x >= block_x_position && mouse.x <= block_x_position + block.width;
    bool is_y_mouse_in_block = mouse.y >= block_y_position && mouse.y <= block_y_position + block.height;

    return is_x_mouse_in_block && is_y_mouse_in_block;
}

void set_block_position_on_mouse(ALLEGRO_MOUSE_EVENT mouse, ACTION_BLOCK* block) {
    block->position_x = (mouse.x - ACTION_BLOCK_CONTAINER_POSITION_X) - block->width / 2;
    block->position_y = (mouse.y - ACTION_BLOCK_CONTAINER_POSITION_Y) - block->height / 2;
}


ACTION_BLOCK* on_deleting_block(ALLEGRO_EVENT* event, ACTION_BLOCK* instantiated_blocks, bool* redraw) {
    if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event->mouse.button == 2) {
        int instantiated_blocks_lenght = get_array_size(instantiated_blocks);
        int last_position_added = 0;

        // TODO: Verificar o que acontece quando só tem um bloco
        ACTION_BLOCK* new_instatiated_blocks = allocate_array(instantiated_blocks_lenght - 1, sizeof(ACTION_BLOCK));

        for (int i = 0; i < instantiated_blocks_lenght; i++)
        {
            ACTION_BLOCK current_block = instantiated_blocks[i];

            if (is_mouse_in_action_block(event->mouse, current_block)) {
                continue;
            }

            // Significa que nenhum bloco foi removido
            if (last_position_added == instantiated_blocks_lenght - 1) return instantiated_blocks;

            new_instatiated_blocks[last_position_added] = current_block;
            last_position_added++;
        }

        new_instatiated_blocks = reallocate_array(new_instatiated_blocks, instantiated_blocks_lenght - 1, sizeof(ACTION_BLOCK));

        // Se chegou até aqui, é esperado que algum bloco tenha sido removido
        for (int i = 0; i < instantiated_blocks_lenght - 1; i++)
        {
            ACTION_BLOCK current_block = new_instatiated_blocks[i];

            int new_block_position_x = 10;
            int new_block_position_y = 90;

            if (i > 0) {
                ACTION_BLOCK last_block = instantiated_blocks[i - 1];

                new_block_position_x = last_block.position_x + last_block.width + 10;
                new_block_position_y = last_block.position_y;

                // Cabem somente 4 blocos por fileira, dessa forma sabemos que se o número de blocos instanciados
                // for divisível por quatro, chegou ao limite da fileira e deve pular para a fileira de baixo
                if (i % 4 == 0) {
                    new_block_position_x = 10;
                    new_block_position_y = last_block.position_y + last_block.height + 10;
                }
            }

            new_instatiated_blocks[i] = create_block(action_block_container_bitmap, new_block_position_x, new_block_position_y, current_block.action_type);
        }

        *redraw = true;
        return new_instatiated_blocks;
    }

    return instantiated_blocks;
}

ACTION_BLOCK* on_intantiating_block(ALLEGRO_EVENT* event, ACTION_BLOCK* blocks_template, ACTION_BLOCK* instantiated_blocks, bool* redraw) {
    if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event->mouse.button == 1) {
        int blocks_template_lenght = get_array_size(blocks_template);
        int instantiated_blocks_lenght = get_array_size(instantiated_blocks);

        if (instantiated_blocks_lenght == 36) {
            printf("\nQuantidade máxima de blocos atingida.");
            return instantiated_blocks;
        }

        for (int i = 0; i < blocks_template_lenght; i++)
        {
            ACTION_BLOCK current_block = blocks_template[i];

            if (is_mouse_in_action_block(event->mouse, current_block)) {
                int new_block_position_x = 10;
                int new_block_position_y = 90;

                if (instantiated_blocks_lenght > 0) {
                    ACTION_BLOCK last_block = instantiated_blocks[instantiated_blocks_lenght - 1];

                    new_block_position_x = last_block.position_x + last_block.width + 10;
                    new_block_position_y = last_block.position_y;

                    // Cabem somente 4 blocos por fileira, dessa forma sabemos que se o número de blocos instanciados
                    // for divisível por quatro, chegou ao limite da fileira e deve pular para a fileira de baixo
                    if (instantiated_blocks_lenght % 4 == 0) {
                        new_block_position_x = 10;
                        new_block_position_y = last_block.position_y + last_block.height + 10;
                    }
                }

                ACTION_BLOCK new_instantiated_block = create_block(action_block_container_bitmap, new_block_position_x, new_block_position_y, current_block.action_type);
                instantiated_blocks = reallocate_array(instantiated_blocks, instantiated_blocks_lenght + 1, sizeof(ACTION_BLOCK));

                instantiated_blocks[instantiated_blocks_lenght] = new_instantiated_block;
            }
        }

        *redraw = true;
    }

    return instantiated_blocks;
}

/// <summary>
/// Função para encontrar o bloco e seleciona-lo com base na posição do mouse 
/// </summary>
/// <param name="event">Recebe o evento</param>
/// <param name="head">Acessa o topo da lista de blocos</param>
void on_handle_mouse_event(ALLEGRO_EVENT* event, ACTION_BLOCK* instantiated_blocks_list) {
    if (event == NULL || instantiated_blocks_list == NULL) return;

    ACTION_BLOCK* found_block = NULL;

    int blocks_list_length = get_array_size(instantiated_blocks_list);
    static bool is_dragging = false;

    if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if (event->mouse.button & 1) { // Botão esquerdo do mouse

            // Itera sobre a lista de blocos para encontrar qual foi clicado
            for (int i = 0; i < blocks_list_length; i++)
            {
                ACTION_BLOCK* current_block = &(instantiated_blocks_list[i]);

                if (is_mouse_in_action_block(event->mouse, *current_block)) {
                    found_block = current_block;
                }

                if (found_block != NULL) {
                    selected_block = found_block;
                    is_dragging = true;
                    break;
                }
            }
        }
    }
    else if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
        if (event->mouse.button & 1) { // Botãoo esquerdo do mouse
            is_dragging = false;
            selected_block = NULL; // Libera a seleção
        }
    }
    else if (event->type == ALLEGRO_EVENT_MOUSE_AXES) {
        if (is_dragging && selected_block) {
            // Atualiza a posição do bloco arrastado
            set_block_position_on_mouse(event->mouse, selected_block);
            draw_block(selected_block);
        }
    }
}