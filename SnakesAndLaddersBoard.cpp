#include <cstdlib>
#include <iostream>
#include <ctime>
#include <sstream>
#include "snakesandladdersboard.h"
#include "Helper.h"


int SnakesAndLaddersBoard::click(int& x, int& y) {
    SDL_PumpEvents();
    SDL_FlushEvents(0, SDL_LASTEVENT);   //clear all previous events
    SDL_Event event;
    while (SDL_WaitEvent(&event) && event.type != SDL_QUIT) {
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN: //mouse click
                if (event.button.button == SDL_BUTTON_LEFT) //with left button
                {
                    x = event.button.x;
                    y = event.button.y;
                    return 1;
                }
                break;
            default:
                break;
        }

    }
    return 0;
}

void SnakesAndLaddersBoard::roll(int number) {
    int x, y;
    //waiting for a click on the roll button
    while (click(x, y)) {
        if ((ROLL_BUTTON_X + (double) ROLL_BUTTON_DIAMETER / 2 - x) *
            (ROLL_BUTTON_X + (double) ROLL_BUTTON_DIAMETER / 2 - x) +
            (ROLL_BUTTON_Y + (double) ROLL_BUTTON_DIAMETER / 2 - y) *
            (ROLL_BUTTON_Y + (double) ROLL_BUTTON_DIAMETER / 2 - y) <
            ((double) ROLL_BUTTON_DIAMETER / 2) * ((double) ROLL_BUTTON_DIAMETER / 2)) {
            rollAnimation(number);
            SDL_Delay(300); //wait for a short time, so that the user can
            drawRoll();
            break; //roll is complete
        }
    }
}

void SnakesAndLaddersBoard::pieceOnPoint(const Point* point, int jatekos) {
    rect = {point->getCoordinates().x + 1 + (jatekos % 3) * 21, point->getCoordinates().y + 1 + (jatekos / 3) * 33,
            PIECE_WIDTH, PIECE_HEIGHT};
    SDL_RenderCopy(renderer, players[jatekos]->getTexture(), nullptr, &rect);
}

void SnakesAndLaddersBoard::drawEmptyBoard() {
    /*
    displaying the background for each square
    */
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            int szam = 91 + j - i * 10;
            rect = {points[szam - 1]->getCoordinates().x, points[szam - 1]->getCoordinates().y, SQUARE_SIDE,
                    SQUARE_SIDE};
            switch ((i + j) % 4) {
                case 0:
                    SDL_RenderCopy(renderer, lightsquaretexture, nullptr, &rect);
                    break;
                case 1:
                    SDL_RenderCopy(renderer, darksquaretexture, nullptr, &rect);
                    break;
                case 2:
                    SDL_RenderCopy(renderer, lightsquare2texture, nullptr, &rect);
                    break;
                case 3:
                    SDL_RenderCopy(renderer, darksquare2texture, nullptr, &rect);
                    break;
                default:
                    break;
            }

        }
    }

    /*
    loading other elements of the board - frame, snakes, ladders
    */
    rect = {0, 0, BOARD_WIDTH, BOARD_HEIGHT};
    SDL_RenderCopy(renderer, boardimagetexture, nullptr, &rect);

    /*
    the numbers are missing from every 4th square - we have to draw them
    in a new cycle, as they have to be atop everything else, so as to be visible
    */
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            int szam = 91 + j - i * 10;
            rect = {points[szam - 1]->getCoordinates().x, points[szam - 1]->getCoordinates().y, SQUARE_SIDE,
                    SQUARE_SIDE};
            switch ((i + j) % 4) {
                case 3:
                    int w, h;
                    TTF_SizeUTF8(numberfont, helper::to_string(szam).c_str(), &w, &h);
                    SDL_FreeSurface(number);
                    number = TTF_RenderUTF8_Blended(numberfont, helper::to_string(szam).c_str(), TEXT_COLOR);
                    SDL_DestroyTexture(numbertexture);
                    numbertexture = SDL_CreateTextureFromSurface(renderer, number);
                    rect = {rect.x + (szam > 9 ? 30 : 47), rect.y - 4, w / 5, h / 5};
                    SDL_RenderCopy(renderer, numbertexture, nullptr, &rect);
                    break;
                default:
                    break;
            }
        }
    }
}

