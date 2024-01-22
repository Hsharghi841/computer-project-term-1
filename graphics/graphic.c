typedef struct button button;
typedef struct animal animal;
typedef struct coordinates coordinates;
typedef enum direction direction;
typedef enum turns turns;
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>
#include <string.h>

#define get_cat_id(x) (x) + 22

extern struct animal{
    int ID;
    char name[11];
    unsigned short energy;
    unsigned short power;
    unsigned short score;
    unsigned short dogdefense;
    unsigned short x;
    unsigned short y;
    unsigned short freaz;
    int id_mic[19];
};

extern struct coordinates {
    int x;
    int y;
};


extern struct button {
    ALLEGRO_BITMAP * icon;
    coordinates from;
    coordinates to;
    bool is_showing;
};

extern enum direction {None , Up, Right, Down, Left};

extern enum turns {none, cat1, cat2, cat3, cat4};

#include "../graphics/graphic.h"


ALLEGRO_DISPLAY * display;

ALLEGRO_BITMAP * cursor, * selsction, * selsctionHavel, * background, * mygif, * scoreboardBMP, * playerSelectionBMP;
ALLEGRO_BITMAP * dice[7];

ALLEGRO_FONT * font, * numFont, * fontsml;

ALLEGRO_MOUSE_STATE msestate;

ALLEGRO_SAMPLE * selection_fail_audio;
ALLEGRO_SAMPLE * selection_audio;
ALLEGRO_SAMPLE_ID isPlayingSampleId;

button diceThrowBTN;


extern animal animals[27];
extern int boardSize;
extern int wall[31][31];
extern turns catslist[4];
extern int catsNumber;

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
    al_init_ttf_addon();
	font = al_load_ttf_font("fonts/font.ttf", 30, 0);
	fontsml = al_load_ttf_font("fonts/font.ttf", 20, 0);
	numFont = al_load_ttf_font("fonts/number font.ttf", 50, 0);
    
	
    al_init_primitives_addon();
    
    al_install_mouse();
    
    al_init_image_addon(); 
	cursor = al_load_bitmap("cursor.tga");
    selsction = al_load_bitmap("selection.png");
    selsctionHavel = al_load_bitmap("selection_havel.png");
    background = al_load_bitmap("background.jpg");
    dice[0] = al_load_bitmap("dice/dice_0.png");
    dice[1] = al_load_bitmap("dice/dice_1.png");
    dice[2] = al_load_bitmap("dice/dice_2.png");
    dice[3] = al_load_bitmap("dice/dice_3.png");
    dice[4] = al_load_bitmap("dice/dice_4.png");
    dice[5] = al_load_bitmap("dice/dice_5.png");
    dice[6] = al_load_bitmap("dice/dice_6.png");
    scoreboardBMP = al_load_bitmap("scoreboard.png");
    playerSelectionBMP = al_load_bitmap("select_player.png");

    diceThrowBTN.from.x = 885;
    diceThrowBTN.from.y = 570;
    diceThrowBTN.to.x = 1085;
    diceThrowBTN.to.y = 670;
    diceThrowBTN.icon = al_load_bitmap("buttons/trow dice button.png");

    if(!diceThrowBTN.icon){
        printf("error loading btn!");
        return 0;
    }
    
    for(int i = 0;i <= 6;i++){
        if(!dice[i]){
            printf("error loading dice!");
            return 0;
        }
        
    }

    
	if (!cursor) {
      printf("Error loading cursor.tga\n");
      return 0;
    }
	
	if (!selsction) {
      printf("Error loading cursor.tga\n");
      return 0;
    }
	
	if (!selsctionHavel) {
      printf("Error loading cursor.tga\n");
      return 0;
    }

    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(2);
    selection_fail_audio = al_load_sample("./audios/board select fail.wav");
    if(!selection_fail_audio){
        printf("audio error!");
    }
    selection_audio = al_load_sample("./audios/blub.wav");
    if(!selection_audio){
        printf("audio error!");
    }



    return 1;
}

int allegroDESTROY(){
	

	al_destroy_font(font);

    al_shutdown_font_addon();

	al_shutdown_primitives_addon();

	al_destroy_mouse_cursor(cursor);
	al_uninstall_mouse();

	al_shutdown_image_addon();
    al_destroy_bitmap(cursor);
    al_destroy_bitmap(selsction);
    al_destroy_bitmap(selsctionHavel);
    al_destroy_bitmap(background);
    al_destroy_bitmap(mygif);
    for (size_t i = 0; i <= 6; i++){
        al_destroy_bitmap(dice[i]);
    }
    al_destroy_bitmap(scoreboardBMP);
    al_destroy_bitmap(playerSelectionBMP);
    
    
    al_destroy_sample(selection_fail_audio);
    al_uninstall_audio();
	
	al_destroy_display(display);
	return 1;
}

int put_mouse(){
	al_get_mouse_state(&msestate);
	al_draw_bitmap(cursor,msestate.x,msestate.y,0);
    al_draw_bitmap(cursor,msestate.x,msestate.y,0);
	return 1;
}

void show_board(){
    int x,y;
    x=y=700 /boardSize;
    for (int i = 10; (i-10)/x < boardSize; i+=x)
        for (int j = 10; (j-10)/y < boardSize; j+=y){
            al_draw_filled_rectangle(i,j,i+x,j+y, al_map_rgb(190,156,84));
            al_draw_rectangle(i,j,i+x,j+y, al_map_rgb(158,153,101),60 / boardSize);
        }
    
}

