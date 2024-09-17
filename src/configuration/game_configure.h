#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#ifndef ALLEGRO_CONFIGURE_H
#define ALLEGRO_CONFIGURE_H

/* CONSTANTES REFERENTES AO TAMANHO DA TELA 
------------------------------------------- */
#define DISPLAY_WIDTH 1555 // Dimensão de LARGURA do display em pixels
#define DISPLAY_HEIGHT 900 // Dimensão de ALTURA do display em pixels

/* CONSTANTES REFERENTES AO TAMANHO DOS BLOCOS DOS MAPAS 
-------------------------------------------------------- */
#define BLOCK_WIDTH 60 // Dimensão da LARGURA dos blocos em pixels
#define BLOCK_HEIGHT 60 // Dimensão de ALTURA dos blocos em pixels

/* VARIAVEIS GLOBAIS DO ALLEGRO 5 
--------------------------------- */
extern ALLEGRO_TIMER* timer;
extern ALLEGRO_EVENT_QUEUE* queue;
extern ALLEGRO_DISPLAY* display;
extern ALLEGRO_FONT* font;

void resolve_dependencies();

#endif
