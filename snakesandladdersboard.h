#ifndef KIGYOKESLETRAKPALYA_H_INCLUDED
#define KIGYOKESLETRAKPALYA_H_INCLUDED

#include "Board.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

/** \brief The class that manages snakes and ladders game
 */
class SnakesAndLaddersBoard : public Board {
    /*
    constants for graphics
    */
    static const int WINDOW_WIDTH = 904;
    static const int WINDOW_HEIGHT = 704;
    static const int BOARD_WIDTH = 704;
    static const int BOARD_HEIGHT = 704;
    static const int START_BUTTON_WIDTH = 150;
    static const int START_BUTTON_HEIGHT = 42;
    static const int START_BUTTON_Y = 550;
    static const int START_BUTTON_X = BOARD_WIDTH + (WINDOW_WIDTH - BOARD_WIDTH - START_BUTTON_WIDTH) / 2;
    static const int PIECE_WIDTH = 19;
    static const int PIECE_HEIGHT = 30;
    static const int END_PIECE_WIDTH = 60;
    static const int END_PIECE_HEIGHT = 100;
    static const int END_PIECE_Y = 125;
    static const int ROLL_BUTTON_DIAMETER = 175;
    static const int ROLL_BUTTON_Y = 500;
    static const int ROLL_BUTTON_X = BOARD_WIDTH + (WINDOW_WIDTH - BOARD_WIDTH - ROLL_BUTTON_DIAMETER) / 2;
    static const int END_BUTTON_WIDTH = 175;
    static const int END_BUTTON_HEIGHT = 47;
    static const int END_BUTTON_Y = 500;
    static const int INCREMENT_BUTTON_WIDTH = 75;
    static const int INCREMENT_BUTTON_HEIGHT = 57;
    static const int INCREMENT_BUTTON_Y = 220;
    static const int INCREMENT_BUTTON_X = BOARD_WIDTH + (WINDOW_WIDTH - BOARD_WIDTH - INCREMENT_BUTTON_WIDTH) / 2;
    static const int DECREMENT_BUTTON_Y = 420;
    static const int WREATH_WIDTH = 150;
    static const int WREATH_HEIGHT = 150;
    static const int WREATH_Y = 107;
    static const int SQUARE_SIDE = 66;
    static const int ANIMATION_DELAY = 33;
    static const int ROLL_IMAGE_WIDTH = 130;
    static const int ROLL_IMAGE_HEIGHT = 280;
    static const int ROLL_IMAGE_X = BOARD_WIDTH + (WINDOW_WIDTH - BOARD_WIDTH - ROLL_IMAGE_WIDTH) / 2;
    static const int ROLL_IMAGE_Y = 140;
    static const int DICE_SHAKER_WIDTH = 150;
    static const int DICE_SHAKER_HEIGHT = 150;
    static const int DICE_SHAKER_X = BOARD_WIDTH + (WINDOW_WIDTH - BOARD_WIDTH - DICE_SHAKER_WIDTH) / 2;
    static const int SELECTION_TEXT_Y = 35;
    static const int SELECTION_TEXT_SPACE = 50;
    static const int NUMBER_OF_PLAYERS_X = 787;
    static const int NUMBER_OF_PLAYERS_Y = 310;
    static const int END_TEXT_Y = 260;
    static const int END_TEXT_SPACE = 70;
    const SDL_Color TEXT_COLOR = {24, 22,
                                  22}; /**< The color of various texts (including numbers on the board) on the screen */


