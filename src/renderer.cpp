#include "renderer.h"

Renderer::Renderer()
{
    if(SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        printf("SDL init failed! Error: %s\n", SDL_GetError());
        exit(1);
    }
    else
    {
        window = SDL_CreateWindow("TEST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
        if(window == NULL)
        {
            printf("SDL failed creating window! Error: %s\n", SDL_GetError());
            exit(1);
        }
        else
        {
            rendMain = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            SDL_SetRenderDrawColor(rendMain, 0x00, 0x00, 0x00, 0x00);
        }
    }
};

void Renderer::Draw()
{
    SDL_RenderClear(rendMain);
    SDL_RenderPresent(rendMain);
};