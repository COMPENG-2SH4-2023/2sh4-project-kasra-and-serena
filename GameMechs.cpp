#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{

    input = '\0';
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = 30;
    boardSizeY = 15;

}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = '\0';
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = boardX;
    boardSizeY = boardY;
}

/*
GameMechs::~GameMechs()
{
    //Empty
}
*/

bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

char GameMechs::getInput()
{
    if(MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }
    return input; 
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{

    exitFlag = true;

}

void GameMechs::setInput(char this_input)
{

    input = this_input;

}

void GameMechs::clearInput()
{
    input = '\0';
}

void GameMechs::incrementScore(int amount)
{
    score += amount;
}

int GameMechs::getScore()
{
    return score;
}