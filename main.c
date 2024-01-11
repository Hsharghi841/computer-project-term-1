#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "./graphics/graphic.h"
//

extern ALLEGRO_DISPLAY * display;

// defines

#define sq(x) (x) * (x) // for square a number
#define TRAP 27
#define CHOCOLATE 28
#define FISH_2 32
#define FISH_3 33
#define FISH_4 34
int FISH[3] = {FISH_2, FISH_3, FISH_4};
enum direction {None , Up, Right, Down, Left};
typedef enum direction direction;

//functions:

void initAnimals();
int abs(int x);
void sortObject(int id[], int idnum, int boardSize);
int startSettingBoard(int boardSize);
int putOnboard(int id, int width, int length);// putOnboard tries to put an object on board if can return 1 else 0 :
void initwall(int n);
void show_board(int n);
int show_components(int boadSize);
void move(int id,direction masir[5],int tedadgam);
void delete_id(int id,int i,int j);

// structures for objects (mice, cats, dogs)

struct animal{
    int ID;
    char * name;
    unsigned short energy;
    unsigned short power;
    unsigned short score;
    unsigned short dogdefense;
    unsigned short x;
    unsigned short y;
    unsigned short freaz;
    int id_mic[19];
};

typedef struct animal animal;




// 1 to 4 for dogs, 5 to 22 for mice, 23 to 26 for cats
animal animals[27];
int board[31][31][30];
int wall[31][31];


int main(){
    if(!None){
        printf("none is false");
    }
    int n;
	srand(time(0));
    scanf("%d",&n);
    
    allegroINIT();
    		        
    initwall(n);
    startSettingBoard(n);

    ALLEGRO_TIMER * timer = al_create_timer(1.0 / 60);
    al_start_timer(timer);


    ALLEGRO_EVENT event;
    ALLEGRO_EVENT_QUEUE * queue = al_create_event_queue();
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_display_event_source(display));
    
    _Bool showMouse = 1;
    _Bool needUpdateDisplay = 1;
    ALLEGRO_BITMAP * oldDisplay;
    
    while(1){
    	al_wait_for_event(queue,&event);



        if(event.type == ALLEGRO_EVENT_MOUSE_AXES){

        }

        if(event.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY){
            showMouse = 0;
        }

        if(event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY){
            showMouse = 1;
        }

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            break;
        }


        if(event.type == ALLEGRO_EVENT_TIMER){
            if(needUpdateDisplay){
                al_clear_to_color(al_map_rgb(0, 0, 0));
                show_board(n);
                show_components(n);
                show_walls(n);
                oldDisplay = al_clone_bitmap(al_get_backbuffer(display));
                needUpdateDisplay = 0;
            }else{
                al_draw_bitmap(oldDisplay, 0, 0, 0);
            }
            if(showMouse)put_mouse();
            al_flip_display();
        }

    


    	
	}
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    allegroDESTROY();	        
}

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
    // cats : (conditions must be change)

    if(boardSize % 2 == 1) {
        
        for (size_t i = 23; i <= 26; i++)
        {
            if (1) {
                putOnboard(i, boardSize / 2 , boardSize / 2);
            }
        }

    }else{
        int r = rand() % 4;

        for (size_t i = 23; i <= 26; i++)
        {
            if (1) {
                putOnboard(i, boardSize / 2 - r / 2 , boardSize / 2 - r % 2);
            }
        }
        
    }
    
    // dogs :
    
    int dogs[] = {1, 2, 3, 4};
    sortObject(dogs, 4, boardSize);
    
    // mice :
    
    int mice[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22};
    sortObject(mice, 18, boardSize);
    
    // fishes :
    
    int fishes[10];
    for (int i = 0; i < 10; ++i)
        fishes[i] = FISH[rand() % 3];
    
    sortObject(fishes, 10, boardSize);
    
    // Chocolate :
    
    int chocolate[] = {CHOCOLATE, CHOCOLATE, CHOCOLATE, CHOCOLATE, CHOCOLATE, CHOCOLATE, CHOCOLATE, CHOCOLATE};
    sortObject(chocolate, 8, boardSize);
    
    // traps :
    
    int trap[] = {TRAP, TRAP, TRAP, TRAP, TRAP, TRAP, TRAP, TRAP};
    sortObject(trap, 8, boardSize);
    
    
    
}

int show_components(int boardSize){
    for (size_t i = 0; i < boardSize; i++)
        for (size_t j = 0; j < boardSize; j++)
        {
            if(board[i][j][0]){
                for(int k = 2; k <= board[i][j][0] + 1; k++){
                    show_object(board[i][j][k], boardSize);
                }
            }

            if(board[i][j][1]){
                show_object(board[i][j][1], boardSize);
            }
        }
}

