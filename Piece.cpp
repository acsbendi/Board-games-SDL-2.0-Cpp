#include "Piece.h"

Piece::Piece(Point * point, Player * owner) : owner(owner), point(point) {}
const Point* Piece::getPoint() const
{
    return point;
}
void Piece::setPoint(Point * point)
{
    this->point = point;
}
const Player* Piece::getOwner() const
{
    return owner;
}
void Piece::setOwner(Player * t)
{
    owner = t;
}

Piece::~Piece()
{

}
