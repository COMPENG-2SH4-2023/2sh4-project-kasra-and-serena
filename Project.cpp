#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"

//constants
#define DELAY_CONST 100000

using namespace std;

Player* myPlayer;
GameMechs* myGM;
Food* myFood;


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    //---------initilize game mechanics, food, and player objects--------
    myGM = new GameMechs(30,15);
    myFood = new Food(*myGM);
    myPlayer = new Player(myGM,myFood);

    //----------generate initial piece of food-----------
    objPosArrayList* body;
    objPos head;
    body = myPlayer->getPlayerPos();
    body->getHeadElement(head);
    myFood->generateFood(*body);

}

void GetInput(void)
{
    myGM->getInput();
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir(); //change direction depending on input
    myPlayer->movePlayer(); //move player based on current state
    myGM->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); //clear previous frame

    objPos tempBody, tempFood;
    bool objFound;
    objPosArrayList *playerBody = myPlayer->getPlayerPos(); //get current snake body list
    objPosArrayList *foodBucket = myFood->getFoodPos(); //get current food list
    

    //----------------------------Game Mechanics Information----------------------------------
    
    MacUILib_printf("Boardsize:%dx%d\n", myGM->getBoardSizeX(), myGM->getBoardSizeY());
    
    //Uncomment for debugging/viewing purposes
    /*
    MacUILib_printf("Player Positions: ");
    for (int m = 0; m < playerBody->getSize(); m++)
    {
        playerBody->getElement(tempBody, m);
        MacUILib_printf("<%d,%d>",tempBody.x, tempBody.y);
    }

    MacUILib_printf("\nFood Position: ");
    for(int n = 0; n < foodBucket->getSize(); n++)
    {
        foodBucket->getElement(tempFood, n);
        MacUILib_printf("<%d,%d>", tempFood.x, tempFood.y);
    }

    MacUILib_printf("\n\n");

    */

    //-----------------------------Print gameboard on screen-----------------------------
    for(int j = 0; j < myGM->getBoardSizeY(); j++)   //iterate through each element of game board
    {
        for(int i = 0; i < myGM->getBoardSizeX(); i++)
        {
            objFound = false;

            //draw border (x or y =  0 or n)
            if (j == 0 || j == (myGM->getBoardSizeY() - 1) || i == 0 || i == (myGM->getBoardSizeX() - 1))
            {
                MacUILib_printf("#");
                objFound = true;
            }
            
            else
            {
                //check for snake body by iterating through each element
                for(int k = 0; k < playerBody->getSize(); k++)
                {
                    playerBody->getElement(tempBody,k);
                    if (i == tempBody.x && j == tempBody.y)     //check if location is equal to player location
                    {
                        MacUILib_printf("%c", tempBody.symbol);
                        objFound = true;
                        break;
                    }
                }

                //check for food in foodBucket
                for (int p = 0; p < foodBucket->getSize(); p++)
                {
                    foodBucket->getElement(tempFood, p);
                    if (i == tempFood.x && j == tempFood.y)
                    {
                        MacUILib_printf("%c", tempFood.symbol);
                        objFound = true;
                        break;
                    }
                }
                if (!objFound)  //object not found, print space
                    MacUILib_printf(" ");
                

            }
            
        }
        MacUILib_printf("\n");
    }

    //-----------------Score Keeping--------------------
    MacUILib_printf("Your Score: %d\nSnake Size: %d\n\n", myGM->getScore(), playerBody->getSize());
    MacUILib_printf("Food -> '+' = +10 points, 'o' = +1 point and +1 snake length\n");


    //-----------------User instructions----------------
    MacUILib_printf("\nKey Bindings:\n");
    MacUILib_printf("Movement -> UP = W, LEFT = A, DOWN = S, RIGHT = D\n");
    MacUILib_printf("Press space to exit");



}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();   

    //-----------------Losing Message/shutdown----------
    if (myGM->getLoseFlagStatus())
    {
        MacUILib_printf("\nNOOOO, YOU LOST!!!\n");
    }

    //delete heap elements
    delete myGM;
    delete myFood;
    delete myPlayer; 
  
    MacUILib_uninit();
}

