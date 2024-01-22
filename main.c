
// *in the name of god*

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>


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

// structures:

struct coordinates {
    int x;
    int y;
};
typedef struct coordinates coordinates;


// structures for objects (mice, cats, dogs)
struct animal{
    int ID;
    char name[11];
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

struct button {
    ALLEGRO_BITMAP * icon;
    coordinates from;
    coordinates to;
    bool is_showing;
};
typedef struct button button;

extern button diceThrowBTN;


enum direction {None , Up, Right, Down, Left};
typedef enum direction direction;


enum turns {none, cat1, cat2, cat3, cat4};
typedef enum turns turns;


#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "./graphics/graphic.h"

// allegro variables:
extern ALLEGRO_DISPLAY * display;
extern ALLEGRO_SAMPLE * selection_fail_audio;
extern ALLEGRO_SAMPLE_ID isPlayingSampleId;
extern ALLEGRO_SAMPLE * selection_audio;

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
int check_button(button b, int x, int y);
int throw_next_die(int dice[4], bool needThrow[4]);
int is_dice_repeated(int dice[4], bool repeatedDice[4]);
void swap(int *a, int * b);
void set_turns(int dice[4]);
void move(int id,direction masir[5],int tedadgam);
void delete_id(int id,int i,int j);
void war_between_cat_dog(int catid,int dogid);
void war_between_cat1_cat2(int cat1id,int cat2id);

// 1 to 4 for dogs, 5 to 22 for mice, 23 to 26 for cats
animal animals[27];
int board[31][31][30];
int boardSize;
int wall[31][31];
turns catslist[4];
int catsNumber = 0;
turns turn[4];
int numfish=10;


int ________________________________________$_START_GAME_$________________________________________(){

	srand(time(0));
    scanf("%d",&boardSize);

    for (size_t i = 0; i < 4; i++)
    {
        printf("cat %d : ", i + 1);
        scanf("%10s", animals[get_cat_id(i + 1)].name);
        if(animals[get_cat_id(i + 1)].name[0] - '0'){
            catslist[catsNumber] = i + 1;
            catsNumber++;
        }
    }
    
    
    
    if(!allegroINIT())return 0;
    		        
    initwall();
    initAnimals();
    startSettingBoard();

    // for (size_t i = 0; i < boardSize; i++)
    // {
    //     for (int j = 0;j < boardSize;j++)
    //     {
    //         printf("%3d", board[i][j][2]);
    //     }
    //     printf("\n");
        
    // }
    
    
    turns turn = none;

    
    int dice[4] = {0};
    int diceTimer = 0;
    bool needThrowdie[4] = {0};
    for (size_t i = 0; i < catsNumber; i++){
        needThrowdie[catslist[i] - 1] = 1;
    }
    bool throwingDice = 0;
    diceThrowBTN.is_showing = 1;

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
            if(turn && is_mouse_on_Board(event.mouse.x, event.mouse.y)){
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
                            al_stop_sample(&isPlayingSampleId);
                            al_play_sample(selection_audio, 0.5, 0.0, nselection * 0.5 + 1, ALLEGRO_PLAYMODE_ONCE, &isPlayingSampleId);
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
                                al_stop_sample(&isPlayingSampleId);
                                al_play_sample(selection_audio, 0.5, 0.0, nselection * 0.5 + 1, ALLEGRO_PLAYMODE_ONCE, &isPlayingSampleId);
                                nselection++;
                            }
                            if(nmoves > 3){
                                selecting = 0;
                                nmoves = 0;
                                nselection = 0;
                                mouseButtonDown = 0;
                            }
                        } else { // if wall exist
                            al_stop_sample(&isPlayingSampleId);
                            al_play_sample(selection_audio, 0.5, 0.0, 2.5, ALLEGRO_PLAYMODE_ONCE, &isPlayingSampleId);
                            selecting = 0;
                            nmoves = 0;
                            nselection = 0;
                            mouseButtonDown = 0;
                        }
                    }
            	}
            }
            else {// if mosue is not on board
                if(selecting){
                    al_stop_sample(&isPlayingSampleId);
                    al_play_sample(selection_audio, 0.5, 0.0, 3, ALLEGRO_PLAYMODE_ONCE, &isPlayingSampleId);
                    selecting = 0;
                    nmoves = 0;
                    nselection = 0;
                    mouseButtonDown = 0;
                }
            }
        }
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            mouseButtonDown = 1;
            if(is_mouse_on_Board(event.mouse.x, event.mouse.y)){
                coordinates onBoard;
                find_cordinate_on_board(event.mouse.x, event.mouse.y, &onBoard.x, &onBoard.y);
                if(event.mouse.button == 1 && (needShowSelectionHover || (onBoard.x == animals[get_cat_id(turn)].x && onBoard.y == animals[get_cat_id(turn)].y))){
                    
                }
                else{
                    al_play_sample(selection_fail_audio, 1, 0, 1.5, ALLEGRO_PLAYMODE_ONCE, &isPlayingSampleId);
                    mouseButtonDown = 0;
                }
            }

            if(!throwingDice && !turn && check_button(diceThrowBTN, event.mouse.x, event.mouse.y)){
                throwingDice = 1;
                diceThrowBTN.is_showing = 0;
            }

        }

        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            mouseButtonDown = 0;
            if(selecting){
                selecting = 0;
                // move function
                move(get_cat_id(turn), moves, nmoves);
                needUpdateBoardDisplay = 1;
                nmoves = 0;
                nselection = 0;
                turn = next_turn();
                if(!turn){
                	//حرکت سگ و موش _اضافه شدن انرژی 
                    diceThrowBTN.is_showing = 1;
                    for (size_t i = 0; i < catsNumber; i++){
                        needThrowdie[catslist[i] - 1] = 1;
                    }
                    
                }
            }
        }


        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            break;
        }

        if(event.type == ALLEGRO_EVENT_TIMER){
            if(needUpdateBoardDisplay){

                show_background();
                show_scoreboard();
                show_board();
                show_components();
                show_walls();

                oldBoardDisplay = al_clone_bitmap(al_get_backbuffer(display));
                needUpdateBoardDisplay = 0;
            }else{
                al_draw_bitmap(oldBoardDisplay, 0, 0, 0);
            }

            if(throwingDice){
                throwingDice = throw_next_die(dice, needThrowdie);
                if(!throwingDice){
                    set_turns(dice);
                    if(!is_dice_repeated(dice, needThrowdie)){
                        turn = next_turn();
                        diceThrowBTN.is_showing = 0;
                    }else{
                        diceThrowBTN.is_showing = 1;
                    }
                }
            }

            if(diceThrowBTN.is_showing){
                show_button(diceThrowBTN);
            }

            if(1){
                show_dice(dice, !(diceTimer));
                if(!diceTimer)diceTimer += 2;
                diceTimer--;
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

    // animals[1].name = "bulldog";
    animals[1].energy = 5;
    animals[1].power = 5;
    animals[1].dogdefense = 30;
    animals[1].ID = 1;

    // animals[2].name = "pitbull";
    animals[2].energy = 2;
    animals[2].power = 2;
    animals[2].dogdefense = 15;
    animals[2].ID = 2;

    // animals[3].name = "Shepherd";
    animals[3].energy = 3;
    animals[3].power = 2;
    animals[3].dogdefense = 20;
    animals[3].ID = 3;

    // animals[4].name = "BulldogJr";
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
        animals[i].freaz=0;
        animals[i].id_mic[0]=0;
    }
    // 6 2-point mice
    for (size_t i = 9; i < 15; i++)
    {
        animals[i].energy = 2;
        animals[i].score = 2;
        animals[i].ID = i;
        animals[i].freaz=0;
        animals[i].id_mic[0]=0;
    }
    // 8 1-point mice
    for (size_t i = 15; i < 23; i++)
    {
        animals[i].energy = 1;
        animals[i].score = 1;
        animals[i].ID = i;
        animals[i].freaz=0;
        animals[i].id_mic[0]=0;
    }
    // cats (this part of code will change!)
    for (size_t i = 23; i <= 26; i++)
    {
        animals[i].energy = 5;
        animals[i].power = 2;
        animals[i].ID = i;
        animals[i].freaz=0;
        animals[i].id_mic[0]=0;
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
    static int nturn = -1;
    nturn++;
    if(nturn >= catsNumber){
        nturn = -1;
        return none;
    }
    return turn[nturn];
}

void set_turns(int dice[4]){
    int mylist[4];
    static int nRepeatedDice = 0;
    static int repeatedDice[4] = {0};
    for (size_t i = 0; i < 4; i++)
        mylist[i] = dice[i];
    if(!nRepeatedDice)
        for (int i = catsNumber - 1;i >= 0; i--){
            int maxindex = 0;
            for (int j = 1;j < 4;j++){
                if(mylist[maxindex] < mylist[j]){
                    maxindex = j;
                }
            }
            turn[catsNumber - i - 1] = maxindex + 1;
            if(i < catsNumber - 1){
                if(dice[turn[catsNumber - 2 - i] - 1] == mylist[maxindex]){
                    if(!repeatedDice[turn[catsNumber - 2 - i] - 1]){
                        repeatedDice[turn[catsNumber - 2 - i] - 1] = repeatedDice[maxindex] = ++nRepeatedDice;
                    }else{
                        repeatedDice[maxindex] = repeatedDice[turn[catsNumber - 2 - i] - 1];
                    }
                }
            }
            mylist[maxindex] = -2;  
        }
    else if(nRepeatedDice == 1){
        nRepeatedDice = 0;
        int f;
        for (f = 0; f < catsNumber; f++)
            if(repeatedDice[turn[f] - 1] == 1)break;
        
        for(int i = f;i < catsNumber && repeatedDice[turn[i] - 1] == 1;i++){
            int maxindex = i;
            for (int j = i + 1;j < catsNumber && repeatedDice[turn[j] - 1] == 1; j++){
                if(mylist[turn[j] - 1] > mylist[turn[maxindex] - 1]){
                    maxindex = j;
                }
            }
            swap(&turn[i], &turn[maxindex]);
            if(i > f){
                if(dice[turn[i - 1] - 1] == mylist[turn[i] - 1]){
                    if(!repeatedDice[turn[i - 1] - 1]){
                        repeatedDice[turn[i] - 1] = repeatedDice[turn[i - 1] - 1] = ++nRepeatedDice;
                    }else{
                        repeatedDice[turn[i] - 1] = repeatedDice[turn[i - 1] - 1];
                    }
                }
                else
                    repeatedDice[turn[i] - 1] = 0;
            }else{
                repeatedDice[turn[i] - 1] = 0;
            }
            
            mylist[turn[i] - 1] = -2;
        }    
    }else if(nRepeatedDice == 2){
        nRepeatedDice = 0;
        if(mylist[turn[0] - 1] < mylist[turn[1] - 1]){
            swap(&turn[0], &turn[1]);
            repeatedDice[turn[0] - 1] = 0;
            repeatedDice[turn[1] - 1] = 0;
        }else if(mylist[turn[0] - 1] == mylist[turn[1] - 1]){
            repeatedDice[turn[0] - 1] = 1;
            repeatedDice[turn[1] - 1] = 1;
            nRepeatedDice = 1;
        }

        if(mylist[turn[2] - 1] < mylist[turn[3] - 1]){
            swap(&turn[2], &turn[3]);
            repeatedDice[turn[2] - 1] = 0;
            repeatedDice[turn[3] - 1] = 0;
        }else if(mylist[turn[2] - 1] == mylist[turn[3] - 1]){
            repeatedDice[turn[2] - 1] = repeatedDice[turn[3] - 1] = ++nRepeatedDice;
        }
    }
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

int check_button(button b, int x, int y){
    return b.is_showing && (((b.from.x <= x && x <= b.to.x) && (b.from.y <= y && y <= b.to.y)) || 
            ((b.to.x <= x && x <= b.from.x) && (b.to.y <= y && y <= b.from.y)));
}

int throw_next_die(int dice[4], bool needThrow[4]){
    const int delay = 40;
    static int timer = 0;
    static int dieNum = 0;
    if(!timer && !dieNum){
        for(int i = 0;i < 4;i++)
            if(needThrow[i])
                dice[i] = -1;
        
    }

    if(!dieNum)
        if(timer >= 1.5 * delay){
            if(needThrow[dieNum]){
                dice[dieNum] = rand() % 6 + 1;
                timer = 0;
            }
            dieNum++;
        }else;
    else if(timer >= delay){
        if(needThrow[dieNum]){
            dice[dieNum] = rand() % 6 + 1;
            timer = 0;
        }
        dieNum++;
        if(dieNum >= 4){
                dieNum = 0;
                timer = 0;
                return 0;
        }
    }

    timer++;

    return 1;
}

int is_dice_repeated(int dice[4], bool repeatedDice[4]){
    bool hasRep = 0;
    bool myrep[4] = {0};
    for (size_t i = 0; i < 4; i++)
        if(repeatedDice[i])
            for (size_t j = i + 1; j < 4; j++){
                if(repeatedDice[j]){
                    if(dice[i] == -1 || !dice[i])break;
                    if(dice[j] == -1 || !dice[j])continue;
                    if(dice[i] == dice[j]){
                        myrep[i] = myrep[j] = 1;
                        hasRep = 1;
                    }
                }
            }
    for (size_t i = 0; i < 4; i++)
        repeatedDice[i] = myrep[i];
    
    

    return hasRep;
}

void swap(int *a, int * b){
    int temp = *b;
    *b = *a;
    *a = temp;
}

void move(int id,direction masir[5],int tedadgam){
    int i,j,a,b,min,swich,bmin;
    for (size_t k = 0; k < tedadgam; k++)
    {
        if (masir[k]==Right&&animals[id].energy>0&&!animals[id].freaz)
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
                    if (board[i][j][a]>22&&board[i][j][a]<27)
                        war_between_cat_dog(board[i][j][a],id);
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
                            putOnboard(min,animals[min].y,animals[min].x);
                    }
                    else
                    {
                        if(animals[id].power>2)
                            animals[id].power-=2;
                        else
                        {
                            //ط¯ط± ط§غŒظ†ط¬ط§ ط¨ط§غŒط¯ 3 طھط§ ط§ط² ط§ظ†ط±عکغŒ ط§ط´ ع©ظ… ع¯ط±ط¯ط¯
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
                    numfish--;
                }
                else if(board[i][j][a]==FISH_3)
                {
                    animals[id].energy+=3;
                    board[i][j][a]=0;
                    numfish--;
                }
                else if(board[i][j][a]==FISH_4)
                {
                    animals[id].energy+=4;
                    board[i][j][a]=0;
                    numfish--;
                }
                for ( a = 2; a < board[i][j][0]+2&&swich; a++)
                {
                    if (board[i][j][a]>1&&board[i][j][a]<5)
                    {
                        war_between_cat_dog(id,board[i][j][a]);
                    }
                    else if (board[i][j][a]>4&&board[i][j][a]<23)
                    {
                        delete_id(board[i][j][a],i,j);
                        animals[id].score+=animals[board[i][j][a]].score;
                        animals[id].id_mic[0]++;
                        animals[id].id_mic[animals[id].id_mic[0]]=board[i][j][a];
                    }
                    if (board[i][j][a]>22&&board[i][j][a]<27&&board[i][j][a]!=id)
                    {
                        war_between_cat1_cat2(id,board[i][j][a]);
                    }
                }
            }
        }
        else if (masir[k]==Left&&animals[id].energy>0&&!animals[id].freaz)
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
                    if (board[i][j][a]>22&&board[i][j][a]<27)
                        war_between_cat_dog(board[i][j][a],id);
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
                        putOnboard(min,animals[min].y,animals[min].x);
                    }
                    else
                    {
                        if(animals[id].power>2)
                            animals[id].power-=2;
                        else
                        {
                            //ط¯ط± ط§غŒظ†ط¬ط§ ط¨ط§غŒط¯ 3 طھط§ ط§ط² ط§ظ†ط±عکغŒ ط§ط´ ع©ظ… ع¯ط±ط¯ط¯
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
                    numfish--;
                }
                else if(board[i][j][a]==FISH_3)
                {
                    animals[id].energy+=3;
                    board[i][j][a]=0;
                    numfish--;
                }
                else if(board[i][j][a]==FISH_4)
                {
                    animals[id].energy+=4;
                    board[i][j][a]=0;
                    numfish--;
                }
                for ( a = 2; a < board[i][j][0]+2&&swich; a++)
                {
                    if (board[i][j][a]>1&&board[i][j][a]<5)
                    {
                        war_between_cat_dog(id,board[i][j][a]);
                    }
                    else if (board[i][j][a]>4&&board[i][j][a]<23)
                    {
                        delete_id(board[i][j][a],i,j);
                        animals[id].score+=animals[board[i][j][a]].score;
                        animals[id].id_mic[0]++;
                        animals[id].id_mic[animals[id].id_mic[0]]=board[i][j][a];
                    }
                    if (board[i][j][a]>22&&board[i][j][a]<27&&board[i][j][a]!=id)
                    {
                        war_between_cat1_cat2(id,board[i][j][a]);
                    }
                }
            }
        }
        else if (masir[k]==Up&&animals[id].energy>0&&!animals[id].freaz)
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
                    if (board[i][j][a]>22&&board[i][j][a]<27)
                        war_between_cat_dog(board[i][j][a],id);
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
                        putOnboard(min,animals[min].y,animals[min].x);
                    }
                    else
                    {
                        if(animals[id].power>2)
                            animals[id].power-=2;
                        else
                        {
                            //ط¯ط± ط§غŒظ†ط¬ط§ ط¨ط§غŒط¯ 3 طھط§ ط§ط² ط§ظ†ط±عکغŒ ط§ط´ ع©ظ… ع¯ط±ط¯ط¯
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
                    numfish--;
                }
                else if(board[i][j][a]==FISH_3)
                {
                    animals[id].energy+=3;
                    board[i][j][a]=0;
                    numfish--;
                }
                else if(board[i][j][a]==FISH_4)
                {
                    animals[id].energy+=4;
                    board[i][j][a]=0;
                    numfish--;
                }
                for ( a = 2; a < board[i][j][0]+2&&swich; a++)
                {
                    if (board[i][j][a]>1&&board[i][j][a]<5)
                    {
                        war_between_cat_dog(id,board[i][j][a]);
                    }
                    else if (board[i][j][a]>4&&board[i][j][a]<23)
                    {
                        delete_id(board[i][j][a],i,j);
                        animals[id].score+=animals[board[i][j][a]].score;
                        animals[id].id_mic[0]++;
                        animals[id].id_mic[animals[id].id_mic[0]]=board[i][j][a];
                    }
                    if (board[i][j][a]>22&&board[i][j][a]<27&&board[i][j][a]!=id)
                    {
                        war_between_cat1_cat2(id,board[i][j][a]);
                    }
                }
            }
        }
        else if (masir[k]==Down&&animals[id].energy>0&&!animals[id].freaz)
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
                    if (board[i][j][a]>22&&board[i][j][a]<27)
                        war_between_cat_dog(board[i][j][a],id);
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
                        putOnboard(min,animals[min].y,animals[min].x);
                    }
                    else
                    {
                        if(animals[id].power>2)
                            animals[id].power-=2;
                        else
                        {
                            //ط¯ط± ط§غŒظ†ط¬ط§ ط¨ط§غŒط¯ 3 طھط§ ط§ط² ط§ظ†ط±عکغŒ ط§ط´ ع©ظ… ع¯ط±ط¯ط¯
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
                    numfish--;
                }
                else if(board[i][j][a]==FISH_3)
                {
                    animals[id].energy+=3;
                    board[i][j][a]=0;
                    numfish--;
                }
                else if(board[i][j][a]==FISH_4)
                {
                    animals[id].energy+=4;
                    board[i][j][a]=0;
                    numfish--;
                }
                for ( a = 2; a < board[i][j][0]+2&&swich; a++)
                {
                    if (board[i][j][a]>1&&board[i][j][a]<5)
                    {
                        war_between_cat_dog(id,board[i][j][a]);
                    }
                    else if (board[i][j][a]>4&&board[i][j][a]<23)
                    {
                        delete_id(board[i][j][a],i,j);
                        animals[id].score+=animals[board[i][j][a]].score;
                        animals[id].id_mic[0]++;
                        animals[id].id_mic[animals[id].id_mic[0]]=board[i][j][a];
                    }
                    if (board[i][j][a]>22&&board[i][j][a]<27&&board[i][j][a]!=id)
                    {
                        war_between_cat1_cat2(id,board[i][j][a]);
                    }
                }
            }
        }
    }
    if(animals[id].freaz)
        	animals[id].freaz--;
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
}

