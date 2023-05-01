/**
 * @file RacketRight.h
 *
 * @author Y-LBG <?@?.?>
 */

#ifndef RACKETRIGHT_H_
#define RACKETRIGHT_H_

#include "Racket.h"

class RacketRight : public Racket {
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
   RacketRight(SDL_Surface * window);

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
   virtual bool isInBoundingBox(int ballPositionX, int ballPositionTopY, int ballPositionBottomY) const;

   /**
    * Paint the racket at its current position and the score corresponding.
    */
   virtual void paint();
};

#endif /* RACKETRIGHT_H_ */
