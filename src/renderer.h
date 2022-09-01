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

        Symbol              s[100];
        SDL_Window*         window = NULL;
        SDL_Renderer*       rendMain = NULL;
};

#endif