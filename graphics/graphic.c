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
    char name[20];
    short energy;
    unsigned short power;
    unsigned short score;
    unsigned short dogdefense;
    unsigned short x;
    unsigned short y;
    unsigned short freaz;
    int id_mic[19];
    bool on_board;
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

extern enum page {endofGame, firstmenu, ingame, gameStarter, loadmenu};

#include "../graphics/graphic.h"


ALLEGRO_DISPLAY * display;

ALLEGRO_BITMAP * cursor, * selsction, * selsctionHavel, * background, * mygif, * scoreboardBMP, * playerSelectionBMP , * playerFreazeBMP;
ALLEGRO_BITMAP * dice[7],*anipic[35];

ALLEGRO_FONT * scoreboardFont, * numFont, * numFont2, * numFont2sml, * scoreboardFontsml, * namefont, * menuFont;

ALLEGRO_MOUSE_STATE msestate;

ALLEGRO_SAMPLE * selection_fail_audio;
ALLEGRO_SAMPLE * selection_audio;
ALLEGRO_SAMPLE_ID isPlayingSampleId;

button diceThrowBTN, playBTN, optionsBTN, loadBTN, exitBTN, backBTN, changeBTN, startBTN, pauseBTN, resumeBTN, saveBTN, mainMenuBTN;


extern animal animals[27];
extern int board[31][31][30];
extern int boardSize;
extern int wall[31][31];
extern turns catslist[4];
extern int catsNumber;
extern int roundLimit;
extern int playingRound;
extern int numfish;