void SnakesAndLaddersBoard::drawBoard() {
    drawEmptyBoard();
    for (int i = 0; i < numberofplayers; i++)
        pieceOnPoint((*players[i])[0]->getPoint(), i);
    SDL_RenderPresent(renderer);
}

void SnakesAndLaddersBoard::turn() {
    int rolled = rand() % 6 + 1;    //randomize the rolled number
    roll(rolled);     //graphical part of the roll

    Point* move;   //the point on which the player's piece is after the roll (it can be the starting point of a snake or a ladder)
    int currentid = (*players[current])[0]->getPoint()->getId();
    if (rolled + currentid > 100) move = points[99 - (rolled - (100 - currentid))];     //went over the last square
    else move = points[currentid - 1 + rolled];   //did not go over it
    if (move->getId() == numberofpoints ||
        (*move)[0] == points[move->getId()])  //moved to the last square or to a normal square
    {
        (*players[current])[0]->setPoint(move);
    } else //it is a special square - ladder or snake starts here
    {
        (*players[current])[0]->setPoint((*move)[0]);
    }
    drawBoard();
}

void SnakesAndLaddersBoard::showText(const string s, int x, int y, SDL_Color szin, TTF_Font* font) {
    int w, h;
    TTF_SizeUTF8(font, s.c_str(), &w, &h);
    SDL_FreeSurface(number);
    number = TTF_RenderUTF8_Blended(font, s.c_str(), szin);
    SDL_DestroyTexture(numbertexture);
    numbertexture = SDL_CreateTextureFromSurface(renderer, number);
    rect = {x, y, w / 3, h /
                         3};   //only 3rd of size, the fonts are intentionally loaded in a size 3 times greater, so that they don't look blurry
    SDL_RenderCopy(renderer, numbertexture, nullptr, &rect);
}

void SnakesAndLaddersBoard::drawRoll() {
    rect = {BOARD_WIDTH, 0, WINDOW_WIDTH - BOARD_WIDTH, WINDOW_HEIGHT};
    SDL_RenderCopy(renderer, backgroundtexture, nullptr, &rect);         //loading background
    rect = {ROLL_BUTTON_X, ROLL_BUTTON_Y, ROLL_BUTTON_DIAMETER, ROLL_BUTTON_DIAMETER};
    SDL_RenderCopy(renderer, rollbuttontexture, nullptr, &rect);         //loading roll button
    rect = {ROLL_IMAGE_X, ROLL_IMAGE_Y, ROLL_IMAGE_WIDTH, ROLL_IMAGE_HEIGHT};
    SDL_RenderCopy(renderer, greenbackgroundtexture, nullptr, &rect);    //loading green background
    rect = {BOARD_WIDTH + (WINDOW_WIDTH - BOARD_WIDTH - DICE_SHAKER_WIDTH) / 2, 0, DICE_SHAKER_WIDTH,
            DICE_SHAKER_HEIGHT};
    SDL_RenderCopyEx(renderer, diceshakertexture, nullptr, &rect, 0, nullptr, SDL_FLIP_VERTICAL);  //loading dice shaker
    SDL_RenderPresent(renderer);
}

