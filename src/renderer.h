#ifndef RENDERER_H_
#define RENDERER_H_

#include <SDL2/SDL.h>
#include <stdio.h>
#include "symbol.h"

#define NR_OF_LINES 200

class Renderer
{
    public:
        Renderer();
        void Draw();
        void LoadSymbols();

        Symbol              s[NR_OF_LINES];
        SDL_Texture*        textureSymbols;
        SDL_Texture*        textureSymbols_highlight;
        SDL_Texture*        textureBackground;
        SDL_Window*         window = NULL;
        SDL_Renderer*       rendMain = NULL;
};

#endif