void move(int id,direction masir[5],int tedadgam){
    int i,j,a,b,min,swich,bmin;
    for (size_t k = 0; k < tedadgam; k++)
    {
        if (masir[k]==Right&&animals[id].power>0)
        {
            j=animals[id].x;
            i=animals[id].y;
            delete_id(id,i,j);
            j++;
            putOnboard(id,i,j);
            if (id>0&&id<5)
            {
                for ( a = 2; a < board[i][j][0]+2; a++)
                {
                    //if (board[i][j][a]>22&&board[i][j][a]<27)
                        //war betwean id and board[i][j][a]
                }
            }
            else if (id>4&&id<23)
            {
                for ( a = 2; a < board[i][j][0]+2; a++)
                    if (board[i][j][a]>22&&board[i][j][a]<27)
                    {
                        delete_id(id,i,j);
                        animals[board[i][j][a]].score+=animals[id].score;
                        animals[board[i][j][a]].id_mic[0]++;
                        animals[board[i][j][a]].id_mic[animals[board[i][j][a]].id_mic[0]]=id;
                    }
            }
            else if (id>22&&id<27)
            {
                animals[id].energy--;
                swich=1;
                a=1;
                if(board[i][j][a]==TRAP)
                {
                    if (animals[id].id_mic[0])
                    {
                        min=animals[id].id_mic[1];
                        bmin=1;
                        for ( b = 2; b< animals[id].id_mic[0]+1; b++)
                        {
                            if(min>animals[id].id_mic[b])
                            {
                                min=animals[id].id_mic[b];
                                bmin=b;
                            }
                        }
                        for ( b = bmin; b < animals[id].id_mic[0]; b++)
                            animals[id].id_mic[b]=animals[id].id_mic[b+1];
                        animals[id].id_mic[b]=0;
                        animals[id].score-=animals[min].score;
                        animals[id].id_mic[0]--;
                        putOnboard(min,animals[id].y,animals[id].x);
                    }
                    else
                    {
                        if(animals[id].power>2)
                            animals[id].power-=2;
                        else
                        {
                            //در اینجا باید 3 تا از انرژی اش کم گردد
                        }
                    }
                }
                else if(board[i][j][a]==CHOCOLATE)
                    animals[id].power++;
                else if(board[i][j][a]==FISH_2)
                {
                    animals[id].energy+=2;
                    board[i][j][a]=0;
                }
                else if(board[i][j][a]==FISH_3)
                {
                    animals[id].energy+=3;
                    board[i][j][a]=0;
                }
                else if(board[i][j][a]==FISH_4)
                {
                    animals[id].energy+=4;
                    board[i][j][a]=0;
                }
                for ( a = 2; a < board[i][j][0]+2&&swich; a++)
                {
                    if (board[i][j][a]>1&&board[i][j][a]<5)
                    {
                        //war betwean id and board[i][j][a]
                    }
                    else if (board[i][j][a]>4&&board[i][j][a]<23)
                    {
                        delete_id(board[i][j][a],i,j);
                        animals[id].score+=animals[board[i][j][a]].score;
                        animals[id].id_mic[0]++;
                        animals[id].id_mic[animals[id].id_mic[0]]=board[i][j][a];
                    }
                    if (board[i][j][a]>22&&board[i][j][a]<27)
                    {
                        //war betwean id and board[i][j][a]
                    }
                }
            }
        }
        else if (masir[k]==Left&&animals[id].power>0)
        {
            j=animals[id].x;
            i=animals[id].y;
            delete_id(id,i,j);
            j--;
            putOnboard(id,i,j);
            if (id>0&&id<5)
            {
                for ( a = 2; a < board[i][j][0]+2; a++)
                {
				
                    //if (board[i][j][a]>22&&board[i][j][a]<27)
                        //war betwean id and board[i][j][a]
                }
            }
            else if (id>4&&id<23)
            {
                for ( a = 2; a < board[i][j][0]+2; a++)
                    if (board[i][j][a]>22&&board[i][j][a]<27)
                    {
                        delete_id(id,i,j);
                        animals[board[i][j][a]].score+=animals[id].score;
                        animals[board[i][j][a]].id_mic[0]++;
                        animals[board[i][j][a]].id_mic[animals[board[i][j][a]].id_mic[0]]=id;
                    }
            }
            else if (id>22&&id<27)
            {
                animals[id].energy--;
                swich=1;
                a=1;
                if(board[i][j][a]==TRAP)
                {
                    if (animals[id].id_mic[0])
                    {
                        min=animals[id].id_mic[1];
                        bmin=1;
                        for ( b = 2; b< animals[id].id_mic[0]+1; b++)
                        {
                            if(min>animals[id].id_mic[b])
                            {
                                min=animals[id].id_mic[b];
                                bmin=b;
                            }
                        }
                        for ( b = bmin; b < animals[id].id_mic[0]; b++)
                            animals[id].id_mic[b]=animals[id].id_mic[b+1];
                        animals[id].id_mic[b]=0;
                        animals[id].score-=animals[min].score;
                        animals[id].id_mic[0]--;
                        putOnboard(min,animals[id].y,animals[id].x);
                    }
                    else
                    {
                        if(animals[id].power>2)
                            animals[id].power-=2;
                        else
                        {
                            //در اینجا باید 3 تا از انرژی اش کم گردد
                        }
                    }
                }
                else if(board[i][j][a]==CHOCOLATE)
                {
                    animals[id].power++;
                    board[i][j][a]=0;
                }
                else if(board[i][j][a]==FISH_2)
                {
                    animals[id].energy+=2;
                    board[i][j][a]=0;
                }
                else if(board[i][j][a]==FISH_3)
                {
                    animals[id].energy+=3;
                    board[i][j][a]=0;
                }
                else if(board[i][j][a]==FISH_4)
                {
                    animals[id].energy+=4;
                    board[i][j][a]=0;
                }
                for ( a = 2; a < board[i][j][0]+2&&swich; a++)
                {
                    if (board[i][j][a]>1&&board[i][j][a]<5)
                    {
                        //war betwean id and board[i][j][a]
                    }
                    else if (board[i][j][a]>4&&board[i][j][a]<23)
                    {
                        delete_id(board[i][j][a],i,j);
                        animals[id].score+=animals[board[i][j][a]].score;
                        animals[id].id_mic[0]++;
                        animals[id].id_mic[animals[id].id_mic[0]]=board[i][j][a];
                    }
                    if (board[i][j][a]>22&&board[i][j][a]<27)
                    {
                        //war betwean id and board[i][j][a]
                    }
                }
            }
        }
        else if (masir[k]==Up&&animals[id].power>0)
        {
            j=animals[id].x;
            i=animals[id].y;
            delete_id(id,i,j);
            i--;
            putOnboard(id,i,j);
            if (id>0&&id<5)
            {
                for ( a = 2; a < board[i][j][0]+2; a++)
                {
                    //if (board[i][j][a]>22&&board[i][j][a]<27)
                        //war betwean id and board[i][j][a]
            	}
            }
            else if (id>4&&id<23)
            {
                for ( a = 2; a < board[i][j][0]+2; a++)
                    if (board[i][j][a]>22&&board[i][j][a]<27)
                    {
                        delete_id(id,i,j);
                        animals[board[i][j][a]].score+=animals[id].score;
                        animals[board[i][j][a]].id_mic[0]++;
                        animals[board[i][j][a]].id_mic[animals[board[i][j][a]].id_mic[0]]=id;
                    }
            }
            else if (id>22&&id<27)
            {
                animals[id].energy--;
                swich=1;
                a=1;
                if(board[i][j][a]==TRAP)
                {
                    if (animals[id].id_mic[0])
                    {
                        min=animals[id].id_mic[1];
                        bmin=1;
                        for ( b = 2; b< animals[id].id_mic[0]+1; b++)
                        {
                            if(min>animals[id].id_mic[b])
                            {
                                min=animals[id].id_mic[b];
                                bmin=b;
                            }
                        }
                        for ( b = bmin; b < animals[id].id_mic[0]; b++)
                            animals[id].id_mic[b]=animals[id].id_mic[b+1];
                        animals[id].id_mic[b]=0;
                        animals[id].score-=animals[min].score;
                        animals[id].id_mic[0]--;
                        putOnboard(min,animals[id].y,animals[id].x);
                    }
                    else
                    {
                        if(animals[id].power>2)
                            animals[id].power-=2;
                        else
                        {
                            //در اینجا باید 3 تا از انرژی اش کم گردد
                        }
                    }
                }
                else if(board[i][j][a]==CHOCOLATE)
                    animals[id].power++;
                else if(board[i][j][a]==FISH_2)
                {
                    animals[id].energy+=2;
                    board[i][j][a]=0;
                }
                else if(board[i][j][a]==FISH_3)
                {
                    animals[id].energy+=3;
                    board[i][j][a]=0;
                }
                else if(board[i][j][a]==FISH_4)
                {
                    animals[id].energy+=4;
                    board[i][j][a]=0;
                }
                for ( a = 2; a < board[i][j][0]+2&&swich; a++)
                {
                    if (board[i][j][a]>1&&board[i][j][a]<5)
                    {
                        //war betwean id and board[i][j][a]
                    }
                    else if (board[i][j][a]>4&&board[i][j][a]<23)
                    {
                        delete_id(board[i][j][a],i,j);
                        animals[id].score+=animals[board[i][j][a]].score;
                        animals[id].id_mic[0]++;
                        animals[id].id_mic[animals[id].id_mic[0]]=board[i][j][a];
                    }
                    if (board[i][j][a]>22&&board[i][j][a]<27)
                    {
                        //war betwean id and board[i][j][a]
                    }
                }
            }
        }
        else if (masir[k]==Down&&animals[id].power>0)
        {
            j=animals[id].x;
            i=animals[id].y;
            delete_id(id,i,j);
            i++;
            putOnboard(id,i,j);
            if (id>0&&id<5)
            {
                for ( a = 2; a < board[i][j][0]+2; a++)
                {
				
                   // if (board[i][j][a]>22&&board[i][j][a]<27)
                        //war betwean id and board[i][j][a]
            	}
            }
            else if (id>4&&id<23)
            {
                for ( a = 2; a < board[i][j][0]+2; a++)
                    if (board[i][j][a]>22&&board[i][j][a]<27)
                    {
                        delete_id(id,i,j);
                        animals[board[i][j][a]].score+=animals[id].score;
                        animals[board[i][j][a]].id_mic[0]++;
                        animals[board[i][j][a]].id_mic[animals[board[i][j][a]].id_mic[0]]=id;
                    }
            }
            else if (id>22&&id<27)
            {
                animals[id].energy--;
                swich=1;
                a=1;
                if(board[i][j][a]==TRAP)
                {
                    if (animals[id].id_mic[0])
                    {
                        min=animals[id].id_mic[1];
                        bmin=1;
                        for ( b = 2; b< animals[id].id_mic[0]+1; b++)
                        {
                            if(min>animals[id].id_mic[b])
                            {
                                min=animals[id].id_mic[b];
                                bmin=b;
                            }
                        }
                        for ( b = bmin; b < animals[id].id_mic[0]; b++)
                            animals[id].id_mic[b]=animals[id].id_mic[b+1];
                        animals[id].id_mic[b]=0;
                        animals[id].score-=animals[min].score;
                        animals[id].id_mic[0]--;
                        putOnboard(min,animals[id].y,animals[id].x);
                    }
                    else
                    {
                        if(animals[id].power>2)
                            animals[id].power-=2;
                        else
                        {
                            //در اینجا باید 3 تا از انرژی اش کم گردد
                        }
                    }
                }
                else if(board[i][j][a]==CHOCOLATE)
                    animals[id].power++;
                else if(board[i][j][a]==FISH_2)
                {
                    animals[id].energy+=2;
                    board[i][j][a]=0;
                }
                else if(board[i][j][a]==FISH_3)
                {
                    animals[id].energy+=3;
                    board[i][j][a]=0;
                }
                else if(board[i][j][a]==FISH_4)
                {
                    animals[id].energy+=4;
                    board[i][j][a]=0;
                }
                for ( a = 2; a < board[i][j][0]+2&&swich; a++)
                {
                    if (board[i][j][a]>1&&board[i][j][a]<5)
                    {
                        //war betwean id and board[i][j][a]
                    }
                    else if (board[i][j][a]>4&&board[i][j][a]<23)
                    {
                        delete_id(board[i][j][a],i,j);
                        animals[id].score+=animals[board[i][j][a]].score;
                        animals[id].id_mic[0]++;
                        animals[id].id_mic[animals[id].id_mic[0]]=board[i][j][a];
                    }
                    if (board[i][j][a]>22&&board[i][j][a]<27)
                    {
                        //war betwean id and board[i][j][a]
                    }
                }
            }
        }
    }
    
}

void delete_id(int id,int i,int j)
{
    int a,b;
    for ( a = 2; a < board[i][j][0]+2; a++)
        if(board[i][j][a]==id)
            break;
    for ( b = a; b < board[i][j][0]+2; b++)
        board[i][j][b]=board[i][j][b+1];
    board[i][j][b]=0;
    board[i][j][0]--;
}*/