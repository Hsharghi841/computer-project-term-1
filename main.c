#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

// defines

#define sq(x) (x) * (x)

//functions:

void initAnimals();
int abs(int x);
void sortObject(int id[], int idnum, int bordSize);
// putOnBord tries to put an object on bord if can return 1 else 0 :
int putOnBord(int id, int width, int length);

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
	srand(time(0));
    // int n = 15;
    // int a[4] = {27, 28, 29, 30};
	// sortObject(a, 4, n);

    // for (size_t i = 0; i < n; i++)
    // {
    //     for (size_t j = 0; j < n; j++)
    //     {
    //         printf("%d", !!bord[i][j][1]);
    //     }
    //     printf("\n");
    // }
    
	
	  
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



int abs(int x){
    if(x < 0)x = -x;
    return x;
}

void sortObject(int id[], int idnum, int bordSize){

    int boolBord[31][31] = {{0}};
    int R = sqrt(bordSize * bordSize / idnum);

    for (size_t j = 0; j < bordSize * bordSize; j++)
    {
        if(sq(bordSize / 2 - (j % bordSize)) + sq(bordSize / 2 - (j / bordSize)) <= sq(R * 2 / 3)){
            boolBord[j / bordSize][j % bordSize] = 1;
        }
    }

    for (size_t k = 0; k < bordSize; k++)
        {
            for (size_t j = 0; j < bordSize; j++)
            {
                printf("%d", boolBord[k][j]);
            }
            printf("\n");
        }
        printf("\n\n");

    for (size_t i = 0; i < idnum; i++)
    {
        int r = rand() % (bordSize * bordSize); 
        int x = r % bordSize, y = r / bordSize;
        
        if(!boolBord[y][x]){
            for (size_t j = 0; j < bordSize * bordSize; j++)
            {
                if(sq(x - (j % bordSize)) + sq(y - (j / bordSize)) <= sq(R)){
                    boolBord[j / bordSize][j % bordSize] = 1;
                }
            }
            
            if(!putOnBord(id[i], y, x)){
                i--;
            }

        }
        else i--;
    }
}

int putOnBord(int id, int width, int length){
    if(0 < id && id < 27){
        bord[width][length][bord[width][length][0] + 2] = id;
        bord[width][length][0]++;
        animals[id].x = length;
        animals[id].y = width;
        return 1;
    }
    {// must add code of objects in if
        if(!bord[width][length][1]){
            bord[width][length][1] = id;
            return 1;
        }
        else return 0;
    }
    //a display function must add in here:

    //


}