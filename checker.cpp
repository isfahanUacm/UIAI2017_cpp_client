#include "checker.h"

Checker::Checker(int x, int y, char c)
{
    pos = new Pos(x,y);
    ismychecker = (c=='m')? true : false;
}
Checker::~Checker()
{
    if(pos)
        delete pos;
    pos=nullptr;
}

bool Checker::isMyChecker()
{
    return ismychecker;
}

Pos& Checker::get_pos()
{
    return *pos;
}
