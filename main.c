#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>


//functions:

void initAnimals();

// stractuers for objects (mouses, cats, dogs)

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




int main()
{   
//    al_init();
//    al_init_font_addon();
//
//    ALLEGRO_DISPLAY * display = al_create_display(800 ,600);
//    ALLEGRO_FONT * font = al_create_builtin_font();
//	
//    al_clear_to_color(al_map_rgb(0, 0, 0));
//    al_draw_text(font, al_map_rgb(255, 255, 255),3, 300, 400, "Hello World");
//    al_flip_display();
//    al_rest(10.0);
    
}


void initAnimals(){

    animal[1].name = "bulldog";
    animal[1].energy = 5;
    animal[1].power = 5;
    animal[1].dogdefense = 30;

    animal[2].name = "pitbull";
    animal[2].energy = 2;
    animal[2].power = 2;
    animal[2].dogdefense = 15;

    animal[3].name = "Shepherd";
    animal[3].energy = 3;
    animal[3].power = 2;
    animal[3].dogdefense = 20;

    animal[4].name = "BulldogJr";
    animal[4].energy = 1;
    animal[4].power = 1;
    animal[4].dogdefense = 5;

    
}