int allegroINIT(){
	
	al_init();
	display = al_create_display(1280 ,720);
	al_hide_mouse_cursor(display);
	
    al_init_font_addon();
    al_init_ttf_addon();
	scoreboardFont = al_load_ttf_font("fonts/font.ttf", 30, 0);
	scoreboardFontsml = al_load_ttf_font("fonts/font.ttf", 20, 0);
	numFont = al_load_ttf_font("fonts/number font.ttf", 30, 0);
	numFont2 = al_load_ttf_font("fonts/number font 2.ttf", 30, 0);
	numFont2sml = al_load_ttf_font("fonts/number font 2.ttf", 25, 0);
    namefont = al_load_ttf_font("fonts/font.ttf", 100, 0);
    menuFont = al_load_ttf_font("fonts/menu font.ttf", 40, 0);
	
    al_init_primitives_addon();

    al_install_keyboard();
    
    al_install_mouse();
    
    al_init_image_addon(); 
	cursor = al_load_bitmap("cursor.png");
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
    playerFreazeBMP = al_load_bitmap("freazed_player.png");
    anipic[1]= al_load_bitmap("animals/bulldog.png");
    anipic[2]= al_load_bitmap("animals/doberman.png");
    anipic[3]= al_load_bitmap("animals/sheperd.png");
    anipic[4]= al_load_bitmap("animals/bulljr.png");
    for (size_t i = 5; i < 9; i++)
    {
        anipic[i]= al_load_bitmap("animals/mouse3.png");
    }
    for (size_t i = 9; i < 15; i++)
    {
        anipic[i]= al_load_bitmap("animals/mouse.png");
    }
    for (size_t i = 15; i < 23; i++)
    {
        anipic[i]= al_load_bitmap("animals/mouse1.png");
    }
    anipic[23]= al_load_bitmap("animals/cat1.png");
    anipic[24]= al_load_bitmap("animals/cat2.png");
    anipic[25]= al_load_bitmap("animals/cat3.png");
    anipic[26]= al_load_bitmap("animals/cat4.png");
    anipic[28]= al_load_bitmap("animals/chocolate.png");
    anipic[32]= al_load_bitmap("animals/fish4.png");
    anipic[33]= al_load_bitmap("animals/fish4.png");
    anipic[34]= al_load_bitmap("animals/fish4.png");

    diceThrowBTN.from.x = 885;
    diceThrowBTN.from.y = 570;
    diceThrowBTN.to.x = 1085;
    diceThrowBTN.to.y = 670;
    diceThrowBTN.icon = al_load_bitmap("buttons/trow dice button.png");

    int length = 290, height = 130; 
    playBTN.from.x = 1100 - length / 2;
    playBTN.from.y = 600 - height / 2;
    playBTN.to.x = 1100 + length / 2;
    playBTN.to.y = 600 + height / 2;
    playBTN.icon = al_load_bitmap("buttons/play.png");

    loadBTN.from.x = 794 - length / 2;
    loadBTN.from.y = 600 - height / 2;
    loadBTN.to.x = 794 + length / 2;
    loadBTN.to.y = 600 + height / 2;
    loadBTN.icon = al_load_bitmap("buttons/load.png");

    optionsBTN.from.x = 486 - length / 2;
    optionsBTN.from.y = 600 - height / 2;
    optionsBTN.to.x = 486 + length / 2;
    optionsBTN.to.y = 600 + height / 2;
    optionsBTN.icon = al_load_bitmap("buttons/options.png");

    exitBTN.from.x = 180 - length / 2;
    exitBTN.from.y = 600 - height / 2;
    exitBTN.to.x = 180 + length / 2;
    exitBTN.to.y = 600 + height / 2;
    exitBTN.icon = al_load_bitmap("buttons/exit.png");

    length = 200;
    height = 90;

    backBTN.from.x = 290 - length / 2;
    backBTN.from.y = 650 - height / 2;
    backBTN.to.x = 290 + length / 2;
    backBTN.to.y = 650 + height / 2;
    backBTN.icon = al_load_bitmap("buttons/back.png");

    startBTN.from.x = 990 - length / 2;
    startBTN.from.y = 650 - height / 2;
    startBTN.to.x = 990 + length / 2;
    startBTN.to.y = 650 + height / 2;
    startBTN.icon = al_load_bitmap("buttons/start.png");

    height = al_get_font_line_height(numFont2) + 10;
    length = height * 2.2;
    changeBTN.from.x = 1090 - length;
    changeBTN.from.y = 145;
    changeBTN.to.x = 1090;
    changeBTN.to.y = 145 + height;
    changeBTN.icon = al_load_bitmap("buttons/change.png");

    height = 90;
    length = height * 4.2;
    resumeBTN.from.x = 640 - length / 2;
    resumeBTN.from.y = 300 - height / 2;
    resumeBTN.to.x = 640 + length / 2;
    resumeBTN.to.y = 300 + height / 2;
    resumeBTN.icon = al_load_bitmap("buttons/resume.png");

    saveBTN.from.x = 640 - length / 2;
    saveBTN.from.y = 400 - height / 2;
    saveBTN.to.x = 640 + length / 2;
    saveBTN.to.y = 400 + height / 2;
    saveBTN.icon = al_load_bitmap("buttons/save.png");
    
    mainMenuBTN.from.x = 640 - length / 2;
    mainMenuBTN.from.y = 500 - height / 2;
    mainMenuBTN.to.x = 640 + length / 2;
    mainMenuBTN.to.y = 500 + height / 2;
    mainMenuBTN.icon = al_load_bitmap("buttons/main menu.png");


    height = 100;
    length = height;
    pauseBTN.from.x = 1120;
    pauseBTN.from.y = 570;
    pauseBTN.to.x = 1120 + length;
    pauseBTN.to.y = 570 + height;
    pauseBTN.icon = al_load_bitmap("buttons/pause.png");




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
    for(int i = 1;i <= 26;i++){
        if(!anipic[i]){
            printf("error loading anipic! %d",i);
            return 0;
        }
        
    }
    for(int i = 32;i <= 34;i++){
        if(!anipic[i]){
            printf("error loading anipic!");
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
	

	al_destroy_font(scoreboardFont);

    al_shutdown_font_addon();

	al_shutdown_primitives_addon();

	al_destroy_mouse_cursor(cursor);
	al_uninstall_mouse();

    al_uninstall_keyboard();

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
    
    for (size_t i = 0; i <= 34; i++){
        al_destroy_bitmap(anipic[i]);
    }
    
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
            al_draw_filled_rectangle(i,j,i+x,j+y, al_map_rgb(204, 191, 123));
            al_draw_rectangle(i,j,i+x,j+y, al_map_rgb(158,153,101),60 / boardSize);
        }
    
}

void show_wall(int i,int j,int x,int y,int x1,int y1,int x2,int y2, float thickness)
{
    if (wall[i][j]==1&&i!=boardSize-1)
    {
        al_draw_filled_rectangle(x1 - thickness / 2, y1, x + thickness / 2, y, al_map_rgb(46, 64, 28));
    }
    if (wall[i][j]==2&&j!=boardSize-1)
    {
        al_draw_filled_rectangle(x2, y2 - thickness / 2, x, y + thickness / 2, al_map_rgb(46, 64, 28));
    }
    if (wall[i][j]==3&&j!=boardSize-1&&i!=boardSize-1)
    {
        al_draw_filled_rectangle(x1 - thickness / 2, y1, x + thickness / 2, y, al_map_rgb(46, 64, 28));
        al_draw_filled_rectangle(x2, y2 - thickness / 2, x, y + thickness / 2, al_map_rgb(46, 64, 28));
    }
    if (i==boardSize-1&&wall[i][j]&&j!=boardSize-1)
    {
        al_draw_filled_rectangle(x2, y2 - thickness / 2, x, y + thickness / 2, al_map_rgb(46, 64, 28));
    }
    if(j==boardSize-1&&wall[i][j]&&i!=boardSize-1)
    {
        al_draw_filled_rectangle(x1 - thickness / 2, y1, x + thickness / 2, y, al_map_rgb(46, 64, 28));
    }
}

void show_walls(){
	int x ,y;
	x = y = 700 / boardSize;
    for (int i = 10; (i-10)/x < boardSize; i+=x)
        for (int j = 10; (j-10)/y < boardSize; j+=y){
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

    al_draw_filled_rectangle(x, y, x + length, y + width, al_map_rgb(204, 191, 123));
    al_draw_rectangle(x, y, x + length, y + width, al_map_rgb(158,153,101), 60 / boardSize);
	if((id>0&&id<27)||id>27){
		al_draw_scaled_bitmap(anipic[id],0,0,512,512,x,y,width,length,0);
        return 1;
    }
    return 0;
    
}

int show_components(){
    for (size_t i = 0; i < boardSize; i++)
        for (size_t j = 0; j < boardSize; j++)
        {
            if(board[i][j][0]){
                for(int k = 2; k <= board[i][j][0] + 1; k++){
                    show_animal(board[i][j][k]);
                }
            }

            if(board[i][j][1] && board[i][j][1] != 27){
                show_object(board[i][j][1], j, i);
            }
        }
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

int check_button(button b, int x, int y){
    return b.is_showing && (((b.from.x <= x && x <= b.to.x) && (b.from.y <= y && y <= b.to.y)) || 
            ((b.to.x <= x && x <= b.from.x) && (b.to.y <= y && y <= b.from.y)));
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
    al_draw_scaled_bitmap(scoreboardBMP, 0, 0, 1280, 720, 730, 100, 528, 292, 0);
    for(int i = 0; i < 4; i++){
        if(animals[get_cat_id(i + 1)].name[0]){
            if(strlen(animals[get_cat_id(i + 1)].name) < 7)
                al_draw_textf(scoreboardFont, al_map_rgb(0, 0, 0), 800 + i * 130, 125, ALLEGRO_ALIGN_CENTER, "%s", animals[get_cat_id(i + 1)].name);        
            else
                al_draw_textf(scoreboardFontsml, al_map_rgb(0, 0, 0), 800 + i * 130, 127, ALLEGRO_ALIGN_CENTER, "%s", animals[get_cat_id(i + 1)].name); 
            if(animals[get_cat_id(i + 1)].freaz)al_draw_scaled_bitmap(playerFreazeBMP, 0, 0, 320, 187, i * 130 + 736, 100, 127.5, 74.5, 0);
            al_draw_textf(numFont, al_map_rgb(0, 0, 0), 800 + i * 130, 203, ALLEGRO_ALIGN_CENTRE, "%d", animals[get_cat_id(i + 1)].score);
            al_draw_textf(numFont, al_map_rgb(0, 0, 0), 800 + i * 130, 275, ALLEGRO_ALIGN_CENTRE, "%d", animals[get_cat_id(i + 1)].energy);
            al_draw_textf(numFont, al_map_rgb(0, 0, 0), 800 + i * 130, 342, ALLEGRO_ALIGN_CENTRE, "%d", animals[get_cat_id(i + 1)].power);
        }        
    }
}

void show_turn(turns turn){
    if(turn)
        al_draw_scaled_bitmap(playerSelectionBMP, 0, 0, 320, 187, (turn - 1) * 130 + 736, 100, 127.5, 74.5, 0);
}

void show_round(int round){
    printf("updated\n");
    al_draw_filled_rectangle(994, 40, 1258, 90, al_map_rgb(0X43, 0X28, 0X18));
    al_draw_filled_rectangle(999, 45, 1253, 85, al_map_rgb(0x99, 0x58, 0x2a));
    al_draw_textf(scoreboardFont, al_map_rgb(0x6f, 0x1d, 0x1b), 1015, 52, ALLEGRO_ALIGN_LEFT, "round :");
    al_draw_textf(numFont, al_map_rgb(0x6f, 0x1d, 0x1b), 1170, 49, ALLEGRO_ALIGN_CENTRE, "%d", round);
}

void show_name_of_game(){
    al_draw_text(namefont, al_map_rgb(240, 45, 58), 640, 20, ALLEGRO_ALIGN_CENTRE, "Mr. Clobber's backyard");
}

void show_starting_menu(){
    al_draw_text(menuFont, al_map_rgb(240, 45, 58), 640, 30, ALLEGRO_ALIGN_CENTRE, "starting menu");

    al_draw_text(menuFont, al_map_rgb(67, 40, 24), 200, 150, ALLEGRO_ALIGN_LEFT, "size of board");
    al_draw_filled_rectangle(700, 150, 800, 150 + al_get_font_line_height(numFont2), al_map_rgb(255, 255, 255));
    al_draw_rectangle(700, 150, 800, 150 + al_get_font_line_height(numFont2), al_map_rgb(51, 53, 51), 1);
    al_draw_textf(numFont2, al_map_rgb(67, 40, 24), 750, 155, ALLEGRO_ALIGN_CENTRE, "%d", boardSize);

    al_draw_text(menuFont, al_map_rgb(67, 40, 24), 200, 200, ALLEGRO_ALIGN_LEFT, "rounds");
    al_draw_filled_rectangle(700, 200, 800, 200 + al_get_font_line_height(numFont2), al_map_rgb(255, 255, 255));
    al_draw_rectangle(700, 200, 800, 200 + al_get_font_line_height(numFont2), al_map_rgb(51, 53, 51), 1);
    al_draw_textf(numFont2, al_map_rgb(67, 40, 24), 750, 205, ALLEGRO_ALIGN_CENTRE, "%d", roundLimit);


    al_draw_text(menuFont, al_map_rgb(255, 0, 0), 200, 300, ALLEGRO_ALIGN_LEFT, "player 1");
    al_draw_filled_rectangle(600, 300, 850, 300 + al_get_font_line_height(numFont2), al_map_rgb(255, 255, 255));
    al_draw_rectangle(600, 300, 850, 300 + al_get_font_line_height(numFont2), al_map_rgb(51, 53, 51), 1);
    al_draw_text(scoreboardFont, al_map_rgb(67, 40, 24), 725, 308, ALLEGRO_ALIGN_CENTRE, animals[get_cat_id(cat1)].name);
    
    al_draw_text(menuFont, al_map_rgb(0, 255, 0), 200, 360, ALLEGRO_ALIGN_LEFT, "player 2");
    al_draw_filled_rectangle(600, 360, 850, 360 + al_get_font_line_height(numFont2), al_map_rgb(255, 255, 255));
    al_draw_rectangle(600, 360, 850, 360 + al_get_font_line_height(numFont2), al_map_rgb(51, 53, 51), 1);
    al_draw_text(scoreboardFont, al_map_rgb(67, 40, 24), 725, 368, ALLEGRO_ALIGN_CENTRE, animals[get_cat_id(cat2)].name);


    al_draw_text(menuFont, al_map_rgb(0, 0, 255), 200, 420, ALLEGRO_ALIGN_LEFT, "player 3");
    al_draw_filled_rectangle(600, 420, 850, 420 + al_get_font_line_height(numFont2), al_map_rgb(255, 255, 255));
    al_draw_rectangle(600, 420, 850, 420 + al_get_font_line_height(numFont2), al_map_rgb(51, 53, 51), 1);
    al_draw_text(scoreboardFont, al_map_rgb(67, 40, 24), 725, 428, ALLEGRO_ALIGN_CENTRE, animals[get_cat_id(cat3)].name);

    al_draw_text(menuFont, al_map_rgb(255, 255, 0), 200, 480, ALLEGRO_ALIGN_LEFT, "player 4");
    al_draw_filled_rectangle(600, 480, 850, 480 + al_get_font_line_height(numFont2), al_map_rgb(255, 255, 255));
    al_draw_rectangle(600, 480, 850, 480 + al_get_font_line_height(numFont2), al_map_rgb(51, 53, 51), 1);
    al_draw_text(scoreboardFont, al_map_rgb(67, 40, 24), 725, 488, ALLEGRO_ALIGN_CENTRE, animals[get_cat_id(cat4)].name);

}

void scan_from_display(char result[20]){
    
    al_draw_filled_rectangle(0, 0, 1280, 720, al_premul_rgba(51, 53, 51, 128));
    al_draw_filled_rectangle(300, 330, 980, 390, al_map_rgb(255, 255, 255));
    al_draw_text(numFont2, al_map_rgb(0, 0, 0), 640, 340, ALLEGRO_ALIGN_CENTRE, result);
    al_flip_display();
    // result[0] = 0;
    int len = strlen(result);
    char strcopy[20];
    strcpy(strcopy, result);
    bool showMouse = 1;

    ALLEGRO_EVENT event;
    ALLEGRO_EVENT_QUEUE * queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));


    while (1){
        al_wait_for_event(queue,&event);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            break;
        }
        
        if(event.type == ALLEGRO_EVENT_KEY_CHAR){
            if(event.keyboard.keycode == ALLEGRO_KEY_ENTER || event.keyboard.keycode == ALLEGRO_KEY_PAD_ENTER){
                return;
            }

            if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                strcpy(result, strcopy);
                return;
            }

            if(event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE){
                if(len)
                    result[--len] = '\0';
            }

            if(event.keyboard.keycode >= ALLEGRO_KEY_A && event.keyboard.keycode <= ALLEGRO_KEY_Z){
                int toascii = 'a' - ALLEGRO_KEY_A;
                if(event.keyboard.modifiers == ALLEGRO_KEYMOD_SHIFT || event.keyboard.modifiers == ALLEGRO_KEYMOD_CAPSLOCK)
                    toascii = 'A' - ALLEGRO_KEY_A;
                result[len++] = event.keyboard.keycode + toascii;
                result[len] = '\0';
            }

            if(event.keyboard.keycode >= ALLEGRO_KEY_0 && event.keyboard.keycode <= ALLEGRO_KEY_9){
                int toascii = '0' - ALLEGRO_KEY_0;
                
                result[len++] = event.keyboard.keycode + toascii;
                result[len] = '\0';
            }

            if(event.keyboard.keycode >= ALLEGRO_KEY_PAD_0 && event.keyboard.keycode <= ALLEGRO_KEY_PAD_9){
                int toascii = '0' - ALLEGRO_KEY_PAD_0;
                
                result[len++] = event.keyboard.keycode + toascii;
                result[len] = '\0';
            }

            al_draw_filled_rectangle(300, 330, 980, 390, al_map_rgb(255, 255, 255));
            al_draw_text(numFont2, al_map_rgb(0, 0, 0), 640, 340, ALLEGRO_ALIGN_CENTRE, result);
            al_flip_display();

        }
        


        
    }

    al_destroy_event_queue(queue);
    
    

}


