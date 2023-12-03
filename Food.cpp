#include "Food.h"


Food::Food(GameMechs& gm)   //constructor
{
    gameMechsRef = &gm;
    foodBucket = new objPosArrayList(); //allocate memory on heap

}

Food::~Food()   //destructor
{
    delete foodBucket;
}

void Food::generateFood(objPosArrayList &blockOff)
{
    int randomNumX;
    int randomNumY;
    objPos foodPos;

    //delete previous food if food has been generated before
    if (foodBucket->getSize() == MAX_FOOD)
    {
        for (int j = 0; j < MAX_FOOD; j++)
            foodBucket->removeHead();
    }

    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(NULL))); 

    for (int i = 0; i < MAX_FOOD; i++)  //generate food positions and symbols
    {
        int overlap;
        do 
        {
            //generate random x and y positions
            randomNumX = (rand() % (gameMechsRef->getBoardSizeX() - 2)) + 1;
            randomNumY = (rand() % (gameMechsRef->getBoardSizeY() - 2)) + 1;

            overlap = false;
            objPos tempBlock;
            for (int k = 0; k < blockOff.getSize(); k++)    //check if generated position is in list (body)
            {
                blockOff.getElement(tempBlock,k);
                if (randomNumX == tempBlock.x && randomNumY == tempBlock.y)
                {
                    overlap = true; //discard position and try again
                }
            }
            
            for (int j = 0; j < i; j++) //check if position has been generated for a previous food
            {
                foodBucket->getElement(foodPos, j);
                if (randomNumX == foodPos.x && randomNumY == foodPos.y)
                    {
                        overlap = true; //discard position and try again
                    }
            }

        }while(overlap); //Keep generating random coordinates until an unused one is made

        foodPos.x = randomNumX;
        foodPos.y = randomNumY;

        if (i == 0) //generate one superfood and the rest normal food
        {
            foodPos.symbol = '+';
        }
        else
        {
            foodPos.symbol = 'o';
        }

        //add new food to foodBucket
        foodBucket->insertHead(foodPos);

    }


}

objPosArrayList* Food::getFoodPos()
{
    return foodBucket;
}
