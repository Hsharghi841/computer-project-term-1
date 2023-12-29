#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

ALLEGRO_DISPLAY * display;
ALLEGRO_BITMAP * cursor;
ALLEGRO_FONT * font;
ALLEGRO_MOUSE_STATE msestate;

extern int wall[31][31];

int allegroINIT(){
	
	al_init();
	display = al_create_display(1280 ,720);
	al_hide_mouse_cursor(display);
	
    al_init_font_addon();
	font = al_create_builtin_font();
	
    al_init_primitives_addon();
    
    al_install_mouse();
    
    al_init_image_addon();
	cursor = al_load_bitmap("cursor.tga");
	
	if (!cursor) {
      printf("Error loading cursor.tga\n");
      return -1;
    }
    return 1;
    

	
}

int allegroDESTROY(){
	
	al_destroy_display(display);
	al_destroy_font(font);
	al_shutdown_primitives_addon();
	al_destroy_mouse_cursor(cursor);
	al_uninstall_mouse();
	al_shutdown_image_addon();
	
	return 1;
}

int put_mouse(){
	al_get_mouse_state(&msestate);
	al_draw_bitmap(cursor,msestate.x,msestate.y,0);
    al_draw_bitmap(cursor,msestate.x,msestate.y,0);
	return 1;
}

void show_board(int n){
    int x,y;
    x=y=700/n;
    for (int i = 10; (i-10)/x < n; i+=x)
        for (int j = 10; (j-10)/y < n; j+=y){
            al_draw_filled_rectangle(i,j,i+x,j+y, al_map_rgb(190,156,84));
            al_draw_rectangle(i,j,i+x,j+y, al_map_rgb(158,153,101),60 / n);
        }
    
}

void show_wall(int i,int j,int x,int y,int x1,int y1,int x2,int y2)
{
    if (wall[i][j]==1)
    {
        al_draw_filled_rectangle(x1-3,y1,x+3,y,al_map_rgb(146,255,71));
    }
    if (wall[i][j]==2)
    {
        al_draw_filled_rectangle(x2,y2-3,x,y+3,al_map_rgb(146,255,71));
    }
    if (wall[i][j]==3)
    {
        al_draw_filled_rectangle(x1-3,y1,x+3,y,al_map_rgb(146,255,71));
        al_draw_filled_rectangle(x2,y2-3,x,y+3,al_map_rgb(146,255,71));
    }
}

void show_walls(int n){
	int x ,y;
	x = y = 700 / n;
    for (int i = 10; (i-10)/x < n-1; i+=x)
        for (int j = 10; (j-10)/y < n-1; j+=y){
           	show_wall(((i-10)/x),((j-10)/y),i+x,j+y,i+x,j,i,j+y);
        }
}





