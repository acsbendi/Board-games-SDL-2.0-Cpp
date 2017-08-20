#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include "point.h"
#include "player.h"
#include "LanguageResourceManager.h"

/** \brief The base class for boards, each tables game inherits from this
 */
class Board{
protected:
    Point ** points;        /**< The array of points, arbitrary number of elements -> dynamically allocated */
    Player * players[6];    /**< The array of players, 6 elements at most */
    int current;            /**< The current player to play */
    int numberofplayers;    /**< The number of players playing the current game */
    int numberofpoints;     /**< The number of points the current board uses */
    LanguageResourceManager* languageresourcemanager; /**< A pointer to a previously created LanguageResourceManager object, used for storing storing language specific resources */
    Board();
public:
    virtual void play() = 0;
    virtual ~Board();
};





#endif // BOARD_H_INCLUDED
