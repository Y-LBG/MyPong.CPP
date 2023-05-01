/**
 * @file Game.cpp
 *
 * @author Y-LBG <?@?.?>
 */

#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Game.h"

Game::Game(SDL_Surface * window) :
   _window(window), _racketLeft(window), _racketRight(window), _ball(window, _racketLeft, _racketRight) {

   /* Load Background */
   _background = loadImage("res/Background.jpg");

   /* Refresh Screen */
   refreshScreen();

   handleEventBeforeService();
}

Game::~Game() {
   SDL_FreeSurface(_background);
}

void Game::handleEventBeforeService() {
   SDL_Event event;
   Uint8 * keystate = NULL;
   Uint32 previousTime, currentTime = SDL_GetTicks(); // Time handling
   double elapsedTime;
   bool quit = false;
   int result = NO_WINNER;
   int rightRacketMovement, leftRacketMovement;

   refreshScreen();

   while (!quit) {
      /* Update the time */
      previousTime = currentTime;
      currentTime = SDL_GetTicks();
      elapsedTime = (currentTime - previousTime) / 1000.0f;

      /* If there's an event to handle */
      if (SDL_PollEvent(&event)) {
	 switch (event.type) {
	    case SDL_QUIT:
	       /* If the user has X out the window, quit the program */
	       quit = true;
	       break;
	    case SDL_KEYDOWN:
	       keystate = SDL_GetKeyState(NULL);
	       if (keystate[SDLK_ESCAPE])
		  quit = true;

	       /* Keys for Left Racket : Space, e, d */
	       if (keystate[SDLK_SPACE]) {
		  if (_ball.isInitialRacket(_racketLeft)) {
		     /* Launch game */
		     result = beginMatch();

		     /* Restart after score OR Leave the game */
		     quit = testResultAndReset(result);
		  }
	       }
	       if (keystate[SDLK_e]) {
		  _racketLeft.accelerateUp();
	       }
	       if (keystate[SDLK_d]) {
		  _racketLeft.accelerateDown();
	       }

	       /* Keys for Left Racket : Num5, Up, Down */
	       if (keystate[SDLK_KP5]) {
		  if (_ball.isInitialRacket(_racketRight)) {
		     /* Launch game */
		     result = beginMatch();

		     /* Restart after score OR Leave the game */
		     quit = testResultAndReset(result);
		  }
	       }
	       if (keystate[SDLK_UP]) {
		  _racketRight.accelerateUp();
	       }
	       if (keystate[SDLK_DOWN]) {
		  _racketRight.accelerateDown();
	       }
	       break;
	    default:
	       break;
	 }
      }

      /* Rackets movement */
      rightRacketMovement = _racketRight.move(elapsedTime);
      leftRacketMovement = _racketLeft.move(elapsedTime);

      /* Ball movement */
      if (_ball.isInitialRacket(_racketRight))
	 _ball.moveAlongYAxis(rightRacketMovement);
      else if (_ball.isInitialRacket(_racketLeft))
	 _ball.moveAlongYAxis(leftRacketMovement);

      /* Refresh */
      refreshScreen();
   }
}

bool Game::testResultAndReset(int & result) {
   if (result == EXIT_GAME)
      return true;
   else if (result == RIGHT_WON_POINT) {
      _ball.setInitialRacket(_racketLeft);
      _racketLeft.setToInitialPosition();
      _racketRight.setToInitialPosition();
      refreshScreen();
   } else if (result == LEFT_WON_POINT) {
      _ball.setInitialRacket(_racketRight);
      _racketLeft.setToInitialPosition();
      _racketRight.setToInitialPosition();
      refreshScreen();
   }
   result = NO_WINNER;
   return false;
}

int Game::beginMatch() {
   SDL_Event event;
   Uint8 * keystate = NULL;
   Uint32 previousTime, currentTime = SDL_GetTicks(); // Time handling
   double elapsedTime;
   bool quit = false;

   while (!quit) {
      /* Update the time */
      previousTime = currentTime;
      currentTime = SDL_GetTicks();
      elapsedTime = (currentTime - previousTime) / 1000.0f;

      /* If there's an event to handle */
      if (SDL_PollEvent(&event)) {
	 switch (event.type) {
	    case SDL_QUIT:
	       /* If the user has X out the window, quit the program */
	       return EXIT_GAME;
	    case SDL_KEYDOWN:
	       keystate = SDL_GetKeyState(NULL);
	       if (keystate[SDLK_ESCAPE])
		  return EXIT_GAME;

	       /* Keys for Left Racket : e, d */
	       if (keystate[SDLK_e]) {
		  _racketLeft.accelerateUp();
	       }
	       if (keystate[SDLK_d]) {
		  _racketLeft.accelerateDown();
	       }
	       /* Keys for Left Racket : Up, Down */
	       if (keystate[SDLK_UP]) {
		  _racketRight.accelerateUp();
	       }
	       if (keystate[SDLK_DOWN]) {
		  _racketRight.accelerateDown();
	       }
	       break;
	    default:
	       break;
	 }
      }

      /* Rackets movement */
      _racketLeft.move(elapsedTime);
      _racketRight.move(elapsedTime);

      /* Ball movement */
      int winner = _ball.move(elapsedTime);
      if (winner == RIGHT_WON_POINT || winner == LEFT_WON_POINT)
	 return winner;

      /* Refresh */
      refreshScreen();
   }
   return true;
}

SDL_Surface * Game::loadImage(std::string filename) {
   SDL_Surface* loadedImage = NULL;

   /* Load the image */
   loadedImage = IMG_Load(filename.c_str());

   //	/* If nothing went wrong in loading the image */
   //	if (loadedImage != NULL) {
   //		/* Create an optimized image */
   //		/* The optimized image that will be used */
   //		SDL_Surface* optimizedImage = SDL_DisplayFormat(loadedImage);
   //
   //		/* Free the old image */
   //		SDL_FreeSurface(loadedImage);
   //
   //		/* Return the optimized image */
   //		return optimizedImage;
   //	}

   return loadedImage;
}

void Game::refreshScreen() {
   /* Background */
   SDL_Rect positionBackground;
   positionBackground.x = 0;
   positionBackground.y = 0;
   SDL_BlitSurface(_background, NULL, _window, &positionBackground);

   /*Racket & Ball */
   _racketLeft.paint();
   _racketRight.paint();
   _ball.paint();

   /* Flip screen */
   SDL_Flip(_window);
}
