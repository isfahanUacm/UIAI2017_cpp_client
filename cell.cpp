#include "cell.h"

void Cell::set_checker(int x, int y, char c)
{
    checker = new Checker(x,y,c);
}

Cell::Cell(int x,int y, char c)
{
    pos = new Pos(x,y);

    if(c=='e')
        checker = nullptr;
    else
        checker = new Checker(x,y,c);
}

Cell::Cell()
{
    pos = new Pos(0,0);
    checker=nullptr;
}

Cell::~Cell()
{
    if(pos!=nullptr)
        delete pos;
    if(checker!=nullptr)
        delete checker;
    pos = nullptr;
    checker=nullptr;
}

int Cell::return_num()
{
    if(get_checker() == nullptr)
        return 0;
    else if(get_checker()->isMyChecker() == true)
        return 1;
    else if (get_checker()->isMyChecker() == false)
        return 2;

}

Checker* Cell::get_checker()
{
    return checker;
}

Pos& Cell::get_pos()
{
    return *pos;
}
