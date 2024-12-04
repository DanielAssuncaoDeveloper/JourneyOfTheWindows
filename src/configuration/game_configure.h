#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#ifndef ALLEGRO_CONFIGURE_H
#define ALLEGRO_CONFIGURE_H

/* CONSTANTES REFERENTES AO TAMANHO DA TELA 
------------------------------------------- */
#define DISPLAY_WIDTH 1440 // Dimensão de LARGURA do display em pixels
#define DISPLAY_HEIGHT 800 // Dimensão de ALTURA do display em pixels

/* CONSTANTES REFERENTES AO TAMANHO DOS BLOCOS DOS MAPAS 
-------------------------------------------------------- */
#define BLOCK_WIDTH 32 // Dimensão da LARGURA dos blocos em pixels
#define BLOCK_HEIGHT 32 // Dimensão de ALTURA dos blocos em pixels

#define ACTION_BLOCK_CONTAINER_POSITION_X 775
#define ACTION_BLOCK_CONTAINER_POSITION_Y 166

/* VARIAVEIS GLOBAIS DO ALLEGRO 5 
--------------------------------- */
extern ALLEGRO_TIMER* timer;
extern ALLEGRO_EVENT_QUEUE* queue;
extern ALLEGRO_DISPLAY* display;
extern ALLEGRO_FONT* font;
extern ALLEGRO_BITMAP* action_block_container_bitmap;

void resolve_dependencies();

#endif
