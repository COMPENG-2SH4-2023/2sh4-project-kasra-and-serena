#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* thisFood)
{
    mainGameMechsRef = thisGMRef;
    foodRef = thisFood;
    myDir = STOP;

    // initilize player position to center of gameboard with list size 1
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, 
                    mainGameMechsRef->getBoardSizeY()/2,
                    '*');

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);

    
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
    
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}


void Player::updatePlayerDir()
{
    // PPA3 input processing logic 
    char input = mainGameMechsRef->getInput();

    if(input != 0)    //if input character is not null, update player direction
    {
        switch(input)
        {
            case ' ':  // exit
                mainGameMechsRef->setExitTrue();
                break;

            //Only transition states for UP and DOWN from LEFT or RIGHT
            // and only transition states for LEFT and RIGHT from UP or DOWN
            // with the exception of default state of STOP

            //'w' key pressed, move UP if direction is stop, left, or right only
            case 'w':
            case 'W':
                if(myDir == STOP || myDir == LEFT || myDir == RIGHT)
                {
                    myDir = UP;
                }
                break;
            //'a' key pressed, move LEFT if direction is stop, up, or down only
            case 'a':
            case 'A':
                if(myDir == STOP || myDir == UP || myDir == DOWN)
                {
                    myDir = LEFT;
                }
                break;
            //'s' key pressed, move DOWN if direction is stop, left, or right
            case 's':
            case 'S':
                if(myDir == STOP || myDir == LEFT || myDir == RIGHT)
                {
                    myDir = DOWN;
                }
                break;
            //'d' key pressed, move RIGHT if direction is stop, up, or down
            case 'd':
            case 'D':
                if(myDir == STOP || myDir == UP || myDir == DOWN)
                {
                    myDir = RIGHT;
                }
                break;

            default:
                break;
        }
    }     
    //clear input buffer
    mainGameMechsRef->clearInput();  
}

void Player::movePlayer()
{
    //------------Check for Self Collision---------------
    if (checkSelfCollision())
    {
        mainGameMechsRef->setLoseFlag();
    }

    //------------PPA3 Finite State Machine logic--------
    //head object data
    objPos currH;
    playerPosList->getHeadElement(currH);

    switch(myDir)
    {
        case STOP:
            //do nothing (default state)
            break;

        case UP:
            if (currH.y <= 0)   //check for top border
            {
                currH.y = mainGameMechsRef->getBoardSizeY() - 2;  //set pos to wraparound
            }
            //decrease y position by one
            currH.y--;
            break;

        case LEFT:
            //check for left border
            if (currH.x <= 0)
            {
                currH.x = mainGameMechsRef->getBoardSizeX() - 2;    
            }
            //decrease x position by one
            currH.x--;
            break;

        case DOWN:
            //check for lower border
            if (currH.y >= (mainGameMechsRef->getBoardSizeY() - 2))
            {
                currH.y = 0;
            }
            //increment y position by one
            currH.y++;
            break;

        case RIGHT:
            if (currH.x >= (mainGameMechsRef->getBoardSizeX() - 2))
            {
                currH.x = 0;
            }
            //incrememnt x position by one
            currH.x++;
            break;

        default:
            break;
    }

    //insert new head
    playerPosList->insertHead(currH);

    //-----------------check for food consumption-----------
    
    if (checkFoodConsumption())
    {
        foodRef->generateFood(*playerPosList);    //generate new food and add to score
        mainGameMechsRef->incrementScore();
    }
    else
    {
        playerPosList->removeTail(); //remove tail if no food is present
    }

}

bool Player::checkFoodConsumption() //check if food position and head position are equal
{
    objPos head, foodPos;
    playerPosList->getHeadElement(head);
    foodRef->getFoodPos(foodPos);

    return head.isPosEqual(&foodPos);
}

bool Player::checkSelfCollision()
{
    objPos head,body;
    playerPosList->getHeadElement(head);
    //compare the head of the snake with the location of the rest of the body
    for(int i = 1; i < playerPosList->getSize(); i++)
    {
        playerPosList->getElement(body,i);
        if (head.isPosEqual(&body))
        {
            return true;    //collision occurred
        }
    }
    return false;
}