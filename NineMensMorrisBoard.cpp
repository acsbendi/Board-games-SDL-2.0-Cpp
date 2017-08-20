#include <iostream>
#include <algorithm>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>
#include "helper.h"
#include "ninemensmorrisboard.h"

using std::find;

void NineMensMorrisBoard::selectPoint(int point)
{
    filledCircleRGBA(renderer,points[point-1]->getCoordinates().x,points[point-1]->getCoordinates().y,25,SELECTION_COLOR.r,SELECTION_COLOR.g,SELECTION_COLOR.b,255);
    showImage(points[point-1]->getCoordinates(), points[point-1]->getPiece()->getOwner()->getTexture());
    SDL_RenderPresent(renderer);
}

void NineMensMorrisBoard::showText(const string s, int x, int y, SDL_Color szin, TTF_Font * font)
{
    int w,h;
    TTF_SizeUTF8(font, s.c_str(), &w, &h);
    SDL_FreeSurface(text);
    text = TTF_RenderUTF8_Blended(font,s.c_str(),szin);
    SDL_DestroyTexture(texttexture);
    texttexture =  SDL_CreateTextureFromSurface(renderer, text);
    rect = {x,y,w/3,h/3};   //only 3rd of size, the fonts are intentionally loaded in a size 3 times greater, so that they don't look blurry
    SDL_RenderCopy(renderer,texttexture,0,&rect);
    SDL_RenderPresent(renderer);
}

void NineMensMorrisBoard::clickOnPoint(int & point)
{
    SDL_Event event;
    while(SDL_WaitEvent(&event) && event.type != SDL_QUIT)
    {
        switch(event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_LEFT)
                for(point = 1; point < 25; point++)
                    if( (points[point - 1]->getCoordinates().x - event.button.x)*(points[point - 1]->getCoordinates().x - event.button.x) +
                            (points[point - 1]->getCoordinates().y - event.button.y)*(points[point - 1]->getCoordinates().y - event.button.y)  < 20*20 )
                        return;

            break;
        }
    }
}

void NineMensMorrisBoard::drawFrame(bool top)
{
    rect = {0,top ? 0 : BOARD_HEIGHT+FRAME_HEIGHT,FRAME_WIDTH,FRAME_HEIGHT};
    SDL_RenderCopy(renderer,top ? whitebackgroundtexture : blackbackgroundtexture,0,&rect);
    rect = {180,top ? 30 : 530,40,40};
    SDL_RenderCopy(renderer,top ? players[0]->getTexture() : players[1]->getTexture(),0,&rect);
    showText(helper::to_string(9 - (top ? numberofwhitepieces : numberofblackpieces)).c_str(),75,top ? 19 : 519,top ? WHITE_LETTER_COLOR : BLACK_LETTER_COLOR,numberfont);
    SDL_RenderPresent(renderer);
}

void NineMensMorrisBoard::drawRemoveFrame(bool top)
{
    rect = {0,top ? 0 : BOARD_HEIGHT+FRAME_HEIGHT,FRAME_WIDTH,FRAME_HEIGHT};
    SDL_RenderCopy(renderer,top ? whitebackgroundtexture : blackbackgroundtexture,0,&rect);
    showText(languageresourcemanager->getNineMensMorrisRemoveText1(),
             languageresourcemanager->getNineMensMorrisRemoveText1X(),
             current== 0 ? 0 : FRAME_HEIGHT + BOARD_HEIGHT,current==0 ? WHITE_LETTER_COLOR : BLACK_LETTER_COLOR,letterfont);
    showText(languageresourcemanager->getNineMensMorrisRemoveText2(),
             languageresourcemanager->getNineMensMorrisRemoveText2X(),
             current== 0 ? REMOVE_TEXT_SPACE : FRAME_HEIGHT + BOARD_HEIGHT + REMOVE_TEXT_SPACE ,current==0 ? WHITE_LETTER_COLOR : BLACK_LETTER_COLOR,letterfont);
    SDL_RenderPresent(renderer);
}

