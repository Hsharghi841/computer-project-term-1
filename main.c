#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

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



