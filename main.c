    #include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>


//functions:

void initAnimals();
int abs(int x);

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
int bord[31][31][30];



int main()
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

void sortingbord(int size){


    // sorting dogs
    int dogsBord[31][31] = {{0}};

    for (size_t i = 1; i <= 4; i++)
    {
        int r = rand() % (size * size); 
        int x = r % size, y = r / size;
        if(!dogsBord[y][x]){
            for (size_t j = 0; j <= size * size; j++)
            {
                if(abs(x - (j % size)) * 2 <= (zize / 4) && abs(y - (j / size)) * 2 <= (zize / 4)){
                    dogsBord[j / size][j % size] = 1;
                }
            }
            
            putOnBord(i, y, x);

        }
        else i--;
    }
    
}


int abs(int x){
    if(x < 0)x = -x;
    return x;
}