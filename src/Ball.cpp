/**
 * @file Ball.cpp
 *
 * @author Y-LBG <?@?.?>
 */

#include <cmath>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Game.h"
#include "RacketLeft.h"
#include "RacketRight.h"
#include "Ball.h"

Ball::Ball(SDL_Surface * window, RacketLeft & racketLeft, RacketRight & racketRight) :
   _window(window), 
   _racketLeft(racketLeft), 
   _racketRight(racketRight), 
   _initialRacket(&racketRight) 
{
   _surface = Game::loadImage("res/Ball.png");

   _velocity.x = -INITIAL_X_VELOCITY;
   _velocity.y = INITIAL_Y_VELOCITY;

   _position.x = _window->w - _racketRight.getWidth() - _surface->w;
   _position.y = _window->h / 2 - _surface->h / 2;
}

Ball::~Ball() {
   SDL_FreeSurface(_surface);
}

int Ball::move(double elapsedTime) { //TODO Take account of elapsedTime
   /* Bounce on rackets */
   if (_racketLeft.isInBoundingBox(_position.x + _velocity.x, _position.y + _velocity.y, _position.y + _velocity.y + _surface->h)) { // Bounce on Left Racket
      /* Update velocity */
      _velocity.x *= -1;
      _velocity.y = _racketLeft.getYVelocityOfBallWhileBouncing(_position.y + _velocity.y + _surface->h / 2);

      /* Normalize velocity */
      double normOfVelocity = sqrt(_velocity.x * _velocity.x + _velocity.y * _velocity.y);
      _velocity.x = _velocity.x / normOfVelocity * NORM_OF_VELOCITY_VECTOR;
      _velocity.y = _velocity.y / normOfVelocity * NORM_OF_VELOCITY_VECTOR;

      /* Update position */
      _position.x = _racketLeft.getWidth();
      _position.y += _velocity.y;
   } else if (_racketRight.isInBoundingBox(_position.x + _velocity.x + _surface->w, _position.y + _velocity.y, _position.y + _velocity.y + _surface->h)) { // Bounce on Right Racket
      /* Update velocity */
      _velocity.x *= -1;
      _velocity.y = _racketRight.getYVelocityOfBallWhileBouncing(_position.y + _velocity.y + _surface->h / 2);

      /* Normalize velocity */
      double normOfVelocity = sqrt(_velocity.x * _velocity.x + _velocity.y * _velocity.y);
      _velocity.x = _velocity.x / normOfVelocity * NORM_OF_VELOCITY_VECTOR;
      _velocity.y = _velocity.y / normOfVelocity * NORM_OF_VELOCITY_VECTOR;

      /* Update position */
      _position.x = _window->w - _racketRight.getWidth() - _surface->w;
      _position.y += _velocity.y;
   } else if (_position.x + _velocity.x > _window->w - _surface->w) { // Left wins
      _racketLeft.increaseScore();
      return Game::LEFT_WON_POINT;
   } else if (_position.x + _velocity.x < 0) { // Right wins
      _racketRight.increaseScore();
      return Game::RIGHT_WON_POINT;
   } else {
      /* Update position */
      _position.x += _velocity.x;
   }
   /* To avoid the ball to be stuck */
   if(_position.x == 0)
      _position.x = 1;
   

   /* Bounce on Top & Bottom */
   if (_position.y + _velocity.y > _window->h - _surface->h) {
      /* Update velocity */
      _velocity.y *= -1;

      /* Update position */
      _position.y = _window->h - _surface->h;
   } else if (_position.y + _velocity.y < 0) {
      /* Update velocity */
      _velocity.y *= -1;

      /* Update position */
      _position.y = 0;
   } else {
      /* Update position */
      _position.y += _velocity.y;
   }

   return Game::NO_WINNER;
}

void Ball::moveAlongYAxis(int movement) {
   _position.y += movement;
}

bool Ball::isInitialRacket(Racket & racket) const {
   return (racket == *_initialRacket);
}

void Ball::setInitialRacket(const Racket & racket) {
   _initialRacket = &racket;

   /* Set the initial position of the ball depending on its initial racket */
   if (racket == _racketLeft) {
      _position.x = _racketLeft.getWidth();
      _position.y = _window->h / 2 - _surface->h / 2;

      _velocity.x = INITIAL_X_VELOCITY;
   } else if (racket == _racketRight) {
      _velocity.x = -INITIAL_X_VELOCITY;

      _position.x = _window->w - _racketRight.getWidth() - _surface->w;
      _position.y = _window->h / 2 - _surface->h / 2;
   }
   _velocity.y = INITIAL_Y_VELOCITY;

}

void Ball::paint() {
   SDL_BlitSurface(_surface, NULL, _window, &_position);
}
