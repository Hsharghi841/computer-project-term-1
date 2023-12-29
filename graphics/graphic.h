#ifndef __graphic__
#define __graphic__

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>



int allegroINIT();
int allegroDESTROY();
int put_mouse();
void show_board(int n);

#endif