#ifndef CELL_H
#define CELL_H
#include"pos.h"
#include"checker.h"
class Board;
class Game;
class Cell
{
    friend Board;
    friend Game;
    Pos* pos;
    Checker* checker;
    void set_checker (int x, int y , char c);

public:
    Cell(int,int,char); // char e->empty | m->mine | o->opp
    Cell();
    Checker* get_checker();
    Pos& get_pos();
    ~Cell();
    int return_num();

};

#endif // CELL_H
