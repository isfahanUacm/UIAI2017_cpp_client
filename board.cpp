#include "board.h"
#include<iostream>
using namespace std;

Board::Board() //this constructor has bug high potential!!!
{
    cells = new Cell*[8];
    for(int i=0;i<8;i++)
        cells[i]= new Cell[3]();
}


void Board::set_cell(int x, int y, char c)
{
    cells[x][y].set_checker(x,y,c);
}

void Board::update(string s)
{
    mycells.clear();
    oppcells.clear();
    emptycells.clear();
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<3;j++)
        {
            cells[i][j].pos->x=i;
            cells[i][j].pos->y=j;
            cells[i][j].checker=nullptr;
            if(s[0]!='e')
            {
                cells[i][j].checker = new Checker(i,j,s[0]);
                if(s[0]=='m')
                    mycells.push_back(&cells[i][j]);
                else
                    oppcells.push_back(&cells[i][j]);
            }
            else
            {
                emptycells.push_back(&cells[i][j]);
            }
            if(s.length()>=2)
                s=s.substr(2);
        }
    }
}

Board::~Board()
{
    for(int i=0;i<8;i++)
    {
        delete[] cells[i];
        cells[i] = nullptr;
    }
    delete cells;
    cells = nullptr;

    mycells.clear();
    oppcells.clear();
    emptycells.clear();
}

Cell** Board::get_cells()
{
    return cells;
}

Cell& Board::get_cell(Pos p)
{
    return cells[p.getx()][p.gety()];
}

Cell& Board::get_cell(int x, int y)
{
    return cells[x][y];
}

vector<Cell*>& Board::get_myCells()  //must test!
{
    return mycells;
}

vector<Cell*>& Board::get_oppCells() //must test!
{
    return oppcells;
}

vector<Cell*>& Board::get_emptyCells() //must test!
{
    return emptycells;
}
