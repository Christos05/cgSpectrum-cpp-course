#include <iostream>
#include <string>
#include "Player.h"
#include "Item.h"

using namespace std;

int main()
{
    Item Bomb("Bomb", 20, 0);
    Item HealingPotion("HealingPotion", 0, 10);

    Player myPlayer("Chris", 100);
    myPlayer.Display();
    myPlayer.GiveItem(&Bomb);
    myPlayer.GiveItem(&HealingPotion);
    myPlayer.UseItems();
    //Bomb.Use(&myPlayer);
    //HealingPotion.Use(&myPlayer);
    myPlayer.Display();
}