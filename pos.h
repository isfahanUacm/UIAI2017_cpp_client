#ifndef POS_H
#define POS_H
class Board;
class Pos
{
    friend Board;
    int x,y;
public:
    Pos(int,int);
    int getx();
    int gety();
};

#endif // POS_H
