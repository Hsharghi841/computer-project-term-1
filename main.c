#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
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
}
