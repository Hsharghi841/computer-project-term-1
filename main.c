
// *in the name of god*

// defines :
#define sq(x) (x) * (x) // for square a number
#define get_cat_id(x) (x) + 22
#define TRAP 27
#define CHOCOLATE 28
#define FISH_2 32
#define FISH_3 33
#define FISH_4 34
int FISH[3] = {FISH_2, FISH_3, FISH_4};
#define ________________________________________$_START_GAME_$________________________________________ main
#define _________________________________________$_END_GAME_$_________________________________________ }

struct coordinates {
    int x;
    int y;
};
typedef struct coordinates coordinates;

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
};
typedef struct animal animal;


enum direction {None , Up, Right, Down, Left};
typedef enum direction direction;

enum turns {none, cat1, cat2, cat3, cat4};
typedef enum turns turns;


#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "./graphics/graphic.h"


extern ALLEGRO_DISPLAY * display;
extern ALLEGRO_SAMPLE * selection_fail_audio;
extern ALLEGRO_SAMPLE_ID isPlayingSampleId;

//functions:

void initAnimals();
int abs(int x);
void sortObject(int id[], int idnum);
int startSettingBoard();
int putOnboard(int id, int width, int length);// putOnboard tries to put an object on board if can return 1 else 0 :
void initwall();
void show_board();
int show_components();
turns next_turn();
direction find_direction(int x, int y, int xboard, int yboard);
int isEqualCoordinates(coordinates a, coordinates b);
int check_wall(coordinates a, coordinates b);
int check_wall2(int x, int y, coordinates b);

// 1 to 4 for dogs, 5 to 22 for mice, 23 to 26 for cats
animal animals[27];
int board[31][31][30];
int boardSize;
int wall[31][31];
turns catslist[4];
int catsNumber = 0;
turns turn;

int ________________________________________$_START_GAME_$________________________________________(){

	srand(time(0));
    scanf("%d",&boardSize);

    for (size_t i = 0; i < 4; i++)
    {
        printf("cat %d : ", i + 1);
        int a;
        scanf("%d", &a);
        if(a){
            catslist[catsNumber] = i + 1;
            catsNumber++;
        }
    }
    
    
    
    allegroINIT();
    		        
    initwall();
    startSettingBoard();
    
    next_turn();
    next_turn();


    ALLEGRO_TIMER * timer = al_create_timer(1.0 / 60);
    al_start_timer(timer);


    ALLEGRO_EVENT event;
    ALLEGRO_EVENT_QUEUE * queue = al_create_event_queue();
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_display_event_source(display));
    
    bool showMouse = 1;
    bool mouseButtonDown = 0;
    bool selecting = 0;
    coordinates selectionlist[5];
    int nselection = 0;

    bool needUpdateBoardDisplay = 1;
    bool needShowSelectionHover = 0;
    ALLEGRO_BITMAP * oldBoardDisplay;
    // mx : x of mouse , my : y of mouse
    int mx, my;

    direction moves[4];
    int nmoves = 0;

    while(1){
    	al_wait_for_event(queue,&event);


        if(event.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY){
            showMouse = 0;
        }

        if(event.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY){
            showMouse = 1;
        }


        if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
            if(is_mouse_on_Board(event.mouse.x, event.mouse.y)){
                coordinates onBoard;
                find_cordinate_on_board(event.mouse.x, event.mouse.y, &onBoard.x, &onBoard.y);
                if(needShowSelectionHover = (is_mouse_nextto(event.mouse.x, event.mouse.y, animals[get_cat_id(turn)].x, animals[get_cat_id(turn)].y) && check_wall2(animals[get_cat_id(turn)].x, animals[get_cat_id(turn)].y, onBoard)) && !selecting){
                    
                    mx = event.mouse.x;
                    my = event.mouse.y;
                    if(mouseButtonDown){
                        selecting = 1;
                        if(moves[nmoves] = find_direction(onBoard.x, onBoard.y, animals[get_cat_id(turn)].x, animals[get_cat_id(turn)].y)){
                            nmoves++;
                            selectionlist[nselection] = onBoard;
                            nselection++;
                        }
                    }
                }
                if(selecting && !isEqualCoordinates(selectionlist[nselection - 1], onBoard)){
                    if(nselection > 1 && selectionlist[nselection - 2].x == onBoard.x && selectionlist[nselection - 2].y == onBoard.y){
                        nselection--;
                        nmoves--;
                    }
                    else if(nselection == 1 && onBoard.x == animals[get_cat_id(turn)].x && onBoard.y == animals[get_cat_id(turn)].y){
                        selecting = 0;
                        nmoves = 0;
                        nselection = 0;
                        
                    }
                    else {
                        if(check_wall(selectionlist[nselection - 1], onBoard)){
                            if(moves[nmoves] = find_direction(onBoard.x, onBoard.y, selectionlist[nselection - 1].x, selectionlist[nselection - 1].y)){
                                nmoves++;
                                selectionlist[nselection] = onBoard;
                                nselection++;
                            }
                            if(nmoves > 3){
                                selecting = 0;
                                nmoves = 0;
                                nselection = 0;
                                mouseButtonDown = 0;
                            }
                        } else { // if wall exist
                            selecting = 0;
                            nmoves = 0;
                            nselection = 0;
                            mouseButtonDown = 0;
                        }
                    }
                }
                // printf("%d\n", wall[onBoard.x][onBoard.y]);
            }
            else {// if mosue is not on board
                selecting = 0;
                nmoves = 0;
                nselection = 0;
                mouseButtonDown = 0;
            }
            // printf("%d\n", nmoves);
        }

        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            mouseButtonDown = 1;
            coordinates onBoard;
            find_cordinate_on_board(event.mouse.x, event.mouse.y, &onBoard.x, &onBoard.y);
            if(event.mouse.button == 1 && (needShowSelectionHover || (onBoard.x == animals[get_cat_id(turn)].x && onBoard.y == animals[get_cat_id(turn)].y))){
                
            }
            else{
                al_play_sample(selection_fail_audio, 1, 0, 1.5, ALLEGRO_PLAYMODE_ONCE, &isPlayingSampleId);
                mouseButtonDown = 0;
            }
        }

        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            mouseButtonDown = 0;
            if(selecting){
                selecting = 0;
                // move function
                nmoves = 0;
                nselection = 0;
            }
        }


        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            break;
        }

        if(event.type == ALLEGRO_EVENT_TIMER){
            if(needUpdateBoardDisplay){
                al_clear_to_color(al_map_rgb(255, 255, 255));
                show_board();
                show_components();
                show_walls();
                

                oldBoardDisplay = al_clone_bitmap(al_get_backbuffer(display));
                needUpdateBoardDisplay = 0;
            }else{
                al_draw_bitmap(oldBoardDisplay, 0, 0, 0);
            }
            if(needShowSelectionHover){
                needShowSelectionHover = show_slection_hover(mx, my);
            }
            if(selecting && nselection){
                
                show_slections(selectionlist, nselection);
            }
            if(showMouse)put_mouse();
            al_flip_display();
        }


    


    	
	}
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    allegroDESTROY();

