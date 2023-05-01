/**
 * A home-made Pong.
 *
 * @version     2.1
 * @todo Elapsed time, IA, Menu, 3/4 players, ...
 *
 * @file MyPong.cpp
 *
 * @author Y-LBG <?@?.?>
 */

#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "Game.h"

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

int main(int argc, char* args[]) {
   /* Start SDL */
   if (SDL_Init(SDL_INIT_VIDEO) == -1) {
      std::cerr << "Error while initializing SDL\n" << std::endl;
      return -1;
   }

   /* Init TTF for text */
   if (TTF_Init() == -1) {
      std::cerr << "Error while initializing TTF : " << TTF_GetError() << std::endl;
      return -1;
   }

   /* Set Icon and Caption */
   SDL_WM_SetIcon(SDL_LoadBMP("res/Ball.png"), NULL);
   SDL_WM_SetCaption("MyPong", NULL);

   /* Create window */
   SDL_Surface * window = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
   if (window == NULL)
      return 1;

   SDL_EnableKeyRepeat(1, 1);

   /* Create Menu */
   //...

   /* Create game */
   Game * game = new Game(window);

   /* Delete game (Need to be done before SDL_Quit()) */
   delete game;

   /* Quit TTF used for text */
   TTF_Quit();

   /* Free window */
   SDL_FreeSurface(window);

   /* Quit SDL */
   SDL_Quit();
}