void SnakesAndLaddersBoard::drawSelection(int current) {
    rect = {BOARD_WIDTH, 0, WINDOW_WIDTH - BOARD_WIDTH, WINDOW_HEIGHT};
    SDL_RenderCopy(renderer, backgroundtexture, nullptr, &rect);     //displaying background
    showText(languageresourcemanager->getSnakesAndLaddersSelectionScreenText1(),
             languageresourcemanager->getSnakesAndLaddersSelectionScreenText1X(), SELECTION_TEXT_Y, TEXT_COLOR,
             letterfont);
    showText(languageresourcemanager->getSnakesAndLaddersSelectionScreenText2(),
             languageresourcemanager->getSnakesAndLaddersSelectionScreenText2X(),
             SELECTION_TEXT_Y + SELECTION_TEXT_SPACE, TEXT_COLOR, letterfont);
    showText(languageresourcemanager->getSnakesAndLaddersSelectionScreenText3(),
             languageresourcemanager->getSnakesAndLaddersSelectionScreenText3X(),
             SELECTION_TEXT_Y + 2 * SELECTION_TEXT_SPACE, TEXT_COLOR,
             letterfont);  //showing the question about the number of players
    rect = {INCREMENT_BUTTON_X, INCREMENT_BUTTON_Y, INCREMENT_BUTTON_WIDTH, INCREMENT_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, incrementbuttontexture, nullptr, &rect);     //displaying increment button
    showText(helper::to_string(current), NUMBER_OF_PLAYERS_X, NUMBER_OF_PLAYERS_Y, TEXT_COLOR,
             letterfont);   //showing the currently selected number of players
    rect = {INCREMENT_BUTTON_X, DECREMENT_BUTTON_Y, INCREMENT_BUTTON_WIDTH, INCREMENT_BUTTON_HEIGHT};
    SDL_RenderCopyEx(renderer, incrementbuttontexture, nullptr, &rect, 0, nullptr,
                     SDL_FLIP_VERTICAL); //displaying decrement button, using a vertical flip
    rect = {START_BUTTON_X, START_BUTTON_Y, START_BUTTON_WIDTH, START_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, buttontexture, nullptr, &rect);       //displaying start button
    SDL_RenderPresent(renderer);
}

int SnakesAndLaddersBoard::selectNumberOfPlayers() {
    int temp = 2, x, y;
    drawSelection(temp);
    while (click(x, y)) {
        //number of players is selected - start button
        if (x > START_BUTTON_X && x < START_BUTTON_X + START_BUTTON_WIDTH && y > START_BUTTON_Y &&
            y < START_BUTTON_Y + START_BUTTON_HEIGHT
            && !(x - START_BUTTON_X + y - START_BUTTON_Y < 6 ||
                 std::abs(x - START_BUTTON_X - START_BUTTON_WIDTH) + y - START_BUTTON_Y < 6
                 || x - START_BUTTON_X + std::abs(y - START_BUTTON_Y - START_BUTTON_HEIGHT) < 6 ||
                 std::abs(x - START_BUTTON_X - START_BUTTON_WIDTH) +
                 std::abs(y - START_BUTTON_Y - START_BUTTON_HEIGHT) < 6))
            break;
        //increment button
        if (x > INCREMENT_BUTTON_X && x < INCREMENT_BUTTON_X + INCREMENT_BUTTON_WIDTH && y > INCREMENT_BUTTON_Y &&
            y < INCREMENT_BUTTON_Y + INCREMENT_BUTTON_HEIGHT &&
            ((x - INCREMENT_BUTTON_X < (double) INCREMENT_BUTTON_WIDTH / 2 && y - INCREMENT_BUTTON_Y >
                                                                              INCREMENT_BUTTON_HEIGHT -
                                                                              (double) INCREMENT_BUTTON_HEIGHT /
                                                                              INCREMENT_BUTTON_WIDTH *
                                                                              (x - INCREMENT_BUTTON_X) * 2)
             || (x - INCREMENT_BUTTON_X > (double) INCREMENT_BUTTON_WIDTH / 2 && y - INCREMENT_BUTTON_Y >
                                                                                 (double) INCREMENT_BUTTON_HEIGHT /
                                                                                 INCREMENT_BUTTON_WIDTH *
                                                                                 (x - INCREMENT_BUTTON_X) * 2 -
                                                                                 INCREMENT_BUTTON_HEIGHT)) && temp < 6)
            drawSelection(++temp);
        //decrement button
        if (x > INCREMENT_BUTTON_X && x < INCREMENT_BUTTON_X + INCREMENT_BUTTON_WIDTH && y > DECREMENT_BUTTON_Y &&
            y < DECREMENT_BUTTON_Y + INCREMENT_BUTTON_HEIGHT &&
            ((x - INCREMENT_BUTTON_X < (double) INCREMENT_BUTTON_WIDTH / 2 && y - DECREMENT_BUTTON_Y <
                                                                              (double) INCREMENT_BUTTON_HEIGHT /
                                                                              INCREMENT_BUTTON_WIDTH *
                                                                              (x - INCREMENT_BUTTON_X) * 2)
             || (x - INCREMENT_BUTTON_X > (double) INCREMENT_BUTTON_WIDTH / 2 && y - DECREMENT_BUTTON_Y <
                                                                                 INCREMENT_BUTTON_HEIGHT -
                                                                                 (double) INCREMENT_BUTTON_HEIGHT /
                                                                                 INCREMENT_BUTTON_WIDTH *
                                                                                 (x - INCREMENT_BUTTON_X -
                                                                                  (double) INCREMENT_BUTTON_WIDTH / 2) *
                                                                                 2)) && temp > 1)
            drawSelection(--temp);
    }
    return temp;
}

