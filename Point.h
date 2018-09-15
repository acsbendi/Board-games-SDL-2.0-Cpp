#ifndef MEZO_H_INCLUDED
#define MEZO_H_INCLUDED

#include <SDL.h>
#include "Player.h"
#include "Piece.h"

class Piece;

/** \brief The class representing the points of a board, where pieces can move (e.g. the squares in snakes and ladders)
 */
class Point {
protected:
    const int id;   /**< The identification number of the point  */
    Point* neighbors[4];   /**< The array containing pointers to the neighbors of the point (4 at most) */
    Piece* piece;  /**< Pointer to the piece on the point */
    SDL_Point coordinates; /**< SDL structure for storing x,y coordinates on the window  */
public:

    /** \brief Constructor of the Point class
     *
     * \param id int The identification number to be set
     *
     */
    explicit Point(int id);

    /** \brief Indexing operator, for handling its neighbors
     *
     * \param i int The index of the neighbor
     * \return Point*& Reference of the neighbor given by its index
     *
     */
    Point*& operator[](int i);

    /** \brief Constant indexing operator, for handling its neighbors
     *
     * \param i int The index of the neighbor
     * \return const Point* The neighbor given by its index
     *
     */
    const Point* operator[](int i) const;

    /** \brief Checks whether the point is occupied by a piece
     *
     * \return bool True if occupied, false if not
     *
     */
    bool isOccupied() const;

    /** \brief Sets a piece on the point
     *
     * \param piece Piece*  A pointer to a piece to occupy the point
     * \return void
     *
     */
    void setPiece(Piece* piece);

    /** \brief Returns the piece on the point
     *
     * \return Piece* A pointer to the piece occupying the point
     *
     */
    Piece* getPiece() const;

    /** \brief Returns the id of the point
     *
     * \return int The id of the point
     *
     */
    int getId() const;

    /** \brief Sets the coordinates of the point
     *
     * \param coord SDL_Point An SDL_Point struct to set
     * \return void
     *
     */
    void setCoordinates(SDL_Point coord);

    /** \brief Return the coordinates of the point
     *
     * \return SDL_Point The SDL_Point struct containing the coordinates
     *
     */
    SDL_Point getCoordinates() const;
    virtual ~Point();
};

#endif // MEZO_H_INCLUDED
