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

    objPosArrayList *playerBody = myPlayer->getPlayerPos(); //get current list
    objPos tempBody, tempFood;
    bool objFound;

    //----------------------------Game Mechanics Information----------------------------------
    MacUILib_printf("Boardsize:%dx%d Snake Size: %d Player Positions:\n", myGM->getBoardSizeX(), myGM->getBoardSizeY(), playerBody->getSize());
    for (int m = 0; m < playerBody->getSize(); m++)
    {
        playerBody->getElement(tempBody, m);
        MacUILib_printf("<%d,%d>",tempBody.x, tempBody.y);
    }

    myFood->getFoodPos(tempFood);
    MacUILib_printf("\nFood Position: <%d,%d>", tempFood.x, tempFood.y);

    MacUILib_printf("\n\n");

    //-----------------------------Print gameboard on screen-----------------------------
    for(int j = 0; j < myGM->getBoardSizeY(); j++)   //iterate through each element of game board
    {
        for(int i = 0; i < myGM->getBoardSizeX(); i++)
        {
            objFound = false;

            //draw border (x or y =  0 or n) and food object
            if (j == 0 || j == (myGM->getBoardSizeY() - 1) || i == 0 || i == (myGM->getBoardSizeX() - 1))
            {
                MacUILib_printf("#");
            }
            else if (i == tempFood.x && j == tempFood.y)
            {
                MacUILib_printf("%c", tempFood.symbol);
            }
            
            else
            {
                //draw snake by iterating through each part of the body
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
                if(!objFound)
                    MacUILib_printf(" ");
 
            }
        }
        MacUILib_printf("\n");
    }

    //-----------------Score Keeping--------------------
    MacUILib_printf("Your Score: %d\n", myGM->getScore());

    //-----------------Losing Message/shutdown----------
    if (myGM->getLoseFlagStatus())
    {
        MacUILib_printf("\nNOOOO, YOU LOST!!!\n");
        MacUILib_Delay(350000);    //to allow player to see message
        myGM->setExitTrue();
    }

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

    //delete heap elements
    delete myGM;
    delete myFood;
    delete myPlayer; 
  
    MacUILib_uninit();
}