void SnakesAndLaddersBoard::initGraphics() {
    window = SDL_CreateWindow(languageresourcemanager->getSnakesAndLaddersWindowTitle().c_str(),
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << languageresourcemanager->getWindowErrorText() << SDL_GetError() << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (TTF_Init() == -1) {
        std::cerr << languageresourcemanager->getTTFErrorText() << TTF_GetError();
        return;
    }
    numberfont = TTF_OpenFont("resources/fonts/segoe-print.ttf", 115);
    if (!numberfont) std::cerr << languageresourcemanager->getFontErrorText() << SDL_GetError() << std::endl;
    letterfont = TTF_OpenFont("resources/fonts/segoe-print-bold.ttf", 115);
    if (!letterfont) std::cerr << languageresourcemanager->getFontErrorText() << SDL_GetError() << std::endl;


    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << languageresourcemanager->getIMGErrorText() << IMG_GetError();
        return;
    }

    boardimage = IMG_Load("resources/images/snakesandladders.png");
    if (boardimage == nullptr) {
        std::cerr << languageresourcemanager->getImageErrorText() << SDL_GetError();
        return;
    }
    boardimagetexture = SDL_CreateTextureFromSurface(renderer, boardimage);

    lightsquare = IMG_Load("resources/images/lightsquare.png");
    if (lightsquare == nullptr) {
        std::cerr << languageresourcemanager->getImageErrorText() << SDL_GetError();
        return;
    }
    lightsquaretexture = SDL_CreateTextureFromSurface(renderer, lightsquare);

    lightsquare2 = IMG_Load("resources/images/lightsquare2.png");
    if (lightsquare2 == nullptr) {
        std::cerr << languageresourcemanager->getImageErrorText() << SDL_GetError();
        return;
    }
    lightsquare2texture = SDL_CreateTextureFromSurface(renderer, lightsquare2);

    darksquare = IMG_Load("resources/images/darksquare.png");
    if (darksquare == nullptr) {
        std::cerr << languageresourcemanager->getImageErrorText() << SDL_GetError();
        return;
    }
    darksquaretexture = SDL_CreateTextureFromSurface(renderer, darksquare);

    darksquare2 = IMG_Load("resources/images/darksquare2.png");
    if (darksquare2 == nullptr) {
        std::cerr << languageresourcemanager->getImageErrorText() << SDL_GetError();
        return;
    }
    darksquare2texture = SDL_CreateTextureFromSurface(renderer, darksquare2);

    background = IMG_Load("resources/images/salbackground.png");
    if (background == nullptr) {
        std::cerr << languageresourcemanager->getImageErrorText() << SDL_GetError();
        return;
    }
    backgroundtexture = SDL_CreateTextureFromSurface(renderer, background);

    incrementbutton = IMG_Load("resources/images/incrementbutton.png");
    if (incrementbutton == nullptr) {
        std::cerr << languageresourcemanager->getImageErrorText() << SDL_GetError();
        return;
    }
    incrementbuttontexture = SDL_CreateTextureFromSurface(renderer, incrementbutton);

    button = IMG_Load("resources/images/salbutton.png");
    if (button == nullptr) {
        std::cerr << languageresourcemanager->getImageErrorText() << SDL_GetError();
        return;
    }
    buttontexture = SDL_CreateTextureFromSurface(renderer, button);

    rollbutton = IMG_Load(languageresourcemanager->getRollButtonFileName().c_str());
    if (rollbutton == nullptr) {
        std::cerr << languageresourcemanager->getImageErrorText() << SDL_GetError();
        return;
    }
    rollbuttontexture = SDL_CreateTextureFromSurface(renderer, rollbutton);

    endbackground = IMG_Load("resources/images/salendbackground.png");
    if (endbackground == nullptr) {
        std::cerr << languageresourcemanager->getImageErrorText() << SDL_GetError();
        return;
    }
    endbackgroundtexture = SDL_CreateTextureFromSurface(renderer, endbackground);

    endbutton = IMG_Load("resources/images/endbutton.png");
    if (endbutton == nullptr) {
        std::cerr << languageresourcemanager->getImageErrorText() << SDL_GetError();
        return;
    }
    endbuttontexture = SDL_CreateTextureFromSurface(renderer, endbutton);

    wreath = IMG_Load("resources/images/wreath.png");
    if (wreath == nullptr) {
        std::cerr << languageresourcemanager->getImageErrorText() << SDL_GetError();
        return;
    }
    wreathtexture = SDL_CreateTextureFromSurface(renderer, wreath);

    diceshaker = IMG_Load("resources/images/diceshaker.png");
    if (diceshaker == nullptr) {
        std::cerr << languageresourcemanager->getImageErrorText() << SDL_GetError();
        return;
    }
    diceshakertexture = SDL_CreateTextureFromSurface(renderer, diceshaker);

    greenbackground = IMG_Load("resources/images/greenbackground.png");
    if (greenbackground == nullptr) {
        std::cerr << languageresourcemanager->getImageErrorText() << SDL_GetError();
        return;
    }
    greenbackgroundtexture = SDL_CreateTextureFromSurface(renderer, greenbackground);

    //setting the coordinates of points
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            points[90 + j - i * 10]->setCoordinates({4 + 70 * j, 4 + 70 * i});
}