enum page show_pause_menu(){
    bool showMouse = 1;
    enum page result;
    ALLEGRO_TIMER * timer = al_create_timer(1.0 / 60);
    al_start_timer(timer);
    
    ALLEGRO_EVENT event;
    ALLEGRO_EVENT_QUEUE * queue = al_create_event_queue();
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_display_event_source(display));

    
    al_draw_filled_rectangle(0, 0, 1280, 720, al_premul_rgba(51, 53, 51, 128));
    resumeBTN.is_showing = 1;
    show_button(resumeBTN);
    saveBTN.is_showing = 1;
    show_button(saveBTN);
    mainMenuBTN.is_showing = 1;
    show_button(mainMenuBTN);
    
    ALLEGRO_BITMAP * oldDisplay = al_clone_bitmap(al_get_backbuffer(display));

    while (1){
        al_wait_for_event(queue,&event);

        if(event.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY){
            showMouse = 0;
        }

        if(event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY){
            showMouse = 1;
        }

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            result = endofGame;
            break;
        }

        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){

            if(check_button(resumeBTN, event.mouse.x, event.mouse.y)){
                result = ingame;
                break;
            }

            if(check_button(saveBTN, event.mouse.x, event.mouse.y)){
                char saveName[28];
                char Direction[80] = "./saves/";
                char number[8] = {0};
                strcpy(saveName, "name of file");
                scan_from_display(saveName);
                strcat(Direction, saveName);
                strcat(Direction, ".dat");
                FILE * saveFile = fopen(Direction, "r+b");
                int fileCount;
                if(saveFile){
                    
                    fclose(saveFile);
                    Direction[strlen(Direction) - 4] = 0;
                    fileCount = 2;
                    sprintf(number, "(%d)", fileCount);
                    strcat(Direction, number);
                    strcat(Direction, ".dat");
                    saveFile = fopen(Direction, "r+b");
                    while (saveFile){
                        fclose(saveFile);
                        fileCount++;
                        int i;
                        for(i = strlen(Direction) - 1; Direction[i] != '('; i--);
                        Direction[i] = 0;
                        sprintf(number, "(%d)", fileCount);
                        strcat(Direction, number);
                        strcat(Direction, ".dat");
                        saveFile = fopen(Direction, "r+b");
                    }
                    
                }
                
                {
                    FILE * saveNamesfile = fopen("./saves/save list.txt", "r+t");
                    if(!saveNamesfile){
                        saveNamesfile = fopen("./saves/save list.txt", "w+t");
                        fprintf(saveNamesfile, "1- %s\n", saveName);
                    }else{
                        int n;
                        do{
                            char temp[20];
                            fscanf(saveNamesfile, "%d- %s", &n, &temp);
                        }while(!feof(saveNamesfile));
                        n++;
                        strcat(saveName, number);
                        fprintf(saveNamesfile, "%d- %s\n", n, saveName);
                        
                        
                    }
                    fclose(saveNamesfile);
                }

                saveFile = fopen(Direction, "wb");
                fwrite(animals, sizeof(animal), 27, saveFile);
                fwrite(board, sizeof(int), 31 * 31 * 30, saveFile);
                fwrite(&boardSize, sizeof(int), 1, saveFile);
                fwrite(wall, sizeof(int), 31 * 31, saveFile);
                fwrite(catslist, sizeof(turns), 4, saveFile);
                fwrite(&catsNumber, sizeof(int), 1, saveFile);
                fwrite(&roundLimit, sizeof(int), 1, saveFile);
                fwrite(&playingRound, sizeof(int), 1, saveFile);
                fwrite(&numfish, sizeof(int), 1, saveFile);
                fclose(saveFile);

                result = ingame;
                break;
                
            }

            if(check_button(mainMenuBTN, event.mouse.x, event.mouse.y)){
                result = firstmenu;
                break;
            }

        }

        if(event.type == ALLEGRO_EVENT_TIMER){
            
            al_draw_bitmap(oldDisplay, 0, 0, 0);




            if(showMouse)put_mouse();

            al_flip_display();
        }


        
    }
    al_destroy_event_queue(queue);
    al_stop_timer(timer);
    al_destroy_timer(timer);

    playBTN.is_showing = 0;
    loadBTN.is_showing = 0;
    optionsBTN.is_showing = 0;
    exitBTN.is_showing = 0;

    return result;
}

