#ifndef MALOMPALYA_H_INCLUDED
#define MALOMPALYA_H_INCLUDED

#include "Board.h"
#include <SDL.h>
#include <SDL_ttf.h>

/** \brief The class that manages nine men's morris game
 */
class NineMensMorrisBoard : public Board {

    /*
    constants for graphics
    */
    static const int WINDOW_WIDTH = 400;
    static const int WINDOW_HEIGHT = 600;
    static const int BOARD_WIDTH = WINDOW_WIDTH;
    static const int BOARD_HEIGHT = 400;
    static const int FRAME_WIDTH = WINDOW_WIDTH;
    static const int FRAME_HEIGHT = (WINDOW_HEIGHT - BOARD_HEIGHT) / 2;
    static const int PIECE_SIDE = 40;
    static const int END_BUTTON_WIDTH = 175;
    static const int END_BUTTON_HEIGHT = 47;
    static const int END_BUTTON_Y = 450;
    static const int END_TEXT_Y = 190;
    static const int END_TEXT_SPACE = 75;
    static const int REMOVE_TEXT_SPACE = 40;
    const SDL_Color WHITE_LETTER_COLOR = {207, 149, 66};
    const SDL_Color BLACK_LETTER_COLOR = {50, 30, 10};
    const SDL_Color SELECTION_COLOR = {88, 93, 102};


    bool firstphase;        /**< Indicates whether the game is in the 1st phase, that is, the phase of placing pieces */
    int numberofwhitepieces;/**< Counts how many white pieces have been placed so far (in the 1st phase of the game) */
    int numberofblackpieces;/**< Counts how many black pieces have been placed so far (in the 1st phase of the game) */
    int mills[16][3];       /**< The array of the possible mills, it contains the ids of the points */
    bool over;              /**< Indicates the end of the game, it is needed because the game can end in multiple ways */

    /*
   SDL/graphical variables
   */
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Surface* boardimage = nullptr;
    SDL_Texture* boardimagetexture = nullptr;
    SDL_Surface* whitebackground = nullptr;
    SDL_Texture* whitebackgroundtexture = nullptr;
    SDL_Surface* blackbackground = nullptr;
    SDL_Texture* blackbackgroundtexture = nullptr;
    SDL_Surface* endbackground = nullptr;
    SDL_Texture* endbackgroundtexture = nullptr;
    SDL_Surface* cup = nullptr;
    SDL_Texture* cuptexture = nullptr;
    SDL_Surface* button = nullptr;
    SDL_Texture* buttontexture = nullptr;
    TTF_Font* letterfont = nullptr;
    TTF_Font* numberfont = nullptr;
    SDL_Surface* text = nullptr;
    SDL_Texture* texttexture = nullptr;
    SDL_Rect rect;      /**<  A rectangle to be freely overwritten for displaying various things on the screen */


    /** \brief Initializes the window, images etc needed for the graphical interface
     *
     * \return void
     *
     */
    void initGraphics();

    /** \brief Checks whether the game has to come to an end, by counting each player's pieces
     *
     * \return void
     *
     */
    void checkEnd();

    /** \brief Checks whether there is a mill on a given point
     *
     * \param point const Point* The point to be checked
     * \return int -1 if no mill was found, otherwise the index of the mill in the mills array
     *
     */
    int checkMill(const Point* point);

    /** \brief Handles the mill possibly created after a move
     *
     * \param point Point* The point onto which the last piece was moved
     * \return void
     *
     */
    void mill(const Point* point);

    /** \brief Checks whether the given player has only 3 pieces thus can move anywhere
     *
     * \param player int The player to be checked
     * \return bool True if the player can move anywhere, false otherwise
     *
     */
    bool anywhere(int player);


    /** \brief Handles the phase of placing pieces on the board
     *
     * \return void
     *
     */
    void firstPhase();

    /** \brief Handles the phase of moving pieces
     *
     * \return void
     *
     */
    void secondPhase();

    /** \brief Creates the points of the board, sets their position, neighbors, and the possible mills along them
     *
     * \return void
     *
     */
    void setPoints();

    /** \brief Shows the image of a player's piece in the given position
     *
     * \param position SDL_Point The position where the image should be displayed (the middle of the image will be here)
     * \param image SDL_Texture* The texture of the image to be shown
     * \return void
     *
     */
    void showImage(SDL_Point position, SDL_Texture* image);

    /** \brief Shows a text on the screen
     *
     * \param s const string The text to be shown
     * \param x int The x coordinate of the point where the text will be shown
     * \param y int The y coordinate of the point where the text will be shown
     * \param color SDL_Color The color of the text
     * \param font TTF_Font* The font of the text
     * \return void
     *
     */
    void showText(string s, int x, int y, SDL_Color color, TTF_Font* font);

    /** \brief Draws the frame during game
     *
      * \param top bool True, if the top frame should be drawn, false if the bottom frame should be drawn
     * \return void
     *
     */
    void drawFrame(bool top);

    /** \brief Draws the frame needed at the removal of a piece
    *
    * \param top bool True, if the top frame should be drawn, false if the bottom frame should be drawn
    * \return void
    *
    */
    void drawRemoveFrame(bool top);

    /** \brief Draws the frame needed when there's a new mill, but the other player has no removable pieces
     *
     * \param top bool True, if the top frame should be drawn, false if the bottom frame should be drawn
     * \return void
     *
     */
    void drawCantRemoveFrame(bool top);

    /** \brief Draws the board, with pieces
     *
     * \return void
     *
     */
    void drawBoard();

    /** \brief Waits until the user click on a point of the board and returns it
     *
     * \param point int& The id of the point on which the user has clicked, as a reference parameter
     * \return void
     *
     */
    void clickOnPoint(int& point);

    /** \brief Draws visual selection around a point
     *
     * \param point int The id of the point to draw visual selection around
     * \return void
     *
     */
    void selectPoint(int point);

    /** \brief Shows the end screen
     *
     * \param white bool Should be true if the winner is white, false otherwise
     * \return void
     *
     */
    void showEnd(bool white);
public:
    /** \brief
     *
     * \param languageresourcemanager LanguageResourceManager* A pointer to a previously created LanguageResourceManager object, used for storing storing language specific resources
     *
     */
    explicit NineMensMorrisBoard(LanguageResourceManager* languageresourcemanager);

    /** \brief Handles the course of the play after the creation of the game
    *
    * \return void
    *
    */
    void play() override;
    ~NineMensMorrisBoard() override;
};

#endif // MALOMPALYA_H_INCLUDED