void war_between_cat_dog(int catid,int dogid)
{
    int b;
    if (animals[catid].power*animals[catid].energy>=animals[dogid].power*animals[dogid].energy)
    {
        delete_id(dogid,animals[dogid].y,animals[dogid].x);
        animals[catid].energy-=round(animals[catid].power*((float)animals[catid].energy/animals[dogid].power));
    }
    else 
    {
        animals[catid].freaz=3;
        for ( b = 1; b < animals[catid].id_mic[0]+1; b++)
        {
            putOnboard(animals[catid].id_mic[b],animals[animals[catid].id_mic[b]].y,animals[animals[catid].id_mic[b]].x);
            animals[catid].id_mic[b]=0;
        }
        animals[catid].id_mic[0]=0;
        animals[catid].power=2;
        animals[catid].energy=5;
        animals[dogid].energy-=round(animals[dogid].power*((float)animals[dogid].energy/animals[catid].power));
    } 
}

void war_between_cat1_cat2(int cat1id,int cat2id)
{
    int b;
    if (animals[cat1id].power*animals[cat1id].energy>=animals[cat2id].power*animals[cat2id].energy)
    {
        animals[cat2id].freaz=3;
        for ( b = 1; b < animals[cat2id].id_mic[0]+1; b++)
        {
            putOnboard(animals[cat2id].id_mic[b],animals[animals[cat2id].id_mic[b]].y,animals[animals[cat2id].id_mic[b]].x);
            animals[cat2id].id_mic[b]=0;
        }
        animals[cat2id].id_mic[0]=0;
        animals[cat2id].power=2;
        animals[cat2id].energy=5;
        animals[cat1id].energy-=round(animals[cat1id].power*((float)animals[cat1id].energy/animals[cat2id].power));
    }
    else 
    {
        animals[cat1id].freaz=3;
        for ( b = 1; b < animals[cat1id].id_mic[0]+1; b++)
        {
            putOnboard(animals[cat1id].id_mic[b],animals[animals[cat1id].id_mic[b]].y,animals[animals[cat1id].id_mic[b]].x);
            animals[cat1id].id_mic[b]=0;
        }
        animals[cat1id].id_mic[0]=0;
        animals[cat1id].power=2;
        animals[cat1id].energy=5;
        animals[cat2id].energy-=round(animals[cat2id].power*((float)animals[cat2id].energy/animals[cat1id].power));
    } 
}