#include "Point.h"

Point::Point(int az) : id(az), piece(nullptr) {
    for (auto& neighbor : neighbors)
        neighbor = nullptr;
}

Point*& Point::operator[](int i) {
    return neighbors[i];
}

const Point* Point::operator[](int i) const {
    return neighbors[i];
}

bool Point::isOccupied() const {
    return piece != nullptr;
}

void Point::setPiece(Piece* piece) {
    this->piece = piece;
}

Piece* Point::getPiece() const {
    return piece;
}

int Point::getId() const {
    return id;
}

void Point::setCoordinates(SDL_Point koord) {
    coordinates = koord;
}

SDL_Point Point::getCoordinates() const {
    return coordinates;
}

Point::~Point() = default;