void NineMensMorrisBoard::drawBoard()
{
    rect = {0,FRAME_HEIGHT,BOARD_WIDTH,BOARD_WIDTH};
    SDL_RenderCopy(renderer,boardimagetexture,0,&rect);
    for(int i = 0; i < numberofpoints; i++)
    {
        if(points[i]->isOccupied())
            showImage(points[i]->getCoordinates(), points[i]->getPiece()->getOwner()->getTexture());
    }
    SDL_RenderPresent(renderer);
}

void NineMensMorrisBoard::setPoints()
{
    /*
    creating points array in dynamically allocated memory
    */
    points = new Point*[numberofpoints];
    for(int i = 0; i < numberofpoints ; i++)
        points[i] = new Point(i+1);

    /*
    setting coordinates for points
    */
    for(int i = 0; i < 3; i++)
        points[i]->setCoordinates({52 + 147*i, 151});
    for(int i = 0; i < 3; i++)
        points[i+3]->setCoordinates({101 + 98*i, 200});
    for(int i = 0; i < 3; i++)
        points[i+6]->setCoordinates({150 + 49*i, 249});
     for(int i = 0; i < 3; i++)
        points[i+9]->setCoordinates({52 + 49*i, 299});
    for(int i = 0; i < 3; i++)
        points[i+12]->setCoordinates({248 + 49*i ,299});
    for(int i = 0; i < 3; i++)
        points[i+15]->setCoordinates({150 + 49*i, 348});
    for(int i = 0; i < 3; i++)
        points[i+18]->setCoordinates({101 + 98*i, 397});
    for(int i = 0; i < 3; i++)
        points[i+21]->setCoordinates({52 + 147*i, 446});


    /*
    setting connections between points, using pointers
    */
    (*points[0])[0] = points[1]; (*points[0])[1] = points[9];
    (*points[1])[0] = points[0]; (*points[1])[1] = points[2];  (*points[1])[2] = points[4];
    (*points[2])[0] = points[1];  (*points[2])[1] = points[14];
    (*points[3])[0] = points[4]; (*points[3])[1] = points[10];
    (*points[4])[0] = points[1]; (*points[4])[1] = points[3];  (*points[4])[2] = points[5]; (*points[4])[3] = points[7];
    (*points[5])[0] = points[4];  (*points[5])[1] = points[13];
    (*points[6])[0] = points[7];  (*points[6])[1] = points[11];
    (*points[7])[0] = points[4]; (*points[7])[1] = points[6];  (*points[7])[2] = points[8];
    (*points[8])[0] = points[7];  (*points[8])[1] = points[12];
    (*points[9])[0] = points[0]; (*points[9])[1] = points[10];  (*points[9])[2] = points[21];
    (*points[10])[0] = points[3]; (*points[10])[1] = points[9];  (*points[10])[2] = points[11]; (*points[10])[3] = points[18];
    (*points[11])[0] = points[6]; (*points[11])[1] = points[10];  (*points[11])[2] = points[15];
    (*points[12])[0] = points[8]; (*points[12])[1] = points[13];  (*points[12])[2] = points[17];
    (*points[13])[0] = points[5]; (*points[13])[1] = points[12];  (*points[13])[2] = points[14]; (*points[13])[3] = points[20];
    (*points[14])[0] = points[2]; (*points[14])[1] = points[13];  (*points[14])[2] = points[23];
    (*points[15])[0] = points[11]; (*points[15])[1] = points[16];
    (*points[16])[0] = points[15]; (*points[16])[1] = points[17];  (*points[16])[2] = points[19];
    (*points[17])[0] = points[12]; (*points[17])[1] = points[16];
    (*points[18])[0] = points[10]; (*points[18])[1] = points[19];
    (*points[19])[0] = points[16]; (*points[19])[1] = points[18];  (*points[19])[2] = points[20]; (*points[19])[3] = points[22];
    (*points[20])[0] = points[13]; (*points[20])[1] = points[19];
    (*points[21])[0] = points[9];  (*points[21])[1] = points[22];
    (*points[22])[0] = points[19]; (*points[22])[1] = points[21];  (*points[22])[2] = points[23];
    (*points[23])[0] = points[14]; (*points[23])[1] = points[22];


    /*
    setting the points in the possible mills
    */
    mills[0][0] = 1; mills[0][1] = 2; mills[0][2] = 3;
    mills[1][0] = 4; mills[1][1] = 5; mills[1][2] = 6;
    mills[2][0] = 7; mills[2][1] = 8; mills[2][2] = 9;
    mills[3][0] = 10; mills[3][1] = 11; mills[3][2] = 12;
    mills[4][0] = 13; mills[4][1] = 14; mills[4][2] = 15;
    mills[5][0] = 16; mills[5][1] = 17; mills[5][2] = 18;
    mills[6][0] = 19; mills[6][1] = 20; mills[6][2] = 21;
    mills[7][0] = 22; mills[7][1] = 23; mills[7][2] = 24;
    mills[8][0] = 1; mills[8][1] = 10; mills[8][2] = 22;
    mills[9][0] = 4; mills[9][1] = 11; mills[9][2] = 19;
    mills[10][0] = 7; mills[10][1] = 12; mills[10][2] = 16;
    mills[11][0] = 2; mills[11][1] = 5; mills[11][2] = 8;
    mills[12][0] = 17; mills[12][1] = 20; mills[12][2] = 23;
    mills[13][0] = 9; mills[13][1] = 13; mills[13][2] = 18;
    mills[14][0] = 6; mills[14][1] = 14; mills[14][2] = 21;
    mills[15][0] = 3; mills[15][1] = 15; mills[15][2] = 24;


}

