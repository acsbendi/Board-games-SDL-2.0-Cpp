#include "Application.h"

Application::Application()
{
    languageresourcemanager = new LanguageResourceManager(english);
    temporaryselectedlanguage = languageresourcemanager->getCurrentLanguage();
    initGraphics();
    noneSelected();
    SDL_SetWindowTitle(window,languageresourcemanager->getApplicationWindowTitle().c_str());
    SDL_RenderPresent(renderer);
}

void Application::initGraphics()
{
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cerr << languageresourcemanager->getSDLErrorText() << SDL_GetError() << std::endl;
        return;
    }

    if(TTF_Init() == -1 )
    {
        std::cerr << languageresourcemanager->getTTFErrorText() << TTF_GetError() << std::endl;
        return;
    }

    font = TTF_OpenFont("resources/fonts/times.ttf", 120);
    if(font == NULL)
    {
        std::cerr << languageresourcemanager->getFontErrorText() << SDL_GetError() << std::endl;
        return;
    }
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);

    startpicture = SDL_LoadBMP("resources/images/start.bmp");
    if(startpicture == NULL)
    {
        std::cerr << languageresourcemanager->getImageErrorText() << SDL_GetError() << std::endl;
        return;
    }

    languageselectionicon = IMG_Load("resources/images/languageselectionicon.png");
    if(languageselectionicon == NULL)
    {
        std::cerr << languageresourcemanager->getImageErrorText() << SDL_GetError() << std::endl;
        return;
    }

    languageselectiontop = IMG_Load("resources/images/languageselectiontop.png");
    if(languageselectiontop == NULL)
    {
        std::cerr << languageresourcemanager->getImageErrorText() << SDL_GetError() << std::endl;
        return;
    }

    languageselectionmiddle = IMG_Load("resources/images/languageselectionmiddle.png");
    if(languageselectionmiddle == NULL)
    {
        std::cerr << languageresourcemanager->getImageErrorText() << SDL_GetError() << std::endl;
        return;
    }

    languageselectionmiddlewhite = IMG_Load("resources/images/languageselectionmiddlewhite.png");
    if(languageselectionmiddle == NULL)
    {
        std::cerr << languageresourcemanager->getImageErrorText() << SDL_GetError() << std::endl;
        return;
    }

    languageselectionbottom = IMG_Load("resources/images/languageselectionbottom.png");
    if(languageselectionbottom == NULL)
    {
        std::cerr << languageresourcemanager->getImageErrorText() << SDL_GetError() << std::endl;
        return;
    }

    window = SDL_CreateWindow( languageresourcemanager->getApplicationWindowTitle().c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
        std::cerr <<  languageresourcemanager->getWindowErrorText() <<  SDL_GetError() << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    startpicturetexture = SDL_CreateTextureFromSurface(renderer, startpicture);
    languageselectionicontexture = SDL_CreateTextureFromSurface(renderer, languageselectionicon);
    languageselectiontoptexture = SDL_CreateTextureFromSurface(renderer, languageselectiontop);
    languageselectionmiddletexture = SDL_CreateTextureFromSurface(renderer, languageselectionmiddle);
    languageselectionmiddlewhitetexture = SDL_CreateTextureFromSurface(renderer, languageselectionmiddlewhite);
    languageselectionbottomtexture = SDL_CreateTextureFromSurface(renderer, languageselectionbottom);
}


