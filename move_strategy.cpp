#include <iostream>
#include"game.h"
using namespace std;

void move_strategy(Game* game)
{
    // write your move strategy here and at the end call game->push() function
    for(int i=0;i<game->get_board().get_myCells().size();i++)
    {
        int x=game->get_board().get_myCells().at(i)->get_pos().getx();
        int y=game->get_board().get_myCells().at(i)->get_pos().gety();
        if(game->get_board().get_cell((x+1)%8,y).get_checker() == nullptr)
        {
            game->move(game->get_board().get_myCells().at(i)->get_checker(),Pos((x+1)%8,y));
            return;
        }
        if(game->get_board().get_cell((x+7)%8,y).get_checker() == nullptr)
        {
            game->move(game->get_board().get_myCells().at(i)->get_checker(),Pos((x+7)%8,y));
            return;
        }
        if(game->get_board().get_cell(x,(y+1)%3).get_checker() == nullptr)
        {
            game->move(game->get_board().get_myCells().at(i)->get_checker(),Pos(x,(y+1)%3));
            return;
        }
        if(game->get_board().get_cell(x,(y+2)%3).get_checker() == nullptr)
        {
            game->move(game->get_board().get_myCells().at(i)->get_checker(),Pos(x,(y+2)%3));
            return;
        }
    }
}