enum page wait_for_click(){
    bool showMouse = 1;
    enum page result;

    ALLEGRO_TIMER * timer = al_create_timer(1.0 / 60);
    al_start_timer(timer);
    
    ALLEGRO_EVENT event;
    ALLEGRO_EVENT_QUEUE * queue = al_create_event_queue();
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_display_event_source(display));


    ALLEGRO_BITMAP * oldDisplay = al_clone_bitmap(al_get_backbuffer(display));


    while (1){
        al_wait_for_event(queue,&event);

        if(event.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY){
            showMouse = 0;
        }

        if(event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY){
            showMouse = 1;
        }

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            result = endofGame;
            break;
        }

        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            result = ingame;
            break;
        }

        if(event.type == ALLEGRO_EVENT_TIMER){
            
            al_draw_bitmap(oldDisplay, 0, 0, 0);




            if(showMouse)put_mouse();

            al_flip_display();
        }

    }

    al_destroy_event_queue(queue);
    al_stop_timer(timer);
    al_destroy_timer(timer);

}
enum page move_animation(coordinates avalie,coordinates sanavie,int id)
{
    enum page page;
    bool showMouse = 1;

    int length, height;
    length = height = 700 / boardSize;

    float dx = (sanavie.x - avalie.x) * length;
    float dy = (sanavie.y - avalie.y) * height;
    float x = avalie.x * length + 10;
    float y = avalie.y * height + 10;


