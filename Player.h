#ifndef JATEKOS_H_INCLUDED
#define JATEKOS_H_INCLUDED

#include <string>
#include <SDL.h>
#include "Piece.h"

using std::string;

class Piece;

class Point;

/** \brief The class representing players
 */
class Player {
protected:
    string name;            /**< The player's name, stored in a string object */
    Piece** pieces; /**< The array storing the player's pieces */
    int numberofpieces;     /**< The size of the pieces array */
    SDL_Surface* image;     /**< The image representing the player's piece(s), stored in a SDL_Image object */
    SDL_Texture* texture;   /**< The texture used for displaying the player's pieces on a screen */

public:

    /** \brief Constructor of the Player class
     *
     * \param name const char*  The name of the current player
     * \param numberofpieces int    The number of the pieces the player has
     * \param starting Point*   Starting point for the pieces of the player
     * \param image const char* The name of the image that represents the player's pieces
     * \param renderer SDL_Renderer*    The renderer on which the image will be shown
     *
     */
    Player(string name, int numberofpieces, Point* starting, const char* image, SDL_Renderer* renderer);

    /** \brief Indexing operator, for handling its pieces
     *
     * \param i int The index of the piece
     * \return Piece*&  Returns a reference of the piece (which is in fact a pointer to a Piece object) given by the index
     *
     */
    Piece*& operator[](int i);

    /** \brief Constant indexing operator, for handling its pieces
     *
     * \param i int The index of the piece
     * \return const Piece*  Returns a pointer to the constant piece given by the index
     *
     */
    const Piece* operator[](int i) const;

    /** \brief Returns the name of the player
     *
     * \return const string Constant string containing the name
     *
     */
    const string getName() const;

    /** \brief Returns the texture for the player's pieces
     *
     * \return SDL_Texture* Pointer to the texture
     *
     */
    SDL_Texture* getTexture() const;
    virtual ~Player();
};

#endif // JATEKOS_H_INCLUDED
