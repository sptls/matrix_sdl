#ifndef RENDERER_H_
#define RENDERER_H_

#include <SDL2/SDL.h>
#include <stdio.h>
#include "symbol.h"

#define WIN_W 1280
#define WIN_H 720

class Renderer
{
    public:
        Renderer();
        void Draw();
        void LoadSymbols();
        void MainLoop();

        Symbol              s[100];
        SDL_Texture*        textureSymbols;
        SDL_Texture*        textureSymbols_highlight;
        SDL_Window*         window = NULL;
        SDL_Renderer*       rendMain = NULL;
};

#endif