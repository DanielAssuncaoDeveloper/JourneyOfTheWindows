#include <stdlib.h>
#include "blocks_service.h"

// Variável global para manter o bloco selecionado ao arrastar
static Block* select_block = NULL;

/// <summary>
/// Função para realizar a criação de cada bloco
/// </summary>
/// <param name="position_x">Recebe a posição horizontal do bloco em tela</param>
/// <param name="position_y">Recebe a posição vertical do bloco em tela</param>
/// <param name="func">Função a qual o bloco será responsável por executar</param>
/// <returns>Retorna o bloco criado</returns>
Block* create_block(ALLEGRO_BITMAP*, int position_x, int position_y, int width, int height, void (*func)()) {
	Block* block = malloc(sizeof(Block));
	if (!block) {
		printf("Couldn't create Block!");
	}
	block->position_x = position_x;
	block->position_y = position_y;
    block->width = width
	block->bitmap = bitmap;
	block->func = func;

	return block;
}

/// <summary>
/// Realiza o desenho do bloco em tela
/// </summary>
/// <param name="block">Nome do bloco a ser renderizado</param>
void draw_block(Block* block) {
    if (block == NULL || block->bitmap == NULL) return;

    // Desenha o bitmap do bloco
    al_draw_bitmap(block->bitmap, block->position_x, block->position_y, block->width, block->height, 0);
}

/// <summary>
/// Função para encontrar o bloco e seleciona-lo com base na posição do mouse 
/// </summary>
/// <param name="event">Recebe o evento</param>
/// <param name="head">Acessa o topo da lista de blocos</param>
void handle_mouse_event(ALLEGRO_EVENT* event, Block** head) {
    if (event == NULL || head == NULL) return;

    static bool is_dragging = false;

    if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if (event->mouse.button & 1) { // Bot?o esquerdo do mouse
            // Itera sobre a lista de blocos para encontrar qual foi clicado
            Block* current = *head;
            Block* found_block = NULL;
            while (current != NULL) {
                if (event->mouse.x >= current->position_x &&
                    event->mouse.x <= current->position_x + current->width &&
                    event->mouse.y >= current->position_y &&
                    event->mouse.y <= current->position_y + current->height) {
                    found_block = current;
                    break;
                }
            }

            if (found_block != NULL) {
                selected_block = found_block;
                is_dragging = true;
            }
        }
    }
    else if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
        if (event->mouse.button & 1) { // Bot?o esquerdo do mouse
            is_dragging = false;
            selected_block = NULL; // Libera a seleção
        }
    }
    else if (event->type == ALLEGRO_EVENT_MOUSE_AXES) {
        if (is_dragging && selected_block) {
            // Atualiza a posi??o do bloco arrastado
            selected_block->position_x = event->mouse.x - selected_block->width / 2;
            selected_block->position_y = event->mouse.y - selected_block->height / 2;
        }
    }
}

/// <summary>
/// Fun??o utilizada para que o jogador andar para a Direita
/// </summary>
void walk_to_right() {
    stage.entities[0].position = get_position(position.grid_column_position, position.grid_row_position + 1, &stage.map);
    break;
}

/// <summary>
/// Fun??o informa que o jogador andar para cima
/// </summary>
void walk_to_up() {
    stage.entities[0].position = get_position(position.grid_column_position - 1, position.grid_row_position, &stage.map);
    break;
}

/// <summary>
/// Fun??o informa que o jogador ande para a esquerda
/// </summary>
void walk_to_left() {
    stage.entities[0].position = get_position(position.grid_column_position, position.grid_row_position - 1, &stage.map);
    break;
}

/// <summary>
///  Fun??o informa que o jogador deve descer na escala do mapa.
/// </summary>
void walk_to_down() {
    stage.entities[0].position = get_position(position.grid_column_position + 1, position.grid_row_position, &stage.map);
    break;
}
