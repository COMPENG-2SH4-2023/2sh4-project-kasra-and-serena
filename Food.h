#ifndef FOOD_H
#define FOOD_H

#define MAX_FOOD 5  //max food generated on the board at a time

#include "objPosArrayList.h"
#include <time.h>
#include <stdlib.h>
#include "GameMechs.h"
#include "objPos.h"

class GameMechs;

class Food 
{
    public:
        Food(GameMechs& gm);
        ~Food();

        void generateFood(objPosArrayList &blockOff);
        objPosArrayList* getFoodPos(); //Getter
        
    private:
        GameMechs* gameMechsRef;
        objPosArrayList* foodBucket;
    };

#endif