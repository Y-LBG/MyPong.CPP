/**
 * @file RacketRight.cpp
 *
 * @author Y-LBG <?@?.?>
 */

#include <SDL/SDL.h>
#include <sstream>
#include "Game.h"
#include "RacketRight.h"

RacketRight::RacketRight(SDL_Surface * window) :
   Racket(window) {
   _surface = Game::loadImage("res/RacketRight.png");
   _shadowSurface = Game::loadImage("res/ShadowRacketRight.png");

   _initialPosition.x = _window->w - _surface->w;
   _initialPosition.y = _window->h / 2 - _surface->h / 2;
   setToInitialPosition();
}

bool RacketRight::isInBoundingBox(int ballPositionX, int ballPositionTopY, int ballPositionBottomY) const {
   if (ballPositionX > _window->w - _surface->w && ballPositionBottomY > _position.y && ballPositionTopY < _position.y + _surface->h)
      return true;
   return false;
}

void RacketRight::paint() {
   Racket::paint();
   /* Score */
   std::ostringstream oss;
   oss << _score;
   std::string scoreString = oss.str();
   SDL_Color color = { 0, 0, 0 };
   SDL_Surface * scoreSurface = TTF_RenderText_Blended(_fontScore, scoreString.c_str(), color);
   SDL_Rect positionScore;
   positionScore.x = _window->w - scoreSurface->w - 20;
   positionScore.y = 20;
   SDL_BlitSurface(scoreSurface, NULL, _window, &positionScore);
}

