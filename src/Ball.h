/**
 * @file Ball.h
 *
 * @author Y-LBG <?@?.?>
 */

#ifndef BALL_H_
#define BALL_H_

#include "RacketLeft.h"
#include "RacketRight.h"

class Ball {
  public:
   /******************/
   /* PUBLIC METHODS */
   /******************/
   /**
    * Constructor.
    *
    * @param window
    * 			The main surface on which is drawn the game.
    * @param racketLeft
    * 			The left racket.
    * @param racketRight
    * 			The right racket.
    */
   Ball(SDL_Surface * window, RacketLeft & racketLeft, RacketRight & racketRight);

   /**
    * Destructor.
    */
   virtual ~Ball();

   /**
    * Move the ball.
    *
    * @param elapsedTime
    * 			The time elapsed between two frames.
    * @return Game::NO_WINNER if the ball is still inside the play area, Game::RIGHT_WON_POINT if the right player won or Game::LEFT_WON_POINT if the left player won.
    */
   int move(double elapsedTime);

   /**
    * Move the ball along the Y axis. (Useful to move the ball with its initial racket before the service)
    *
    * @param movement
    * 			Number of pixel we want the ball to move.
    */
   void moveAlongYAxis(int movement);

   /**
    * Test is the argument is the ball initial racket.
    *
    * @param racket
    * 			The racket to be tested.
    * @return "true" if it's the same racket, "false" otherwise.
    */
   bool isInitialRacket(Racket & racket) const;

   /**
    * Set theball initial racket.
    *
    * @param racket
    * 			The racket we want to set as initial racket.
    */
   void setInitialRacket(const Racket & racket);

   /**
    * Paint the ball at its current position.
    */
   void paint();

  private:
   /**********************/
   /* PRIVATE ATTRIBUTES */
   /**********************/
   SDL_Surface * _window; // Window
   SDL_Surface * _surface; // Ball Surface

   SDL_Rect _position; // Position
   SDL_Rect _velocity; // Velocity

   RacketLeft & _racketLeft; // Left racket
   RacketRight & _racketRight; // Right racket

   const Racket * _initialRacket; // Initial racket

   /*****************************/
   /* PRIVATE STATIC ATTRIBUTES */
   /*****************************/
   static const int NORM_OF_VELOCITY_VECTOR = 7;
   static const int INITIAL_X_VELOCITY = NORM_OF_VELOCITY_VECTOR;
   static const int INITIAL_Y_VELOCITY = 0;

};

#endif /* BALL_H_ */