void SnakesAndLaddersBoard::showEnd(int winner) {
    rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_RenderCopy(renderer, endbackgroundtexture, nullptr, &rect); //loading the background of the end screen
    rect = {WINDOW_WIDTH / 2 - WREATH_WIDTH / 2, WREATH_Y, WREATH_WIDTH, WREATH_HEIGHT};
    SDL_RenderCopy(renderer, wreathtexture, nullptr, &rect);        //loading the wreath around the piece
    rect = {WINDOW_WIDTH / 2 - END_PIECE_WIDTH / 2, END_PIECE_Y, END_PIECE_WIDTH, END_PIECE_HEIGHT};
    SDL_RenderCopy(renderer, players[winner]->getTexture(), nullptr,
                   &rect);  //loading the piece for the end screen (its size is different than while on the board)
    showText(players[winner]->getName(), languageresourcemanager->getSnakesAndLaddersPlayerNameX(winner), END_TEXT_Y,
             TEXT_COLOR, letterfont);
    showText(languageresourcemanager->getSnakesAndLaddersEndScreenText1(),
             languageresourcemanager->getSnakesAndLaddersEndScreenText1X(), END_TEXT_Y + END_TEXT_SPACE, TEXT_COLOR,
             letterfont);
    showText(languageresourcemanager->getSnakesAndLaddersEndScreenText2(),
             languageresourcemanager->getSnakesAndLaddersEndScreenText2X(), END_TEXT_Y + 2 * END_TEXT_SPACE, TEXT_COLOR,
             letterfont);
    rect = {WINDOW_WIDTH / 2 - END_BUTTON_WIDTH / 2, END_BUTTON_Y, END_BUTTON_WIDTH, END_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, endbuttontexture, nullptr, &rect);
    SDL_RenderPresent(renderer);


    int x, y;
    //waiting for a click on the OK button
    while (click(x, y)) {
        x = x - WINDOW_WIDTH / 2 + END_BUTTON_WIDTH / 2;    //x coordinate inside the button
        y = y - END_BUTTON_Y;                            //y coordinate inside the button
        if (x > 0 && x < END_BUTTON_WIDTH && y > 0 && y < END_BUTTON_HEIGHT
            && !(x + y < 7 || (END_BUTTON_WIDTH - x) + y < 7 || x + (END_BUTTON_HEIGHT - y) < 7 ||
                 (END_BUTTON_WIDTH - x) + (END_BUTTON_HEIGHT - y) < 7))    //corners
            break; //click on the button
    }
}

