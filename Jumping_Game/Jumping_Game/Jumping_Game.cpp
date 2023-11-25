#include <iostream>
#include "Game.h"

using namespace std;

int main()
{
    Game myGame;

    while (!myGame.IsGameFinished())
    {
        while (!myGame.IsLevelFinished())
        {
            myGame.DrawFrame(1);
        }
    }
}

