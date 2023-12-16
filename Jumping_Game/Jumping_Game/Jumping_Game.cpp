#include <iostream>
#include "Game.h"

using namespace std;

int main()
{
    Game myGame;

    while (!myGame.IsGameFinished())
    {
        myGame.LoadLevel(1);
        while (!myGame.IsLevelFinished())
        {
            myGame.DrawFrame(1);
        }
    }
}