void NineMensMorrisBoard::checkEnd()
{
    int count1 = 0, count2 = 0;
    for(int i = 0; i < 9 ; i++)
    {
        if((*players[0])[i] != NULL) count1++; //1st player's piece
        if((*players[1])[i] != NULL) count2++; //2nd player's piece
    }
    if(count1 < 3 || count2 < 3)
    {
        showEnd(count2 < 3);
        over = true;
    }
}

bool NineMensMorrisBoard::anywhere(int player)
{
    int counter = 0;
    for(int i = 0; i < 9; i++)
        if((*players[player])[i] != NULL) counter++;
    return counter <= 3;
}

void NineMensMorrisBoard::mill(const Point* point)
{
    bool removable = false; //indicates whether the other player has a removable piece, e.g. that is not in a mill
    for(int i = 0; (i < (current==0 ? numberofblackpieces : numberofwhitepieces)) && !removable; i++)
                if((*players[current==0 ? 1 : 0])[i] != NULL && (*players[current==0 ? 1 : 0])[i]-> getPoint() != NULL
                  && checkMill((*players[current==0 ? 1 : 0])[i]->getPoint()) < 0) removable = true;
    if(checkMill(point) >= 0 && removable)
    {
        drawRemoveFrame(current==0);
        bool valid = false;
        while(!valid)
        {
            int toberemoved;
            clickOnPoint(toberemoved);
            if(points[toberemoved - 1]->isOccupied() &&  checkMill(points[toberemoved - 1]) < 0 && points[toberemoved - 1]->getPiece()->getOwner() == players[current==0 ? 1 : 0])
            {
                valid = true;
                for(int i = 0; i < (current==0 ? numberofblackpieces : numberofwhitepieces); i++)
                    if((*players[current==0 ? 1 : 0])[i] != NULL &&
                       (*players[current==0 ? 1 : 0])[i]->getPoint()->getId() == toberemoved)
                       (*players[current==0 ? 1 : 0])[i] = NULL;
                delete points[toberemoved - 1]->getPiece();
                points[toberemoved - 1]->setPiece(NULL);
                drawBoard();
            }
        }
    }
}

