#ifndef RENDERER_H_
#define RENDERER_H_

#include <SDL2/SDL.h>
#include <stdio.h>
#include "symbol.h"
#include "consts.h"


class Renderer
{
    public:
        Renderer();
        void Init(int nrOfScreens);
        ~Renderer();
        void LoadSymbols();
        static int GetNumOfScreens();
        static void MainLoop(Renderer* r, int rCount);

        Symbol*                             s;
        int                                 symbolCount;
        static bool                         end;
        static Uint64                       endTimer;
        SDL_Texture*                        textureSymbols;
        SDL_Texture*                        textureSymbols_highlight;
        SDL_Texture*                        textureEndScreen;
        SDL_Window*                         window = NULL;
        SDL_Renderer*                       rendMain = NULL;
};

#endif