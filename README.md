# MyPong

Tiny "Pong" project I worked on back in my student days to have fun with C++.

I'm actually surprised the code isn't as terrible as I would have expected, looking at it after so many years 😝

## Resources

All image resources have been created using GIMP.

The font was found here : https://www.dafont.com/zenzai-itacha.font

## Librairies required
- SDL
- SDL_image
- SDL_ttf

## Controls (to play)
| Left Player |                 | Right Player |
|:-----------:|:---------------:|:------------:|
|      e      |  <= Move up =>  |   Up arrow   |
|      d      | <= Move down => |  Down arrow  |
|    Space    |   <= Serve =>   |  5 (Numpad)  |

## Ideas
1) Take account of elapsed time between frames (c.f. Ball.move() & Racket.move())
2) Add a fallible IA (i.e. which doesn't simply follow the ball, but interact with its racket using accelerateUp() & accelerateDown(), as a human would)
3) Handle a simple menu
4) Play with 3/4 players (i.e. Rackets on the top and bottom of the screen)