void Application::start()
{
    SDL_Event event;
    while(SDL_WaitEvent(&event) && event.type != SDL_QUIT) //waiting for user interaction
    {
        switch(event.type)
        {
        case SDL_MOUSEMOTION:
            //the mouse stays near the language selection icon
            if(selected == language && event.motion.x > LANGUAGE_LIST_X &&
                    event.motion.y < LANGUAGE_LIST_Y + LANGUAGE_LIST_TOP_HEIGHT + (int)languageresourcemanager->getLanguages().size()*LANGUAGE_LIST_ITEM_HEIGHT - LANGUAGE_LIST_BOTTOM_OVERLAP + LANGUAGE_LIST_BOTTOM_HEIGHT)
            {
                for(int i = 0; i < (int)languageresourcemanager->getLanguages().size(); i++)
                {
                    if(temporaryselectedlanguage != languageresourcemanager->getLanguages()[i] &&
                            event.motion.x >LANGUAGE_LIST_X && event.motion.y > LANGUAGE_LIST_Y + LANGUAGE_LIST_TOP_HEIGHT + i*LANGUAGE_LIST_ITEM_HEIGHT &&
                            event.motion.x < LANGUAGE_LIST_X + LANGUAGE_LIST_WIDTH &&
                            event.motion.y < LANGUAGE_LIST_Y + LANGUAGE_LIST_TOP_HEIGHT + i*LANGUAGE_LIST_ITEM_HEIGHT + LANGUAGE_LIST_ITEM_HEIGHT)
                        temporaryselectedlanguage = languageresourcemanager->getLanguages()[i];
                    languageSelection();
                }
            }
            //the mouse moves onto the language selection icon
            else if(event.motion.x > LANGUAGE_SELECTION_ICON_X && event.motion.x < LANGUAGE_SELECTION_ICON_X + LANGUAGE_SELECTION_ICON_SIDE &&
                    event.motion.y > LANGUAGE_SELECTION_ICON_Y && event.motion.y < LANGUAGE_SELECTION_ICON_Y + LANGUAGE_SELECTION_ICON_SIDE )
            {
                if(selected != language)
                {
                    temporaryselectedlanguage = languageresourcemanager->getCurrentLanguage();
                    languageSelection();
                }
                selected = language;
            }
            else if(event.motion.x < 264 + event.motion.y*((double)100/480)) //the mouse is on the left side, which means nine men's morris is selected
            {
                if(selected != ninemensmorris) nineMensMorrisSelected();
                selected = ninemensmorris;
            }
            else if(event.motion.x > 275 + event.motion.y*((double)100/480)) //the mouse is on the right side, which means snakes and ladders is selected
            {
                if(selected != snakesandladders) snakesAndLaddersSelected();
                selected = snakesandladders;
            }
            else  //the mouse is on the middle line, which means nothing is selected
            {
                selected = none;
                noneSelected();
                SDL_SetWindowTitle(window,languageresourcemanager->getApplicationWindowTitle().c_str());
                SDL_RenderPresent(renderer);
            }
            break;
        case SDL_MOUSEBUTTONDOWN:   //mouse click
            switch(selected)    //where it happened (current position of the mouse)
            {
            case ninemensmorris:
                SDL_HideWindow(window);  //when a game is running, the main menu should not be visible
                startNineMensMorris();
                SDL_Delay(1000);    //waiting for the game to close properly, this takes a short while
                SDL_ShowWindow(window);
                nineMensMorrisSelected();
                break;
            case snakesandladders:
                SDL_HideWindow(window); //when a game is running, the main menu should not be visible
                startSnakesAndLadders();
                SDL_Delay(1000);    //waiting for the game to close properly, this takes a short while
                SDL_ShowWindow(window);
                snakesAndLaddersSelected();
                break;
            case language:
                for(int i = 0; i < (int)languageresourcemanager->getLanguages().size(); i++)
                {
                    if(languageresourcemanager->getCurrentLanguage() != languageresourcemanager->getLanguages()[i] &&
                            event.motion.x >LANGUAGE_LIST_X && event.motion.y > LANGUAGE_LIST_Y + LANGUAGE_LIST_TOP_HEIGHT + i*LANGUAGE_LIST_ITEM_HEIGHT &&
                            event.motion.x < LANGUAGE_LIST_X + LANGUAGE_LIST_WIDTH &&
                            event.motion.y < LANGUAGE_LIST_Y + LANGUAGE_LIST_TOP_HEIGHT + i*LANGUAGE_LIST_ITEM_HEIGHT + LANGUAGE_LIST_ITEM_HEIGHT)
                    {
                        languageresourcemanager->setLanguage(languageresourcemanager->getLanguages()[i]);
                        languageSelection();
                    }
                }
                break;
            case none:
                break;
            }
            break;
        }
    }
}

void Application::noneSelected()
{
    SDL_RenderCopy(renderer,startpicturetexture,0,0);
    SDL_Rect rect = {LANGUAGE_SELECTION_ICON_X,LANGUAGE_SELECTION_ICON_Y,LANGUAGE_SELECTION_ICON_SIDE,LANGUAGE_SELECTION_ICON_SIDE};
    SDL_RenderCopy(renderer,languageselectionicontexture,0,&rect);
}

void Application::nineMensMorrisSelected()
{
    noneSelected();
    SDL_SetWindowTitle(window,languageresourcemanager->getNineMensMorrisWindowTitle().c_str());
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    thickLineRGBA(renderer,256,0,356,480,15,SELECTION_COLOR.r,SELECTION_COLOR.g,SELECTION_COLOR.b,SELECTION_COLOR.a);
    thickLineRGBA(renderer,0,5,254,5,20,SELECTION_COLOR.r,SELECTION_COLOR.g,SELECTION_COLOR.b,SELECTION_COLOR.a);
    thickLineRGBA(renderer,5,11,5,480,20,SELECTION_COLOR.r,SELECTION_COLOR.g,SELECTION_COLOR.b,SELECTION_COLOR.a);
    thickLineRGBA(renderer,10,475,354,475,20,SELECTION_COLOR.r,SELECTION_COLOR.g,SELECTION_COLOR.b,SELECTION_COLOR.a);
    SDL_RenderPresent(renderer);
}