int NineMensMorrisBoard::checkMill(const Point * point)
{
    int player = (point->getPiece()->getOwner() == players[0]) ? 0 : 1;
    int id = point->getId();
    for(int i = 0; i < 16; i++)
        if(mills[i][0] == id || mills[i][1] == id || mills[i][2] == id)
        {
            int count = 0; //how many pieces belong to the owner of the given point in the mill possibility currently examined
            for(int j=0; j < 9; j++)
            {
                if((*players[player])[j] != NULL && (*players[player])[j]->getPoint() != NULL)
                {
                    int id2 = (*players[player])[j]->getPoint()->getId();
                    if(id2 == mills[i][0] || id2 == mills[i][1] || id2 == mills[i][2]) count++;
                }
            }
            if(count == 3) return i; //mill found, since all there points along a line have the pieces of the same player
        }
    return -1; //no mills
}

void NineMensMorrisBoard::firstPhase()
{
    bool valid = false;
    int point;
    while(!valid)
    {
        clickOnPoint(point);
        if(!points[point - 1]->isOccupied() )
        {
            showImage(points[point - 1]->getCoordinates(),players[current]->getTexture());
            valid = true;
            points[point - 1]->setPiece((*players[current])[current==0 ? numberofwhitepieces : numberofblackpieces]);
            (*players[current])[current==0 ? numberofwhitepieces : numberofblackpieces]->setPoint(points[point - 1]);
            current==0 ? numberofwhitepieces++ : numberofblackpieces++;
            if(numberofblackpieces == 9) firstphase = false;
            mill(points[point - 1]);
            drawFrame(current==0);
        }

    }
}

void NineMensMorrisBoard::secondPhase()
{
    bool valid = false;
    int point1, point2;
    while(!valid)
    {
        drawBoard();
        Piece * movable[9];
        int numberofmovables = 0;
        bool anywherebool = anywhere(current);
        if(!anywherebool)
        {
            for(int i = 0; i < 9; i++)
                if( (*players[current])[i] != NULL && ( !((*(*players[current])[i]->getPoint())[0]->isOccupied()) ||
                !((*(*players[current])[i]->getPoint())[1]->isOccupied()) ||
                ( (*(*players[current])[i]->getPoint())[2] != NULL && !((*(*players[current])[i]->getPoint())[2]->isOccupied()) ) ||
                ( (*(*players[current])[i]->getPoint())[3] != NULL && !((*(*players[current])[i]->getPoint())[3]->isOccupied()) ) ) )
                    movable[numberofmovables++] = (*players[current])[i];
            if(numberofmovables == 0)
            {
                showEnd(current==1);
                over = true;
                return;
            }
        }
        else
        {
            for(int i = 0; i < 9; i++)
                if( (*players[current])[i] != NULL )
                    movable[numberofmovables++] = (*players[current])[i];
        }

        clickOnPoint(point1);
        if(points[point1 - 1]->getPiece() != NULL && find(movable, movable + 9, points[point1 - 1]->getPiece()) != movable + 9)
        {

            while(!valid)
            {
                selectPoint(point1);
                Piece * mozgo = points[point1 - 1]->getPiece();
                clickOnPoint(point2);
                if(!points[point2 - 1]->isOccupied() &&
                    (anywherebool || (*points[point2 - 1])[0] == points[point1 - 1] || (*points[point2 - 1])[1] == points[point1 - 1] ||
                     (*points[point2 - 1])[2] == points[point1 - 1] || (*points[point2 - 1])[3] == points[point1 - 1]) )
                {
                    valid = true;
                    points[point2 - 1]->setPiece(mozgo);
                    mozgo->setPoint(points[point2 - 1]);
                    points[point1 - 1]->setPiece(NULL);
                }
                else if(points[point2 - 1]->getPiece() != NULL && find(movable, movable + 9, points[point2 - 1]->getPiece()) != movable + 9)
                {
                    point1 = point2;
                    drawBoard();
                }
            }
        }
    }
    drawBoard();
    mill(points[point2 - 1]);
    drawFrame(current==0);
}

void NineMensMorrisBoard::showImage(SDL_Point position,SDL_Texture* image)
{
    rect = {position.x - PIECE_SIDE/2,position.y - PIECE_SIDE/2,PIECE_SIDE,PIECE_SIDE};
    SDL_RenderCopy(renderer,image,0,&rect);
}

