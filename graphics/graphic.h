#ifndef __graphic__
#define __graphic__

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>




int allegroINIT();
int allegroDESTROY();
int put_mouse();
void show_board();
void show_wall(int i,int j,int x,int y,int x1,int y1,int x2,int y2, float thickness);
void show_walls();
int show_animal(int id);
int show_object(int id, int x, int y);
int show_components();
int is_mouse_on_Board(int x, int y);
int is_mouse_nextto(int x, int y, int xboard, int yboard);
void find_cordinate_on_board(int x, int y, int *xBoard, int *yBoard);

int show_slection_hover(int x, int y);
void show_slections(coordinates selections[], int n);

void show_background();
void show_dice(int die[4], bool reset);

void show_button(button btn);
int check_button(button b, int x, int y);
void show_scoreboard();
void show_turn(turns turn);
void show_round(int round);

void show_name_of_game();
void show_starting_menu();
void scan_from_display(char result[20]);
enum page show_pause_menu();
enum page wait_for_click();

enum page move_animation(coordinates avalie,coordinates sanavie,int id);
#endif