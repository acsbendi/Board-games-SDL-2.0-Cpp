#ifndef PIECE_H_INCLUDED
#define PIECE_H_INCLUDED

#include "Player.h"
#include "Point.h"

class Player;

class Point;

/** \brief The class representing player's pieces
     */
class Piece {
protected:
    Player* owner; /**< The owner of the piece */
    Point* point;  /**< The point on which the piece is currently */
public:

    /** \brief Constructor of the Piece class
     *
     * \param starting Point* The starting point of the piece
     * \param owner Player* The owner of the piece
     *
     */
    Piece(Point* starting, Player* owner);

    /** \brief Returns the point on which the piece is currently
     *
     * \return const Point* Pointer to the piece's point
     *
     */
    const Point* getPoint() const;


    /** \brief Sets the piece's current point
     *
     * \param point Point* The point on which the piece should be
     * \return void
     *
     */
    void setPoint(Point* point);

    /** \brief Returns the piece's current owner
     *
     * \return const Player* Pointer to the piece's owner (constant)
     *
     */
    const Player* getOwner() const;
    virtual ~Piece();
};


#endif // PIECE_H_INCLUDED
