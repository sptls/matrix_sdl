#ifndef SYMBOL_H_
#define SYMBOL_H_

#include <cstdlib>
#include <time.h>
#include <SDL2/SDL.h>

#include "consts.h"

class Symbol
{
    public:
        Symbol();
        void SetY();
        void MoveSymbols();
        void Randomise();
        
        static int  seed;
        static int  screenWidth;
        static int  screenHeight;
        int         speed;
        int         size;
        int         length;
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