_________________________________________$_END_GAME_$_________________________________________


void initwall()
{
    for (int i = 0; i < (boardSize+1)/2; i++)
    {
        for (int j = 0; j < (boardSize+1)/2; j++)
        {
            int number;
            number=rand()%40;
            if (number>0&&number<4)
            {
                wall[i][j]=number;
            }
        }
        for (int j =(boardSize+1)/2+1 ; j < boardSize; j++)
        {
            int number;
            number=rand()%40;
            if (number>0&&number<4)
            {
                wall[i][j]=number;
            }
        }
    }
    for (int i = (boardSize+1)/2+1; i < boardSize; i++)
    {
        for (int j = 0; j < (boardSize+1)/2; j++)
        {
            int number;
            number=rand()%40;
            if (number>0&&number<4)
            {
                wall[i][j]=number;
            }
        }
        for (int j =(boardSize+1)/2+1 ; j < boardSize; j++)
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

void sortObject(int id[], int idnum){

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

int startSettingBoard(){
    // cats : 

    if(boardSize % 2 == 1) {
        
        for (size_t i = 0; i < catsNumber; i++)
        {
            putOnboard(get_cat_id(catslist[i]), boardSize / 2 , boardSize / 2);
        }

    }else{
        int r = rand() % 4;

        for (size_t i = 0; i < catsNumber; i++)
        {
            putOnboard(get_cat_id(catslist[i]), boardSize / 2 - r / 2 , boardSize / 2 - r % 2);
        }
        
    }
    
    // dogs :
    
    int dogs[] = {1, 2, 3, 4};
    sortObject(dogs, 4);
    
    // mice :
    
    int mice[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22};
    sortObject(mice, 18);
    
    // fishes :
    
    int fishes[10];
    for (int i = 0; i < 10; ++i)
        fishes[i] = FISH[rand() % 3];
    
    sortObject(fishes, 10);
    
    // Chocolate :
    
    int chocolate[] = {CHOCOLATE, CHOCOLATE, CHOCOLATE, CHOCOLATE, CHOCOLATE, CHOCOLATE, CHOCOLATE, CHOCOLATE};
    sortObject(chocolate, 8);
    
    // traps :
    
    int trap[] = {TRAP, TRAP, TRAP, TRAP, TRAP, TRAP, TRAP, TRAP};
    sortObject(trap, 8);
    
    
    
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

            if(board[i][j][1]){
                show_object(board[i][j][1], j, i);
            }
        }
}

turns next_turn(){
    static int tn = 4;
    static turns tlist[4];

    tn++;
    if(tn > catsNumber){
        for (size_t i = 0; i < catsNumber; i++)
            tlist[i] = catslist[i];
        
        tn = 0;
        turn = none;
        return none;
    }
    int r = rand() % (catsNumber - tn + 1);
    turn = tlist[r];
    tlist[r] = tlist[catsNumber - tn];
    return turn;

}

direction find_direction(int x2, int y2, int x1, int y1){
    
    if(x2 == x1 + 1)return Right;
    if(x2 == x1 - 1)return Left;
    if(y2 == y1 + 1)return Down;
    if(y2 == y1 - 1)return Up;
    return None;
}

int isEqualCoordinates(coordinates a, coordinates b){
    return a.x == b.x && a.y == b.y;
}

int check_wall(coordinates a, coordinates b){
    switch (find_direction(b.x, b.y, a.x, a.y))
    {
    case Down:
        if(wall[a.x][a.y] / 2 == 1)return 0;
        break;
    case Right:
        if(wall[a.x][a.y] % 2 == 1)return 0;
        break;
    case Left:
        if(wall[b.x][b.y] % 2 == 1)return 0;
        break;
    case Up:
        if(wall[b.x][b.y] / 2 == 1)return 0;
        break;
    default:
        return 0;
    }
    return 1;
}

int check_wall2(int x, int y, coordinates b){
    switch (find_direction(b.x, b.y, x, y))
    {
    case Down:
        if(wall[x][y] / 2 == 1)return 0;
        break;
    case Right:
        if(wall[x][y] % 2 == 1)return 0;
        break;
    case Left:
        if(wall[b.x][b.y] % 2 == 1)return 0;
        break;
    case Up:
        if(wall[b.x][b.y] / 2 == 1)return 0;
        break;
    default:
        return 0;
    }
    return 1;
}