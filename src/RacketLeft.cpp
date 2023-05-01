/**
 * @file RacketLeft.cpp
 *
 * @author Y-LBG <?@?.?>
 */

#include <SDL/SDL.h>
#include <sstream>
#include "Game.h"
#include "RacketLeft.h"

RacketLeft::RacketLeft(SDL_Surface * window) :
   Racket(window)
{
   _surface = Game::loadImage("res/RacketLeft.png");
   _shadowSurface = Game::loadImage("res/ShadowRacketLeft.png");

   _initialPosition.x = 0;
   _initialPosition.y = _window->h / 2 - _surface->h / 2;
   setToInitialPosition();
}

bool RacketLeft::isInBoundingBox(int ballPositionX, int ballPositionTopY, int ballPositionBottomY) const {
   if (ballPositionX < _surface->w && ballPositionBottomY > _position.y && ballPositionTopY < _position.y + _surface->h)
      return true;
   return false;
}

void RacketLeft::paint() {
   Racket::paint();
   /* Score */
   std::ostringstream oss;
   oss << _score;
   std::string scoreString = oss.str();
   SDL_Color color = { 0, 0, 0 };
   SDL_Surface * scoreSurface = TTF_RenderText_Blended(_fontScore, scoreString.c_str(), color);
   SDL_Rect positionScore;
   positionScore.x = 20;
   positionScore.y = 20;
   SDL_BlitSurface(scoreSurface, NULL, _window, &positionScore);
}

