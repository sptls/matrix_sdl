#ifndef RENDERER_H_
#define RENDERER_H_

#include <SDL2/SDL.h>
#include <stdio.h>
#include "symbol.h"
#include "consts.h"

#if defined(__linux__)
    #include <X11/Xlib.h>
#else
    //windows header here
#endif

class Renderer
{
    public:
        Renderer();
        ~Renderer();
        void Draw();
        void LoadSymbols();
        static void GetScreenRes();

        Symbol*             s;
        int                 symbolCount;
        bool                end = false;
        Uint64              endTimer = UINT64_MAX;
        SDL_Texture*        textureSymbols;
        SDL_Texture*        textureSymbols_highlight;
        SDL_Texture*        textureBackground;
        SDL_Texture*        textureEndScreen;
        SDL_Window*         window = NULL;
        SDL_Renderer*       rendMain = NULL;
};

#endif