    /*
    SDL/graphical variables
    */
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Surface* boardimage = nullptr;
    SDL_Texture* boardimagetexture = nullptr;
    SDL_Surface* lightsquare = nullptr;
    SDL_Texture* lightsquaretexture = nullptr;
    SDL_Surface* lightsquare2 = nullptr;
    SDL_Texture* lightsquare2texture = nullptr;
    SDL_Surface* darksquare = nullptr;
    SDL_Texture* darksquaretexture = nullptr;
    SDL_Surface* darksquare2 = nullptr;
    SDL_Texture* darksquare2texture = nullptr;
    SDL_Surface* background = nullptr;
    SDL_Texture* backgroundtexture = nullptr;
    SDL_Surface* incrementbutton = nullptr;
    SDL_Texture* incrementbuttontexture = nullptr;
    SDL_Surface* button = nullptr;
    SDL_Texture* buttontexture = nullptr;
    SDL_Surface* endbutton = nullptr;
    SDL_Texture* endbuttontexture = nullptr;
    SDL_Surface* rollbutton = nullptr;
    SDL_Texture* rollbuttontexture = nullptr;
    SDL_Surface* rollimage = nullptr;
    SDL_Texture* rollimagetexture = nullptr;
    SDL_Surface* diceshaker = nullptr;
    SDL_Texture* diceshakertexture = nullptr;
    SDL_Surface* greenbackground = nullptr;
    SDL_Texture* greenbackgroundtexture = nullptr;
    SDL_Surface* endbackground = nullptr;
    SDL_Texture* endbackgroundtexture = nullptr;
    SDL_Surface* wreath = nullptr;
    SDL_Texture* wreathtexture = nullptr;
    TTF_Font* numberfont = nullptr;
    TTF_Font* letterfont = nullptr;
    SDL_Surface* number = nullptr;
    SDL_Texture* numbertexture = nullptr;
    SDL_Rect rect;      /**<  A rectangle to be freely overwritten for displaying various things on the screen */



    /*!
    \brief Waits for a click event

    \param x Sets the x coordinate of the mouse click
    \param y Sets the y coordinate of the mouse click

    \return int 1 on success, 0 on failure
    */
    int click(int& x, int& y);

    /*!
    \brief Displays a piece on a point of the board

    \param point The point on which to display (1-100)
    \param piece The piece to be displayed - given by the array index (0-5)
    */
    void pieceOnPoint(const Point* point, int piece);

    /** \brief Draws an empty board (without pieces) onto the screen
     *
     * \return void
     *
     */
    void drawEmptyBoard();

    /**
    \brief Handles visual part of a roll event - waits for a mouse click and shows the rolled number

    \param number The randomized rolled number.
    */
    void roll(int number);


    /** \brief The selection of the number of players by the user on the graphical interface
     *
     * \return int The number of players selected by the user
     *
     */
    int selectNumberOfPlayers();

    /** \brief Handles the next turn of the game
     *
     * \return void
     *
     */
    void turn();

    /** \brief Initializes the window, images etc needed for the graphical interface
     *
     * \return void
     *
     */
    void initGraphics();


    /** \brief  Creates the points of the board and sets the connections between them
     *
     * \param size int The size of the board, that is, how many points (squares) it contains
     * \param connections const char* The connections between points of the table, both ends of snakes and ladders (by point ids)
     * \return void
     *
     */
    void setPoints(int size, const char* connections);

    /** \brief Draws the graphical interface for selecting the number of players
     *
     * \param current int  Currently selected number of players
     * \return void
     *
     */
    void drawSelection(int current);

    /** \brief Draws the entire board, including pieces
     *
     * \return void
     *
     */
    void drawBoard();

    /** \brief Draws the roll interface located on the right, with the roll button
     *
     * \return void
     *
     */
    void drawRoll();

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

    /** \brief Shows a short animation of a dice roll
     *
     * \param roll int  The rolled number - it is shown in the animation
     * \return void
     *
     */
    void rollAnimation(int roll);

    /** \brief Shows the end screen
     *
     * \param winner int The winning player's index
     * \return void
     *
     */
    void showEnd(int winner);


public:

    /** \brief
     *
     * \param languageresourcemanager LanguageResourceManager* A pointer to a previously created LanguageResourceManager object, used for storing storing language specific resources
     * \param 100 int size= The size of the board, that is, how many points (squares) it contains
     * \param const char* connections = "34-1 3-51 25-5 6-27 47-19 20-70 36-55 65-52 87-57 91-61 63-95 68-98 99-69" The connections between points of the table, both ends of snakes and ladders,
     *        it has to be the default for the graphical interface to work correctly
     *
     */
    explicit SnakesAndLaddersBoard(LanguageResourceManager* languageresourcemanager, int size = 100,
                                   const char* connections = "34-1 3-51 25-5 6-27 47-19 20-70 36-55 65-52 87-57 91-61 63-95 68-98 99-69");

    /** \brief Handles the course of the play after the creation of the game
     *
     * \return void
     *
     */
    void play() override;

    ~SnakesAndLaddersBoard() override;
};

#endif // KIGYOKESLETRAKPALYA_H_INCLUDED
