#include <iostream>
#include <vector>
#include <ctime>
#include "game.h"
using namespace std;
int i=23,j=0;
void put_strategy(Game* game)
{
    // write your put strategy here and at the end call game.put() function
    game->put(Pos(i/3 , j));
    i--;
    j++;
    j%=3;
}
