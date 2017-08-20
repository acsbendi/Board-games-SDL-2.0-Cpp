#include "point.h"

Point::Point(int az) : id(az), piece(0)
{
    for(int i = 0; i < 4; i++) neighbors[i] = 0;
}
Point *& Point::operator[](int i)
{
    return neighbors[i];
}
const Point * Point::operator[](int i) const
{
    return neighbors[i];
}
bool Point::isOccupied() const
{
    return piece != 0;
}
void Point::setPiece(Piece * piece)
{
    this->piece = piece;
}
Piece * Point::getPiece() const
{
    return piece;
}
int Point::getId() const
{
    return id;
}
void Point::setCoordinates(SDL_Point koord)
{
    coordinates = koord;
}
SDL_Point Point::getCoordinates() const
{
    return coordinates;
}
Point::~Point() {}