NineMensMorrisBoard::NineMensMorrisBoard(LanguageResourceManager* languageresourcemanager)
{
    this->languageresourcemanager = languageresourcemanager;
    numberofplayers = 2;
    numberofpoints = 24;
    current = 1;    //the current player changes BEFORE every move => we need to set it to last player here (only 2 players in this game)
    firstphase = true;  //the game start with the first phase
    over = false;
    numberofwhitepieces = 0;
    numberofblackpieces = 0;
    setPoints();
    initGraphics();
    players[0] = new Player(languageresourcemanager->getWhiteName(),9,0, "resources/images/white.png",renderer);
    players[1] = new Player(languageresourcemanager->getBlackName(),9,0, "resources/images/black.png", renderer);
    drawBoard();
    //draw both the top and the bottom frame
    drawFrame(true);
    drawFrame(false);
}

void NineMensMorrisBoard::play()
{
    while(!over)
    {
        current = current == 0 ? 1 : 0;
        drawFrame(current==0);
        if(current == 0)
        {
            showText(languageresourcemanager->getWhiteName(),languageresourcemanager->getNineMensMorrisWhiteX(),2,WHITE_LETTER_COLOR,letterfont);
            showText(languageresourcemanager->getNineMensMorrisToMoveText(),languageresourcemanager->getNineMensMorrisToMoveTextX(),42,WHITE_LETTER_COLOR,letterfont);
        }
        else
        {
            showText(languageresourcemanager->getBlackName(),languageresourcemanager->getNineMensMorrisBlackX(),502,BLACK_LETTER_COLOR,letterfont);
            showText(languageresourcemanager->getNineMensMorrisToMoveText(),languageresourcemanager->getNineMensMorrisToMoveTextX(),542,BLACK_LETTER_COLOR,letterfont);
        }
        firstphase ? firstPhase() : secondPhase();
        checkEnd();
    }
}

void NineMensMorrisBoard::initGraphics()
{
    if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) )
    {
        std::cerr << languageresourcemanager->getIMGErrorText() << IMG_GetError();
        return;
    }
    if(TTF_Init() == -1 )
    {
        std::cerr << languageresourcemanager->getTTFErrorText() << TTF_GetError();
        return;
    }

    letterfont = TTF_OpenFont("resources/fonts/Garamond Classico SC.ttf", 160);
    if (!letterfont)  std::cerr << languageresourcemanager->getFontErrorText() << SDL_GetError() << std::endl;
    numberfont = TTF_OpenFont("resources/fonts/times.ttf", 160);
    if (!numberfont)  std::cerr << languageresourcemanager->getFontErrorText() << SDL_GetError() << std::endl;

    boardimage = IMG_Load("resources/images/ninemensmorrisboard.png");
    if(boardimage == NULL)
    {
        std::cerr << languageresourcemanager->getImageErrorText() << SDL_GetError();
        return;
    }

    whitebackground = IMG_Load("resources/images/whitebackground.jpg");
    if(whitebackground == NULL)
    {
        std::cerr << languageresourcemanager->getImageErrorText() << SDL_GetError();
        return;
    }
    blackbackground = IMG_Load("resources/images/blackbackground.jpg");
    if(blackbackground == NULL)
    {
        std::cerr << languageresourcemanager->getImageErrorText() << SDL_GetError();
        return;
    }
    endbackground = IMG_Load("resources/images/endbackground.png");
    if(endbackground == NULL)
    {
        std::cerr << languageresourcemanager->getImageErrorText() << SDL_GetError();
        return;
    }
    cup = IMG_Load("resources/images/cup.png");
    if(cup == NULL)
    {
        std::cerr << languageresourcemanager->getImageErrorText() << SDL_GetError();
        return;
    }
    button = IMG_Load("resources/images/endbutton.png");
    if(button == NULL)
    {
        std::cerr << languageresourcemanager->getImageErrorText() << SDL_GetError();
        return;
    }

    window = SDL_CreateWindow( languageresourcemanager->getNineMensMorrisWindowTitle().c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
        std::cerr <<  languageresourcemanager->getImageErrorText() <<  SDL_GetError() << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    boardimagetexture = SDL_CreateTextureFromSurface(renderer, boardimage);
    whitebackgroundtexture = SDL_CreateTextureFromSurface(renderer, whitebackground);
    blackbackgroundtexture = SDL_CreateTextureFromSurface(renderer, blackbackground);
    endbackgroundtexture = SDL_CreateTextureFromSurface(renderer, endbackground);
    cuptexture = SDL_CreateTextureFromSurface(renderer, cup);
    buttontexture = SDL_CreateTextureFromSurface(renderer, button);
}