    ALLEGRO_TIMER * timer = al_create_timer(1.0 / 60);
    al_start_timer(timer);

    ALLEGRO_EVENT event;
    ALLEGRO_EVENT_QUEUE * queue = al_create_event_queue();
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_display_event_source(display));

    show_background();
    show_button(pauseBTN);
    show_board();
    show_components();
    show_walls();
    show_scoreboard();
    show_round(playingRound);
    show_dice(dice, 0);

    
    ALLEGRO_BITMAP * oldDisplay = al_clone_bitmap(al_get_backbuffer(display));


    while (1){

        al_wait_for_event(queue,&event);

        if(event.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY){
            showMouse = 0;
        }

        if(event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY){
            showMouse = 1;
        }

        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){

        }

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            page = endofGame;
            break;
        }

        if(event.type == ALLEGRO_EVENT_TIMER){

            al_draw_bitmap(oldDisplay, 0, 0, 0);
            
            
            
            al_draw_filled_rectangle(((int)(x - 10) / length) * length + 10, ((int)(y - 10) / height) * height + 10,(((int)(x - 10) / length) + 1) * length + 10, (((int)(y - 10) / height) + 1) * height + 10, al_map_rgb(204, 191, 123));
            al_draw_filled_rectangle(sanavie.x*(length)+10,sanavie.y*(height)+10,(sanavie.x + 1)*length+10,(sanavie.y + 1)*(height)+10, al_map_rgb(204, 191, 123));
            al_draw_rectangle(((int)(x - 10) / length) * length + 10, ((int)(y - 10) / height) * height + 10,(((int)(x - 10) / length) + 1) * length + 10, (((int)(y - 10) / height) + 1) * height + 10, al_map_rgb(158,153,101),60 / boardSize);
            al_draw_rectangle(sanavie.x*(length)+10,sanavie.y*(height)+10,(sanavie.x + 1)*length+10,(sanavie.y + 1)*(height)+10, al_map_rgb(158,153,101),60 / boardSize);
            int x1 = avalie.x, y1 = avalie.y;
            show_wall(y1, x1, (x1 + 1) * length, (y1 + 1) * height, (x1) * length, (y1 + 1) * height, (x1 + 1) * height, (y1) * height, boardSize / 60);
            x1--;
            show_wall(y1, x1, (x1 + 1) * length, (y1 + 1) * height, (x1) * length, (y1 + 1) * height, (x1 + 1) * height, (y1) * height, boardSize / 60);
            x1--;
            show_wall(y1, x1, (x1 + 1) * length, (y1 + 1) * height, (x1) * length, (y1 + 1) * height, (x1 + 1) * height, (y1) * height, boardSize / 60);
            x1++;
            y1--;
            show_wall(y1, x1, (x1 + 1) * length, (y1 + 1) * height, (x1) * length, (y1 + 1) * height, (x1 + 1) * height, (y1) * height, boardSize / 60);
            y1 += 2;
            show_wall(y1, x1, (x1 + 1) * length, (y1 + 1) * height, (x1) * length, (y1 + 1) * height, (x1 + 1) * height, (y1) * height, boardSize / 60);
            x1++;
            show_wall(y1, x1, (x1 + 1) * length, (y1 + 1) * height, (x1) * length, (y1 + 1) * height, (x1 + 1) * height, (y1) * height, boardSize / 60);
            y1 -= 2;
            show_wall(y1, x1, (x1 + 1) * length, (y1 + 1) * height, (x1) * length, (y1 + 1) * height, (x1 + 1) * height, (y1) * height, boardSize / 60);
            y1--;
            show_wall(y1, x1, (x1 + 1) * length, (y1 + 1) * height, (x1) * length, (y1 + 1) * height, (x1 + 1) * height, (y1) * height, boardSize / 60);
            x1++;
            y1++;
            show_wall(y1, x1, (x1 + 1) * length, (y1 + 1) * height, (x1) * length, (y1 + 1) * height, (x1 + 1) * height, (y1) * height, boardSize / 60);
            y1++;
            show_wall(y1, x1, (x1 + 1) * length, (y1 + 1) * height, (x1) * length, (y1 + 1) * height, (x1 + 1) * height, (y1) * height, boardSize / 60);
            al_draw_scaled_bitmap(anipic[id],0,0,512,512,x, y,length,height,0);

            x += dx / 30;
            y += dy / 30;

            
            if(1 > (x - (sanavie.x * length + 10)) && -1 < (x - (sanavie.x * length + 10)) && 1 > (y - (sanavie.y * height + 10)) && -1 < (y - (sanavie.y * height + 10))){
                break;
            }
            
            if(showMouse)put_mouse();
            al_flip_display();
        }


	}
    al_destroy_event_queue(queue);
    al_stop_timer(timer);
    al_destroy_timer(timer);
    return page;
}







