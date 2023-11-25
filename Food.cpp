#include "Food.h"


Food::Food(GameMechs& gm) : gameMechs(gm)
{
    i = 0;
    n = 0;
    foodSymbol = 'o';
}

void Food::generateFood(objPosArrayList &blockOff)
{
    int randomNumX;
    int randomNumY;

    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(NULL))); 

    do 
    {
        randomNumX = (rand() % (gameMechs.getBoardSizeX() - 2)) + 1;
        randomNumY = (rand() % (gameMechs.getBoardSizeY() - 2)) + 1;

        int overlap = false;
        objPos tempBlock;
        for (int k = 0; k < blockOff.getSize(); k++)    //check if generated position is in list
        {
            blockOff.getElement(tempBlock,k);
            if (randomNumX == (tempBlock.x && randomNumY == tempBlock.y))
            {
                overlap = true;
                break;
            }
        }
        if (!overlap)
            break;

    }while(true); //Keep generating random coordinates until an unused one is made

    foodPos.x = randomNumX;
    foodPos.y = randomNumY;
    foodPos.symbol = foodSymbol;
}

void Food::getFoodPos(objPos &returnPos)
{
    returnPos = foodPos; // FIX THIS ITS NOT ACTUALLY THIS I DONT THINK
}
