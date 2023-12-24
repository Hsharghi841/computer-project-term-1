/*#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>*/

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>


// defines

#define sq(x) (x) * (x) // for square a number
#define TRAP 27
#define CHOCOLATE 28
#define FISH_2 32
#define FISH_3 33
#define FISH_4 34
int FISH[3] = {FISH_2, FISH_3, FISH_4};

//functions:

void initAnimals();
int abs(int x);
void sortObject(int id[], int idnum, int boardSize);
int startSettingBoard(int boardSize);
int putOnboard(int id, int width, int length);// putOnboard tries to put an object on board if can return 1 else 0 :
//void initscrean();
void initwall(int n);


// structures for objects (mice, cats, dogs)

typedef struct
{
    int ID;
    char * name;
    unsigned short energy;
    unsigned short power;
    unsigned short score;
    unsigned short dogdefense;
    unsigned short x;
    unsigned short y;
} animal;

// 1 to 4 for dogs, 5 to 22 for mice, 23 to 26 for cats
animal animals[27];
int board[31][31][30];
int wall[31][31];


int main(){
	srand(time(0));
    
    
    
    
    // int n = 15;
    // int a[4] = {27, 28, 29, 30};
	// sortObject(a, 4, n);

    // for (size_t i = 0; i < n; i++)
    // {
    //     for (size_t j = 0; j < n; j++)
    //     {
    //         printf("%d", !!board[i][j][1]);
    //     }
    //     printf("\n");
    // }
    



//    int c;
//	srand(time(0));
////   initscrean();
//    scanf("%d",&c);
//    initwall(c);
//    for (int i = 0; i < c; i++)
//    {
//        for (int j = 0; j < c; j++)
//        {
//
//            printf("%d",wall[i][j]);
//
//        }
//        printf("\n");
//    }
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



void initAnimals(){

    animals[1].name = "bulldog";
    animals[1].energy = 5;
    animals[1].power = 5;
    animals[1].dogdefense = 30;
    animals[1].ID = 1;

    animals[2].name = "pitbull";
    animals[2].energy = 2;
    animals[2].power = 2;
    animals[2].dogdefense = 15;
    animals[2].ID = 2;

    animals[3].name = "Shepherd";
    animals[3].energy = 3;
    animals[3].power = 2;
    animals[3].dogdefense = 20;
    animals[3].ID = 3;

    animals[4].name = "BulldogJr";
    animals[4].energy = 1;
    animals[4].power = 1;
    animals[4].dogdefense = 5;
    animals[4].ID = 4;

    // 4 3-point mice
    for (size_t i = 5; i < 9; i++)
    {
        animals[i].energy = 3;
        animals[i].score = 3;
        animals[i].ID = i;
    }
    // 6 2-point mice
    for (size_t i = 9; i < 15; i++)
    {
        animals[i].energy = 2;
        animals[i].score = 2;
        animals[i].ID = i;
    }
    // 8 1-point mice
    for (size_t i = 15; i < 23; i++)
    {
        animals[i].energy = 1;
        animals[i].score = 1;
        animals[i].ID = i;
    }
    // cats (this part of code will change!)
    for (size_t i = 23; i <= 26; i++)
    {
        animals[i].energy = 5;
        animals[i].power = 2;
        animals[i].ID = i;
    }
    
    
    
}

int abs(int x){
    if(x < 0)return -x;
    return x;
}

void sortObject(int id[], int idnum, int boardSize){

    int boolboard[31][31] = {{0}};
    float R = sqrt(boardSize * boardSize / idnum ) / 1.8;

    for (size_t j = 0; j < boardSize * boardSize; j++)
    {
        if(sq(boardSize / 2 - (j % boardSize)) + sq(boardSize / 2 - (j / boardSize)) <= sq(R * 2 / 3)){
            boolboard[j / boardSize][j % boardSize] = 1;
        }
    }
    
    for (size_t i = 0; i < idnum; i++)
    {
        int r = rand() % (boardSize * boardSize);
        int x = r % boardSize, y = r / boardSize;
        
        if(!boolboard[y][x]){
            for (size_t j = 0; j < boardSize * boardSize; j++)
            {
                if(sq(x - (j % boardSize)) + sq(y - (j / boardSize)) <= sq(R)){
                    boolboard[j / boardSize][j % boardSize] = 1;
                }
            }
            
            if(board[y][x][0] || board[y][x][1] || !putOnboard(id[i], y, x)){
                i--;
            }

        }
        else i--;
    }
}

int putOnboard(int id, int width, int length){
    if(0 < id && id < 27){
        board[width][length][board[width][length][0] + 2] = id;
        board[width][length][0]++;
        animals[id].x = length;
        animals[id].y = width;
        return 1;
    }
    {// must add code of objects in if
        if(!board[width][length][1]){
            board[width][length][1] = id;
            return 1;
        }
        else return 0;
    }
    //a display function must add in here:
    
    
    
}

int startSettingBoard(int boardSize){
    
    if(boardSize % 2 == 1) {
        // cats : (conditions must be change)
        if (1) {
            putOnboard(animals[23].ID, boardSize / 2 + 1, boardSize / 2);
        }
        if (1) {
            putOnboard(animals[24].ID, boardSize / 2, boardSize / 2 + 1);
        }
        if (1) {
            putOnboard(animals[25].ID, boardSize / 2 - 1, boardSize / 2);
        }
        if (1) {
            putOnboard(animals[26].ID, boardSize / 2, boardSize / 2 - 1);
        }
    }else{
    
    }
    printf("cats done!\n");
    
    // dogs :
    
    int dogs[] = {1, 2, 3, 4};
    sortObject(dogs, 4, boardSize);
    
    printf("dogs done!\n");
    // mice :
    
    int mice[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22};
    sortObject(mice, 18, boardSize);
    
    printf("mice done!\n");
    // fishes :
    
    int fishes[10];
    for (int i = 0; i < 10; ++i)
        fishes[i] = FISH[rand() % 3];
    
    sortObject(fishes, 10, boardSize);
    
    printf("fishes done!\n");
    // Chocolate :
    
    int chocolate[] = {CHOCOLATE, CHOCOLATE, CHOCOLATE, CHOCOLATE, CHOCOLATE, CHOCOLATE, CHOCOLATE, CHOCOLATE};
    sortObject(chocolate, 8, boardSize);
    
    printf("chocolates done!\n");
    // traps :
    
    int trap[] = {TRAP, TRAP, TRAP, TRAP, TRAP, TRAP, TRAP, TRAP};
    sortObject(trap, 8, boardSize);
    
    
    
}