void SnakesAndLaddersBoard::setPoints(int size, const char* connections) {
    numberofpoints = size;
    points = new Point* [numberofpoints];
    for (int i = 0; i < numberofpoints; i++) {
        points[i] = new Point(i + 1);
    }
    for (int i = 0; i < numberofpoints - 1; i++) {
        (*points[i])[0] = points[i +
                                 1];        //by default, the point with an id greater by one comes after every point
    }
    (*points[numberofpoints - 1])[0] = nullptr;
    std::stringstream ss;
    int a, b;   // the ids of the points between which there is a snake or a ladder
    ss << connections;
    while (ss >> a) {
        ss.ignore(1);
        ss >> b;
        ss.ignore(1);
        (*points[a - 1])[0] = points[b - 1];
    }
}

SnakesAndLaddersBoard::SnakesAndLaddersBoard(LanguageResourceManager* languageresourcemanager, int meret,
                                             const char* connections) {
    this->languageresourcemanager = languageresourcemanager;
    setPoints(meret, connections);   //setting points
    srand(time(0));     //initialization of random number generator
    initGraphics();    //loading graphical interface
    drawEmptyBoard();  //drawing an empty board - number of players no yet selected
    SDL_RenderPresent(renderer);

    numberofplayers = selectNumberOfPlayers();
    switch (numberofplayers) {
        case 6:
            players[5] = new Player(languageresourcemanager->getGreenName(), 1, points[0],
                                    "resources/images/greenpiece.png", renderer);
        case 5:
            players[4] = new Player(languageresourcemanager->getRedName(), 1, points[0],
                                    "resources/images/redpiece.png", renderer);
        case 4:
            players[3] = new Player(languageresourcemanager->getPinkName(), 1, points[0],
                                    "resources/images/pinkpiece.png", renderer);
        case 3:
            players[2] = new Player(languageresourcemanager->getBlueName(), 1, points[0],
                                    "resources/images/bluepiece.png", renderer);
        case 2:
            players[1] = new Player(languageresourcemanager->getWhiteName(), 1, points[0],
                                    "resources/images/whitepiece.png", renderer);
        case 1:
            players[0] = new Player(languageresourcemanager->getBlackName(), 1, points[0],
                                    "resources/images/blackpiece.png", renderer);
            break;
        default:
            break;
    }
    current =
            numberofplayers - 1; //the current player changes BEFORE every move => we need to set it to last player here
    drawRoll();   //displaying roll interface
    drawBoard();  //displaying board, now with pieces
}

void SnakesAndLaddersBoard::play() {
    while ((*players[current])[0]->getPoint()->getId() != numberofpoints) {
        current = current == numberofplayers - 1 ? 0 : current + 1;
        turn();
    }
    showEnd(current); //the game is over, the current player reached the last square
}

