#ifndef FOOD_H
#define FOOD_H

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
        void generateFood(objPosArrayList &blockOff);
        void getFoodPos(objPos &returnPos); //Getter
        
    private:
        GameMechs* gameMechsRef;
        objPos foodPos;
    };

#endif