#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>


//functions:

void initAnimals();

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