void SnakesAndLaddersBoard::rollAnimation(int roll) {
    std::stringstream name;
    for (int i = 3; i < 17; i++) {
        name << "resources/animation/" << i - 2 << ".png";
        rollimage = IMG_Load(name.str().c_str());
        name.str("");
        if (rollimage == nullptr) {
            std::cout << languageresourcemanager->getImageErrorText() << SDL_GetError();
            return;
        }
        rollimagetexture = SDL_CreateTextureFromSurface(renderer, rollimage);
        SDL_Delay(ANIMATION_DELAY);
        rect = {ROLL_IMAGE_X, ROLL_IMAGE_Y, ROLL_IMAGE_WIDTH, ROLL_IMAGE_HEIGHT};
        SDL_RenderCopy(renderer, rollimagetexture, nullptr, &rect);
        rect = {DICE_SHAKER_X, 0, DICE_SHAKER_WIDTH, DICE_SHAKER_HEIGHT};
        SDL_RenderCopyEx(renderer, diceshakertexture, nullptr, &rect, 0, nullptr, SDL_FLIP_VERTICAL);
        SDL_RenderPresent(renderer);
        SDL_FreeSurface(rollimage);
        SDL_DestroyTexture(rollimagetexture);
    }
    for (int i = 0; i < 3; i++) {
        name << "resources/animation/" << i + 15 << "-" << roll << ".png";
        rollimage = IMG_Load(name.str().c_str());
        name.str("");
        if (rollimage == nullptr) {
            std::cout << languageresourcemanager->getImageErrorText() << SDL_GetError();
            return;
        }
        rollimagetexture = SDL_CreateTextureFromSurface(renderer, rollimage);
        SDL_Delay(ANIMATION_DELAY);
        rect = {ROLL_IMAGE_X, ROLL_IMAGE_Y, ROLL_IMAGE_WIDTH, ROLL_IMAGE_HEIGHT};
        SDL_RenderCopy(renderer, rollimagetexture, nullptr, &rect);
        rect = {DICE_SHAKER_X, 0, DICE_SHAKER_WIDTH, DICE_SHAKER_HEIGHT};
        SDL_RenderCopyEx(renderer, diceshakertexture, nullptr, &rect, 0, nullptr, SDL_FLIP_VERTICAL);
        SDL_RenderPresent(renderer);
        SDL_FreeSurface(rollimage);
        SDL_DestroyTexture(rollimagetexture);
    }
}

SnakesAndLaddersBoard::~SnakesAndLaddersBoard() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(boardimage);
    SDL_DestroyTexture(boardimagetexture);
    SDL_FreeSurface(lightsquare);
    SDL_DestroyTexture(lightsquaretexture);
    SDL_FreeSurface(lightsquare2);
    SDL_DestroyTexture(lightsquare2texture);
    SDL_FreeSurface(darksquare);
    SDL_DestroyTexture(darksquaretexture);
    SDL_FreeSurface(darksquare2);
    SDL_DestroyTexture(darksquare2texture);
    SDL_FreeSurface(background);
    SDL_DestroyTexture(backgroundtexture);
    SDL_FreeSurface(incrementbutton);
    SDL_DestroyTexture(incrementbuttontexture);
    SDL_FreeSurface(button);
    SDL_DestroyTexture(buttontexture);
    SDL_FreeSurface(endbutton);
    SDL_DestroyTexture(endbuttontexture);
    SDL_FreeSurface(rollbutton);
    SDL_DestroyTexture(rollbuttontexture);
    SDL_FreeSurface(rollimage);
    SDL_DestroyTexture(rollimagetexture);
    SDL_FreeSurface(endbackground);
    SDL_DestroyTexture(endbackgroundtexture);
    SDL_FreeSurface(wreath);
    SDL_DestroyTexture(wreathtexture);
    SDL_FreeSurface(greenbackground);
    SDL_DestroyTexture(greenbackgroundtexture);
    TTF_CloseFont(numberfont);
    TTF_CloseFont(letterfont);
    SDL_FreeSurface(number);
    SDL_DestroyTexture(numbertexture);
    IMG_Quit();
    TTF_Quit();
}
