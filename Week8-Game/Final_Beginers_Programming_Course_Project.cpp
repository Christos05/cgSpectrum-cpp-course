#include <iostream>
#include "Game.h"

using namespace std;

int main()
{
	Game myGame;

	if (myGame.Load())
	{
		while (!myGame.IsGameOver())
		{
			myGame.Run();
		}

		cout << "YOU WIN!!!" << endl;
		//PlayWinSound();
	}
	else
	{
		cout << "Game did not load Terminating now!" << endl;
	}
}

//void playdoorclosedsound()
//{
//	beep(500, 75);
//	beep(500, 75);
//}
//void playdooropensound()
//{
//	beep(1379, 200);
//}
//void playkeypickupsound()
//{
//	beep(1568, 200);
//}
//void playwinsound()
//{
//	beep(1568, 200);
//	beep(1568, 200);
//	beep(1568, 200);
//	beep(1245, 1000);
//	beep(1397, 200);
//	beep(1397, 200);
//	beep(1397, 200);
//	beep(1175, 1000);
//}