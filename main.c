/*#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define taleCode 27;
#define chocklet 28;
//functions:

void initAnimals();
//void initscrean();
void initwall(int n);
void init_chocklet_tale(int n);
// stractuers for objects (mice, cats, dogs)

typedef struct 
{
    char *name;
    unsigned short energy;
    unsigned short power;
    unsigned short score;
    unsigned short dogdefense;
    unsigned short x;
    unsigned short y;
} animal;

// 1 to 4 for dogs, 5 to 22 for mouses, 23 to 26 for cats
animal animals[26];


// arrys
int board[31][31][30];
int wall[31][31];


int main()
{
    int c;
	srand(time(0));
//   initscrean();
    scanf("%d",&c);
    initwall(c);
    for (int i = 0; i < c; i++)
    {
        for (int j = 0; j < c; j++)
        {

            printf("%d",wall[i][j]);
            
        }
        printf("\n");
    }
}


/*void initscrean()
{
	   // ALLEGRO_DISPLAY *display;
  //  ALLEGRO_BITMAP *cursor;
    ALLEGRO_MOUSE_STATE msestate;
  //  ALLEGRO_KEYBOARD_STATE kbdstate;
    al_init();
    al_init_font_addon();
    al_init_primitives_addon();
    al_install_mouse();
    al_install_keyboard();
    al_init_image_addon();
    //init_platform_specific();
    ALLEGRO_DISPLAY * display = al_create_display(800 ,600);
    ALLEGRO_FONT * font = al_create_builtin_font();
	al_hide_mouse_cursor(display);
    ALLEGRO_BITMAP *cursor=al_load_bitmap("cursor.tga");
    if (!cursor) {
      printf("Error loading cursor.tga\n");
    }
    int i=1,j=0,mode=1;
    while(1){
    	
    	j=(j+1)%400;
    	al_get_mouse_state(&msestate);
    	al_draw_bitmap(cursor,msestate.x,msestate.y,0);
    	//al_draw_text(font, al_map_rgb(255, 255, 255),3, 300, 400, "Hello World");
    	if(al_mouse_button_down(&msestate,i))
    		mode*=-1;
        if (mode==1)
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(cursor,msestate.x,msestate.y,0);
            al_draw_text(font, al_map_rgb(255, 255, 255),j, 300, 400, "Hello World");
            al_rest(0.05);
        }
        else
        {
            al_clear_to_color(al_map_rgb(0, 255, 255));
            al_draw_bitmap(cursor,msestate.x,msestate.y,0);
            al_draw_text(font, al_map_rgb(255, 50, 150),j, 300, 400, "shargi bebin");
			al_rest(0.05);            
        }
        
    	al_flip_display();
    //al_rest(10.0);
}*/
void initwall(int n)
{
    for (int i = 0; i < (n+1)/2; i++)
    {
        for (int j = 0; j < (n+1)/2; j++)
        {
            int number;
            number=rand()%40;
            if (number>0&&number<4)
            {
                wall[i][j]=number;
            }
        }
        for (int j =(n+1)/2+1 ; j < n; j++)
        {
            int number;
            number=rand()%40;
            if (number>0&&number<4)
            {
                wall[i][j]=number;
            }
        }
    }
    for (int i = (n+1)/2+1; i < n; i++)
    {
        for (int j = 0; j < (n+1)/2; j++)
        {
            int number;
            number=rand()%40;
            if (number>0&&number<4)
            {
                wall[i][j]=number;
            }
        }
        for (int j =(n+1)/2+1 ; j < n; j++)
        {
            int number;
            number=rand()%40;
            if (number>0&&number<4)
            {
                wall[i][j]=number;
            }
        }
    }
}
void init_chocklet_tale(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int number;
            number=rand()%25+3;
            if (number==1)
            {
                board[i][j][1]=number;
            }
        }
        
    }
}
void initAnimals(){

    animals[1].name = "bulldog";
    animals[1].energy = 5;
    animals[1].power = 5;
    animals[1].dogdefense = 30;

    animals[2].name = "pitbull";
    animals[2].energy = 2;
    animals[2].power = 2;
    animals[2].dogdefense = 15;

    animals[3].name = "Shepherd";
    animals[3].energy = 3;
    animals[3].power = 2;
    animals[3].dogdefense = 20;

    animals[4].name = "BulldogJr";
    animals[4].energy = 1;
    animals[4].power = 1;
    animals[4].dogdefense = 5;

    // 4 3-point mice 
    for (size_t i = 5; i < 9; i++)
    {
        animals[i].energy = 3;
        animals[i].score = 3;
    }
    // 6 2-point mice
    for (size_t i = 9; i < 15; i++)
    {
        animals[i].energy = 2;
        animals[i].score = 2;
    }
    // 8 1-point mice
    for (size_t i = 15; i < 23; i++)
    {
        animals[i].energy = 1;
        animals[i].score = 1;
    }
    // cats (this part of code will change!)
    for (size_t i = 23; i <= 26; i++)
    {
        animals[i].energy = 5;
        animals[i].power = 2;
    }
    
    
    
}