void show_wall(int i,int j,int x,int y,int x1,int y1,int x2,int y2, float thickness)
{
    if (wall[i][j]==1)
    {
        al_draw_filled_rectangle(x1 - thickness / 2, y1, x + thickness / 2, y, al_map_rgb(146, 255, 71));
    }
    if (wall[i][j]==2)
    {
        al_draw_filled_rectangle(x2, y2 - thickness / 2, x, y + thickness / 2, al_map_rgb(146, 255, 71));
    }
    if (wall[i][j]==3)
    {
        al_draw_filled_rectangle(x1 - thickness / 2, y1, x + thickness / 2, y, al_map_rgb(146, 255, 71));
        al_draw_filled_rectangle(x2, y2 - thickness / 2, x, y + thickness / 2, al_map_rgb(146, 255, 71));
    }
}

void show_walls(){
	int x ,y;
	x = y = 700 / boardSize;
    for (int i = 10; (i-10)/x < boardSize-1; i+=x)
        for (int j = 10; (j-10)/y < boardSize-1; j+=y){
           	show_wall(((i-10)/x),((j-10)/y),i+x,j+y,i+x,j,i,j+y, 60 / boardSize);
        }
}

int show_animal(int id){
    // printf("id : %d  x : %d  y : %d\n", id, animals[id].x, animals[id].y);
    return show_object(id, animals[id].x, animals[id].y);
}

int show_object(int id, int x, int y){
    int width, length;
    width = length = 700 / boardSize;
    x = x * length + 10;
    y = y * width + 10;

    al_draw_filled_rectangle(x, y, x + length, y + width, al_map_rgb(190,156,84));
    al_draw_rectangle(x, y, x + length, y + width, al_map_rgb(158,153,101), 60 / boardSize);
	//تصویر اینجا اضافه گردد
    al_draw_textf(fontsml, al_map_rgb(100, 45, 114), x + length / 2, y + width / 2, ALLEGRO_ALIGN_CENTRE,"%s", ch[id]);

    return 1;
}

int show_slection_hover(int x, int y){
    int length, width;
    length = width = 700 /boardSize;
    
    x = ((x - 10) / length) * length + 10;
    y = ((y - 10) / width) * width + 10;
    al_draw_scaled_bitmap(selsctionHavel, 0, 0, 250, 243, x, y, length, width, ALLEGRO_FLIP_HORIZONTAL);
    return 1;
    
    
}



void show_slections(coordinates selections[], int n){
    int length, width;
    length = width = 700 /boardSize;

    for (size_t i = 0; i < n; i++)
    {
        al_draw_scaled_bitmap(selsction, 0, 0, 250, 243, selections[i].x * length + 10, selections[i].y * width + 10, length, width, 0);
    }
    // printf("*********************\n");
}

int is_mouse_on_Board(int x, int y){
    int length, width;
    length = width = 700 /boardSize;
    return x > 10 && x < length * boardSize + 10 && y > 10 && y < width * boardSize + 10 ;
}

int is_mouse_nextto(int x, int y, int xboard, int yboard){
    int length, width;
    length = width = 700 /boardSize;
    x = ((x - 10) / length);
    y = ((y - 10) / width);
    
    return (y == yboard && (x == xboard + 1 || x == xboard - 1)) || (x == xboard && (y == yboard + 1 || y == yboard - 1));
}

void find_cordinate_on_board(int x, int y, int *xBoard, int *yBoard){
    int length, width;
    length = width = 700 /boardSize;
    *xBoard = ((x - 10) / length);
    *yBoard = ((y - 10) / width);
}

void show_background(){
    al_draw_scaled_bitmap(background, 0, 0, 1920, 1080, 0, 0, 1280, 720, 0);
}

void show_button(button btn){
    al_draw_scaled_bitmap(btn.icon, 0, 0, al_get_bitmap_width(btn.icon), al_get_bitmap_height(btn.icon), btn.from.x, btn.from.y, btn.to.x - btn.from.x, btn.to.y - btn.from.y, 0);
}

void show_dice(int die[4], bool reset){
    static mydice[4];
    if(reset)
        for (size_t i = 0; i < 4; i++){
            if(die[i] == -1)mydice[i] = rand() % 6 + 1;
            else mydice[i] = die[i];
        }
    
    int x = 740;
    for (size_t i = 0; i < 4; i++){
        al_draw_scaled_bitmap(dice[mydice[i]], 0, 0, 54, 53, x, 400, 120, 120, 0);
        x += 130;
    }
}

void show_scoreboard(){
    al_draw_scaled_bitmap(scoreboardBMP, 0, 0, 1280, 720, 740, 100, 510, 287, 0);
    for(int i = 0; i < 4; i++){
        if(animals[get_cat_id(i + 1)].name[0] - '0'){
            if(strlen(animals[get_cat_id(i + 1)].name) < 7)
                al_draw_textf(font, al_map_rgb(0, 0, 0), 800 + i * 130, 125, ALLEGRO_ALIGN_CENTER, "%s", animals[get_cat_id(i + 1)].name);        
            else
                al_draw_textf(fontsml, al_map_rgb(0, 0, 0), 800 + i * 130, 127, ALLEGRO_ALIGN_CENTER, "%s", animals[get_cat_id(i + 1)].name);        
            al_draw_textf(numFont, al_map_rgb(0, 0, 0), 800 + i * 130, 195, ALLEGRO_ALIGN_CENTRE, "%d", animals[get_cat_id(i + 1)].score);
            al_draw_textf(numFont, al_map_rgb(0, 0, 0), 800 + i * 130, 270, ALLEGRO_ALIGN_CENTRE, "%d", animals[get_cat_id(i + 1)].energy);
            al_draw_textf(numFont, al_map_rgb(0, 0, 0), 800 + i * 130, 337, ALLEGRO_ALIGN_CENTRE, "%d", animals[get_cat_id(i + 1)].power);
        }        
    }
}









