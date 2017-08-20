#include "board.h"

Board::Board() {}
Board::~Board()
{
    for(int i = 0; i < numberofpoints; i++)
    {
        delete points[i];
    }
    delete[] points;
    for(int i = 0; i < numberofplayers; i++)
        delete players[i];
}


