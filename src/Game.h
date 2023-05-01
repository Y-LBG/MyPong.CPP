/**
 * Class handling the game.
 *
 * @file Game.h
 *
 * @author Y-LBG <?@?.?>
 */

#ifndef GAME_H_
#define GAME_H_

#include <string>
#include "RacketLeft.h"
#include "RacketRight.h"
#include "Ball.h"

class Game {
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
   Game(SDL_Surface * window);

   /**
    * Destructor.
    */
   virtual ~Game();

   /*************************/
   /* PUBLIC STATIC METHODS */
   /*************************/
   static SDL_Surface * loadImage(std::string filename);

   /*****************************/
   /* PUBLIC STATIC ATTRIBUTES */
   /*****************************/
   static const int EXIT_GAME = 0;
   static const int RIGHT_WON_POINT = 1;
   static const int LEFT_WON_POINT = 2;
   static const int NO_WINNER = 3;

  private:
   /**********************/
   /* PRIVATE ATTRIBUTES */
   /**********************/
   SDL_Surface * _window; // Window
   SDL_Surface * _background; // Background

   RacketLeft _racketLeft; //Left Player Racket
   RacketRight _racketRight; //Right Player Racket
   Ball _ball; // Ball

   /*******************/
   /* PRIVATE METHODS */
   /*******************/
   /**
    * Handle events before service, which means before the player launch the ball at the beginning of the game or after loosing a point.
    */
   void handleEventBeforeService();

   /**
    * Begin the match, which is after the service.
    */
   int beginMatch();

   /**
    * Refresh the screen with the new positions of the rackets and ball and the new scores.
    */
   void refreshScreen();

   /**
    * Test the result of a game (leave the game, game won by the right player or game won by the left player) and reset positions if needed.
    *
    * @param result
    * 			The result to be tested.
    * @return "true" if leaving the game, "false" otherwise.
    */
   bool testResultAndReset(int & result);
};

#endif /* GAME_H_ */
