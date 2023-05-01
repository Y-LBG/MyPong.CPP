/**
 * @file Racket.cpp
 *
 * @author Y-LBG <?@?.?>
 */

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Racket.h"
#include <iostream>

Racket::Racket(SDL_Surface * window) :
   _window(window), 
   _fontScore(TTF_OpenFont("res/zenzai.ttf", 65)),
   _score(0), 
   _speed(0),
   _isAccelerating(false)
{

}

Racket::~Racket() {
   TTF_CloseFont(_fontScore);
   SDL_FreeSurface(_surface);
}

void Racket::accelerateUp() {
   /* Update speed */
   _speed -= ACCELERATION;

   if(_speed < -MAX_SPEED)
      _speed = -MAX_SPEED;

   /* Update accelerating state */
   _isAccelerating = true;
}

void Racket::accelerateDown() {
   /* Update speed */
   _speed += ACCELERATION;

   if(_speed > MAX_SPEED)
      _speed = MAX_SPEED;

   /* Update accelerating state */
   _isAccelerating = true;
}

int Racket::move(double elapsedTime) { //TODO Take account of elapsedTime
   int previousPositionY = _position.y;

   /* Simulate Inertia */
   if(!_isAccelerating) {
      _speed *= INERTIA_FACTOR;
   } else {
      _isAccelerating = false;
   }
	
   /* Move only if not on the edges */
   if (_position.y + (int) _speed >= 0 && _position.y + (int) _speed <= _window->h - _surface->h)
      _position.y += (int) _speed;
   else if (_position.y + (int) _speed < 0) {
      _position.y = 0;
      _speed *= REBOUND_FACTOR; // Rebound on edges
   } else {
      _position.y = _window->h - _surface->h;
      _speed *= REBOUND_FACTOR; // Rebound on edges
   }

   return _position.y - previousPositionY;
}

void Racket::paint() {
   /* Paint the shadow */
   updateShadowPosition();
   SDL_BlitSurface(_shadowSurface, NULL, _window, &_shadowPosition);

   /* Paint the racket */
   SDL_BlitSurface(_surface, NULL, _window, &_position);
}

int Racket::getYVelocityOfBallWhileBouncing(int middleOfBallPositionY) const {
   int middleOfRacketPositionY = _position.y + _surface->h / 2;
   return (middleOfBallPositionY - middleOfRacketPositionY) / 10;

}

bool Racket::operator==(const Racket &r) const {
   return (this == &r);
}

void Racket::increaseScore() {
   _score++;
}

void Racket::setToInitialPosition() {
   _position.x = _initialPosition.x;
   _position.y = _initialPosition.y;
}

void Racket::updateShadowPosition() {
   _shadowPosition.x = _position.x + _surface->w / 2 - _shadowSurface->w / 2;
   _shadowPosition.y = _position.y + _surface->h / 2 - _shadowSurface->h / 2;
}
