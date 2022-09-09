#ifndef RENDERER_H_
#define RENDERER_H_

#include <SDL2/SDL.h>
#include <stdio.h>
#include "symbol.h"
#include "consts.h"

#if defined(__linux__)
    #include <X11/Xlib.h>
#else
    #include <windows.h>
#endif

class Renderer
{
    public:
        Renderer();
        void Init(int nrOfScreens);
        ~Renderer();
        void Draw();
        void LoadSymbols();
        static void GetScreenRes();
        static int GetNumOfScreens();

        Symbol*                              s;
        int                                 symbolCount;
        static bool                         end;
        static Uint64                       endTimer;
        SDL_Texture*                        textureSymbols;
        SDL_Texture*                        textureSymbols_highlight;
        SDL_Texture*                        textureBackground;
        SDL_Texture*                        textureEndScreen;
        SDL_Window*                         window = NULL;
        SDL_Renderer*                       rendMain = NULL;
};

#endif