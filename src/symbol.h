#ifndef SYMBOL_H_
#define SYMBOL_H_

#include <cstdlib>
#include <time.h>
#include <SDL2/SDL.h>

#define SYMBOL_MAX_SPEED 15
#define SYMBOL_MAX_SIZE 5
#define SYMBOL_MAX_LEN 20
#define NR_OF_SYMBOLS 74

#define WIN_H 1440
#define WIN_W 2560

class Symbol
{
    public:
        Symbol();
        void SetY();
        void MoveSymbols();
        void Randomise();
        
        static int  seed;
        int         speed = 0;
        int         size = 4;
        int         length = 20;
        int         X[SYMBOL_MAX_LEN];
        int         Y[SYMBOL_MAX_LEN];
        int         symbol[SYMBOL_MAX_LEN];
        bool        visible = false;
        Uint64      tick = 0;
        Uint64      fallTick = 0;
        SDL_Rect    rectDst;
        SDL_Rect    rectSrc;
};


#endif