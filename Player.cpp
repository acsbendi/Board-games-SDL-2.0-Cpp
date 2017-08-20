#include <iostream>
#include <SDL_image.h>
#include "player.h"

Player::Player(const string name, int numberofpieces, Point * starting, const char* image , SDL_Renderer* renderer) : name(name), numberofpieces(numberofpieces)
{
    pieces = new Piece*[numberofpieces];
    for(int i = 0; i < numberofpieces; i++)
        pieces[i] = new Piece(starting, this);
    this->image = IMG_Load(image);
    if(this->image == NULL)
    {
        std::cerr << "Képhiba !!! " << SDL_GetError();
        return;
    }
   texture = SDL_CreateTextureFromSurface(renderer,this->image);
}
Piece *& Player::operator[](int i)
{
    return pieces[i];
}
const Piece * Player::operator[](int i) const
{
    return pieces[i];
}
const string Player::getName() const
{
    return name;
}
Player::~Player()
{
    for(int i = 0; i < numberofpieces; i++)
        delete pieces[i];
    delete[] pieces;
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
}

void Player::setImage(SDL_Surface* image, SDL_Renderer* renderer)
{
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    this->image = image;
    texture = SDL_CreateTextureFromSurface(renderer, image);
}
SDL_Surface* Player::getImage() const
{
    return image;
}
SDL_Texture* Player::getTexture() const
{
    return texture;
}


