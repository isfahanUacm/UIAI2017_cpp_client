#ifndef CHECKER_H
#define CHECKER_H
#include"pos.h"

class Checker
{
    Pos* pos;
    bool ismychecker;
public:
    Checker(int,int,char); // char m->mine | o->opp
    ~Checker();
    bool isMyChecker();
    Pos& get_pos();

};

#endif // CHECKER_H
