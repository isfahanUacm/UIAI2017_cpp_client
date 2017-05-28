#include <iostream>
using namespace std;
#include"pop_strategy.h"

void pop_strategy(Game* game)
{    
    // write your pop strategy here and at the end call game->push() function
    if(game->get_board().get_oppCells().size()>0)
        game->pop(game->get_board().get_oppCells().at(0)->get_checker());
}
