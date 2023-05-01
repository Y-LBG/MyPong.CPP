/**
 * @file Racket.h
 *
 * @author Y-LBG <?@?.?>
 */

#ifndef RACKET_H_
#define RACKET_H_

#include <SDL/SDL_ttf.h>

class Racket {
  public:
   /******************/
   /* PUBLIC METHODS */
   /******************/
   /**
    * Constructor.
    *
    * @param window
    * 			The main surface on which is drawn the game.
    */
   Racket(SDL_Surface * window);

   /**
    * Destructor.
    */
   virtual ~Racket();

   /**
    * Test whether the ball is in the racket bounding box.
    *
    * @param ballPositionX
    * 			Position of the ball along the X axis.
    * @param ballPositionTopY
    * 				Position of the top of the ball along the Y axis. (it would be the same than the ball position along Y axis)
    * @param ballPositionBottomY
    * 			Position of the bottom of the ball along the Y axis.
    * @return "true" is the ball is in the racket bounding box, "false" otherwise.
    */
   virtual bool isInBoundingBox(int ballPositionX, int ballPositionTopY, int ballPositionBottomY) const = 0;

   /**
    * Accelerate the racket upward.
    */
   void accelerateUp();

   /**
    * Accelerate the racket downward
    */
   void accelerateDown();

   /**
    * Move the racket.
    *    
    * @param elapsedTime
    * 			The time elapsed between two frames.
    * @return The movement of the racket in pixel.(Useful if you want to know when the racket doesn't move because of the edge)
    */
   int move(double elapsedTime);

   /**
    * Paint the racket at its current position.
    */
   virtual void paint();

   /**
    * Helps the ball determine its Y velocity when bouncing on this racket.
    *
    * @param middleOfBallPositionY
    * 			Position of the middle of the ball along the Y axis.
    * @return	The velocity given by the racket to the ball along the Y axis.
    */
   int getYVelocityOfBallWhileBouncing(int middleOfBallPositionY) const;

   /**
    * Get the width of the racket.
    *
    * @return Width of the racket.
    */
   int getWidth() const {
      return _surface->w;
   }

   /**
    * Get the height of the racket.
    *
    * @return Height of the racket.
    */
   int getHeight() const {
      return _surface->h;
   }

   /**
    * Operator == overloading for the class Racket.
    *
    * @param r
    * 			Another racket.
    * @return "true" if the racket passed as an argument is the same than the current racket, "false" otherwise.
    */
   bool operator==(const Racket & r) const;

   /**
    * Increase the score of the player controlling this racket.
    */
   void increaseScore();

   /**
    * Set the racket to its initial position.
    */
   void setToInitialPosition();

   /**
    * Update the shadow position depending on the new racket position.
    * ( Called in paint() )
    */
   void updateShadowPosition();

  protected:
   /************************/
   /* PROTECTED ATTRIBUTES */
   /************************/
   SDL_Surface * _window; // Window
   SDL_Surface * _surface; // Racket Surface
   SDL_Surface * _shadowSurface; // Racket Shadow Surface

   SDL_Rect _initialPosition; // Initial Position
   SDL_Rect _position; // Position
   SDL_Rect _shadowPosition; // Shadow Position

   TTF_Font * _fontScore; // Font used to write the score.

   int _score; // Score

   double _speed; // Racket's speed

   bool _isAccelerating; // "True" when accelerating

   /*******************************/
   /* PROTECTED STATIC ATTRIBUTES */
   /*******************************/
   static const int MAX_SPEED = 3; // Maximum norm of the racket speed vector
   static const double ACCELERATION = 0.1; // Default norm of the racket acceleration vector
   static const double REBOUND_FACTOR = -0.85; // Default norm of the racket acceleration vector
   static const double INERTIA_FACTOR = 0.975; // Default norm of the racket acceleration vector
};

#endif /* RACKET_H_ */
