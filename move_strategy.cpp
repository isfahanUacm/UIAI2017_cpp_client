#include <iostream>
#include"game.h"
using namespace std;

void move_strategy(Game* game)
{
    // write your move strategy here and at the end call game->push() function
    Pos p(0,0);
    Checker* c = new Checker(1,0,'m');
    game->move(c, p);
}