void NineMensMorrisBoard::showEnd(bool white)
{
    rect = {0,0,WINDOW_WIDTH,WINDOW_HEIGHT};
    SDL_RenderCopy(renderer,endbackgroundtexture,0,&rect); //loading the background of the end screen
    rect = {150,60,100,100};
    SDL_RenderCopy(renderer,cuptexture,0,&rect);  //loading the cup on the end screen
    showText(players[white ? 0 : 1]->getName(),
             white ? languageresourcemanager->getNineMensMorrisEndScreenWhiteX() : languageresourcemanager->getNineMensMorrisEndScreenBlackX(),
             END_TEXT_Y,BLACK_LETTER_COLOR,letterfont);
    showText(languageresourcemanager->getNineMensMorrisEndScreenText1(),
             languageresourcemanager->getNineMensMorrisEndScreenText1X(),
             END_TEXT_Y + END_TEXT_SPACE,BLACK_LETTER_COLOR,letterfont);
    showText(languageresourcemanager->getNineMensMorrisEndScreenText2(),
             languageresourcemanager->getNineMensMorrisEndScreenText2X(),
             END_TEXT_Y + 2*END_TEXT_SPACE,BLACK_LETTER_COLOR,letterfont);
    rect = {(WINDOW_WIDTH-END_BUTTON_WIDTH)/2,END_BUTTON_Y,END_BUTTON_WIDTH,END_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer,buttontexture,0,&rect); //loading end button
    SDL_RenderPresent(renderer);
    SDL_Event event;
    while(SDL_WaitEvent(&event) && event.type != SDL_QUIT)
    {
        switch(event.type)
        {
        case SDL_MOUSEBUTTONDOWN: //mouse click
            if(event.button.button == SDL_BUTTON_LEFT) //with left button
            {
                int x = event.button.x - (WINDOW_WIDTH-END_BUTTON_WIDTH)/2;
                int y = event.button.y - END_BUTTON_Y;
                if(x > 0 && x < END_BUTTON_WIDTH && y > 0 && y < END_BUTTON_HEIGHT
                   && !(x+y<7 || (END_BUTTON_WIDTH - x) + y < 7 || x + (END_BUTTON_HEIGHT - y) < 7 ||  (END_BUTTON_WIDTH - x) + (END_BUTTON_HEIGHT - y) < 7) )    //corners
                        return;
            }
            break;
        }
    }
}

NineMensMorrisBoard::~NineMensMorrisBoard()
{
    TTF_CloseFont(letterfont);
    TTF_CloseFont(numberfont);
    SDL_FreeSurface(boardimage);
    SDL_FreeSurface(whitebackground);
    SDL_FreeSurface(blackbackground);
    SDL_FreeSurface(endbackground);
    SDL_FreeSurface(cup);
    SDL_FreeSurface(button);
    SDL_FreeSurface(text);
    SDL_DestroyTexture(boardimagetexture);
    SDL_DestroyTexture(whitebackgroundtexture);
    SDL_DestroyTexture(blackbackgroundtexture);
    SDL_DestroyTexture(endbackgroundtexture);
    SDL_DestroyTexture(cuptexture);
    SDL_DestroyTexture(buttontexture);
    SDL_DestroyTexture(texttexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow( window );
    TTF_Quit();
    IMG_Quit();
}
