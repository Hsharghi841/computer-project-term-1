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
void show_board();
void show_wall(int i,int j,int x,int y,int x1,int y1,int x2,int y2, float thickness);
void show_walls();
// int show_animal(int id, int boadSize);
int show_object(int id);
int is_mouse_on_Board(int x, int y);

int show_slection_havel(int x, int y);

#endif