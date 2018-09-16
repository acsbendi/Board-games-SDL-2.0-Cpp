#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include <iostream>
#include <string>
#include <sstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>
#include "ninemensmorrisboard.h"
#include "snakesandladdersboard.h"
#include "LanguageResourceManager.h"


/** \brief The class that manages game and language selection, each game can be started from here
 */
class Application {
    /** \brief The part of screen the user's mouse is currently pointing at
     */
    enum Selected {
        ninemensmorris, snakesandladders, language, none
    };
    Selected selected = none;   /**< State variable for indicating mouse position */
    LanguageResourceManager* languageresourcemanager;
    static constexpr int WINDOW_WIDTH = 640;
    static constexpr int WINDOW_HEIGHT = 480;
    static constexpr int LANGUAGE_SELECTION_ICON_X = 585;
    static constexpr int LANGUAGE_SELECTION_ICON_Y = 20;
    static constexpr int LANGUAGE_SELECTION_ICON_SIDE = 35;
    static constexpr int LANGUAGE_LIST_X = 460;
    static constexpr int LANGUAGE_LIST_Y = 48;
    static constexpr int LANGUAGE_LIST_WIDTH = 150;
    static constexpr int LANGUAGE_LIST_TEXT_WIDTH = 120;
    static constexpr int LANGUAGE_LIST_TEXT_X = 480;
    static constexpr int LANGUAGE_LIST_TEXT_Y_DIFFERENCE = 5;
    static constexpr int LANGUAGE_LIST_ITEM_HEIGHT = 39;
    static constexpr int LANGUAGE_LIST_TOP_HEIGHT = 18;
    static constexpr int LANGUAGE_LIST_BOTTOM_HEIGHT = 18;
    static constexpr int LANGUAGE_LIST_BOTTOM_OVERLAP = 5;
    static constexpr SDL_Color LETTER_COLOR = {44, 127, 3};
    static constexpr SDL_Color SELECTION_COLOR = {88, 93, 102, 130};
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Surface* startpicture = nullptr;
    SDL_Texture* startpicturetexture = nullptr; //infrastructure, manufacture
    SDL_Surface* languageselectionicon = nullptr;
    SDL_Texture* languageselectionicontexture = nullptr;
    SDL_Surface* languageselectiontop = nullptr;
    SDL_Texture* languageselectiontoptexture = nullptr;
    SDL_Surface* languageselectionmiddle = nullptr;
    SDL_Texture* languageselectionmiddletexture = nullptr;
    SDL_Surface* languageselectionmiddlewhite = nullptr;
    SDL_Texture* languageselectionmiddlewhitetexture = nullptr;
    SDL_Surface* languageselectionbottom = nullptr;
    SDL_Texture* languageselectionbottomtexture = nullptr;
    SDL_Surface* text = nullptr;
    SDL_Texture* texttexture = nullptr;
    TTF_Font* font = nullptr;  /**< Font used for showing the text of languages */
    Language temporaryselectedlanguage;  /**< Indicates which language's rectangle (showing the language) was the mouse pointing on last */

    /** \brief Shows the default start menu, without anything being selected
     *
     * \return void
     *
     */
    void noneSelected();

    /** \brief Shows nine mens morris as being selected in the start menu
     *
     * \return void
     *
     */
    void nineMensMorrisSelected();

    /** \brief Opens a menu showing the available languages for the user to choose from
     *
     * \return void
     *
     */
    void languageSelection();

    /** \brief Shows snakes and ladders as being selected in the start menu
     *
     * \return void
     *
     */
    void snakesAndLaddersSelected();

    /** \brief Starts a new snakes and ladders game (in a new window)
     *
     * \return void
     *
     */
    void startSnakesAndLadders();

    /** \brief Starts a new nine men's morris game (in a new window)
     *
     * \return void
     *
     */
    void startNineMensMorris();

    /** \brief Initializes the window, images etc needed for the graphical interface
     *
     * \return void
     *
     */
    void initGraphics();

    void onMouseMotion(const SDL_MouseMotionEvent& motionevent);
    void onMouseButtonDown(const SDL_Event& event);


public:
    Application();

    /** \brief Starts the application, and handles user interaction on the main menu
     *
     * \return void
     *
     */
    void start();

    ~Application();
};


#endif // APPLICATION_H_INCLUDED
