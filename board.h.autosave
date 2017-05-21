#ifndef BOARD_H
#define BOARD_H
#include"cell.h"
#include"pos.h"
#include<string>
#include<vector>

using namespace std;

class Board
{
    friend Game;

    Cell** cells;
    vector<Cell*> mycells;
    vector<Cell*> oppcells;
    vector<Cell*> emptycells;
    void set_cell(int x , int y , char c  );

public:
    void update(string s);
    Board();
    ~Board();
    Cell** get_cells();
    vector<Cell*>& get_myCells();
    vector<Cell*>& get_oppCells();
    vector<Cell*>& get_emptyCells();
    Cell& get_cell(Pos p);
    Cell& get_cell(int x,int y);
};

#endif // BOARD_H
