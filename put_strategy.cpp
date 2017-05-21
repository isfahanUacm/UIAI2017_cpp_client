#include <iostream>
#include <vector>
#include <ctime>
#include "game.h"
using namespace std;


void put_strategy(Game* game)
{
    // write your pot strategy here and at the end call game->put() function
    game->put(game->get_board().get_emptyCells()[0]->get_pos());
}