void Application::languageSelection()
{
    noneSelected();
    SDL_Rect rect = {LANGUAGE_LIST_X,LANGUAGE_LIST_Y,LANGUAGE_LIST_WIDTH,LANGUAGE_LIST_TOP_HEIGHT};
    SDL_RenderCopy(renderer,languageselectiontoptexture,0,&rect);
    const vector<Language>& languages = languageresourcemanager->getLanguages();
    for(int i = 0; i < (int)languages.size(); i++)
    {
        rect = {LANGUAGE_LIST_X,LANGUAGE_LIST_Y + LANGUAGE_LIST_TOP_HEIGHT + i*LANGUAGE_LIST_ITEM_HEIGHT,LANGUAGE_LIST_WIDTH,LANGUAGE_LIST_ITEM_HEIGHT};
        SDL_RenderCopy(renderer,languages[i] == temporaryselectedlanguage ? languageselectionmiddlewhitetexture : languageselectionmiddletexture,0,&rect);
        SDL_FreeSurface(text);
        text = TTF_RenderUTF8_Blended(font,languageresourcemanager->getLanguageString(languages[i]).c_str(),LETTER_COLOR);
        SDL_DestroyTexture(texttexture);
        texttexture =  SDL_CreateTextureFromSurface(renderer, text);
        rect = {LANGUAGE_LIST_TEXT_X,LANGUAGE_LIST_Y + LANGUAGE_LIST_TOP_HEIGHT + i*LANGUAGE_LIST_ITEM_HEIGHT - LANGUAGE_LIST_TEXT_Y_DIFFERENCE,
                LANGUAGE_LIST_TEXT_WIDTH,LANGUAGE_LIST_ITEM_HEIGHT
               };
        SDL_RenderCopy(renderer,texttexture,0,&rect);
    }
    rect = {LANGUAGE_LIST_X,LANGUAGE_LIST_Y + LANGUAGE_LIST_TOP_HEIGHT + (int)languages.size()*LANGUAGE_LIST_ITEM_HEIGHT - LANGUAGE_LIST_BOTTOM_OVERLAP,
            LANGUAGE_LIST_WIDTH,LANGUAGE_LIST_BOTTOM_HEIGHT
           };
    SDL_RenderCopy(renderer,languageselectionbottomtexture,0,&rect);
    SDL_RenderPresent(renderer);
    SDL_SetWindowTitle(window,languageresourcemanager->getLanguageSelectionText().c_str());
}

void Application::snakesAndLaddersSelected()
{
    noneSelected();
    SDL_SetWindowTitle(window,languageresourcemanager->getSnakesAndLaddersWindowTitle().c_str());
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    thickLineRGBA(renderer,290,10,640,10,20,SELECTION_COLOR.r,SELECTION_COLOR.g,SELECTION_COLOR.b,SELECTION_COLOR.a);
    thickLineRGBA(renderer,284,0,384,480,15,SELECTION_COLOR.r,SELECTION_COLOR.g,SELECTION_COLOR.b,SELECTION_COLOR.a);
    thickLineRGBA(renderer,630,15,630,480,20,SELECTION_COLOR.r,SELECTION_COLOR.g,SELECTION_COLOR.b,SELECTION_COLOR.a);
    thickLineRGBA(renderer,388,470,620,470,20,SELECTION_COLOR.r,SELECTION_COLOR.g,SELECTION_COLOR.b,SELECTION_COLOR.a);
    SDL_RenderPresent(renderer);
}

void Application::startSnakesAndLadders()
{
    SnakesAndLaddersBoard snakesandladdersboard(languageresourcemanager);
    snakesandladdersboard.play();
}

void Application::startNineMensMorris()
{
    NineMensMorrisBoard ninemensmorrisboard(languageresourcemanager);
    ninemensmorrisboard.play();
}

Application::~Application()
{
    delete languageresourcemanager;
    SDL_FreeSurface(startpicture);
    SDL_DestroyTexture(startpicturetexture);
    SDL_FreeSurface(languageselectionicon);
    SDL_DestroyTexture(languageselectionicontexture);
    SDL_FreeSurface(languageselectiontop);
    SDL_DestroyTexture(languageselectiontoptexture);
    SDL_FreeSurface(languageselectionmiddle);
    SDL_DestroyTexture(languageselectionmiddletexture);
    SDL_FreeSurface(languageselectionmiddlewhite);
    SDL_DestroyTexture(languageselectionmiddlewhitetexture);
    SDL_FreeSurface(languageselectionbottom);
    SDL_DestroyTexture(languageselectionbottomtexture);
    SDL_FreeSurface(text);
    SDL_DestroyTexture(texttexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
