#include "../graphics/graphic.h"


ALLEGRO_DISPLAY * display;
ALLEGRO_BITMAP * cursor;
ALLEGRO_FONT * font;
ALLEGRO_MOUSE_STATE msestate;

extern int wall[31][31];
extern struct animal{
    int ID;
    char * name;
    unsigned short energy;
    unsigned short power;
    unsigned short score;
    unsigned short dogdefense;
    unsigned short x;
    unsigned short y;
};

typedef struct animal animal;

extern enum direction {None , Up, Right, Down, Left};
typedef enum direction direction;

extern animal animals[27];

// extern animal animals[27];

char *ch[35] = {"", "d1", "d2", "d3", "d4", "m1",
              "m2", "m3", "m4", "m5", "m6", "m7", "m8", "m9", "m10", "m11", "m12", "m13", "m14", "m15", "m16", "m17", "m18",
              "c1", "c2", "c3", "c4",
              "T", "Choco", "", "", "", "F1", "F2", "F3"
              };

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
    al_shutdown_font_addon();
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

void show_board(int boadSize){
    int x,y;
    x=y=700 /boadSize;
    for (int i = 10; (i-10)/x < boadSize; i+=x)
        for (int j = 10; (j-10)/y < boadSize; j+=y){
            al_draw_filled_rectangle(i,j,i+x,j+y, al_map_rgb(190,156,84));
            al_draw_rectangle(i,j,i+x,j+y, al_map_rgb(158,153,101),60 / boadSize);
        }
    
}

void show_wall(int i,int j,int x,int y,int x1,int y1,int x2,int y2, float thickness)
{
    if (wall[i][j]==1)
    {
        al_draw_filled_rectangle(x1-thickness / 2,y1,x+thickness / 2,y,al_map_rgb(146,255,71));
    }
    if (wall[i][j]==2)
    {
        al_draw_filled_rectangle(x2,y2-thickness / 2,x,y+thickness / 2,al_map_rgb(146,255,71));
    }
    if (wall[i][j]==3)
    {
        al_draw_filled_rectangle(x1-thickness / 2,y1,x+thickness / 2,y,al_map_rgb(146,255,71));
        al_draw_filled_rectangle(x2,y2-thickness / 2,x,y+thickness / 2,al_map_rgb(146,255,71));
    }
}

void show_walls(int boadSize){
	int x ,y;
	x = y = 700 / boadSize;
    for (int i = 10; (i-10)/x < boadSize-1; i+=x)
        for (int j = 10; (j-10)/y < boadSize-1; j+=y){
           	show_wall(((i-10)/x),((j-10)/y),i+x,j+y,i+x,j,i,j+y, 60 / boadSize);
        }
}

// int show_animal(int id, int boadSize){
//     int width, length;
//     width = length = 700 / boadSize;
	
//     int x = animals[id].x * length + 10;
//     int y = animals[id].y * width + 10;

//     al_draw_textf(font, al_map_rgb(100, 45, 114), x + length / 2, y + width / 2, ALLEGRO_ALIGN_CENTRE,"%d", id);
    
//     return 1;
// }

int show_object(int id, int boadSize){
    int width, length;
    width = length = 700 / boadSize;

    int x = animals[id].x * length + 10;
    int y = animals[id].y * width + 10;

    al_draw_filled_rectangle(x, y, x + length, y + width, al_map_rgb(190,156,84));
    al_draw_rectangle(x, y, x + length, y + width, al_map_rgb(158,153,101), 60 / boadSize);

    al_draw_textf(font, al_map_rgb(100, 45, 114), x + length / 2, y + width / 2, ALLEGRO_ALIGN_CENTRE,"%s", ch[id]);

    return 1;
}








