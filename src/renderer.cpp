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
    LoadSymbols();
};

void Renderer::Draw()
{
    SDL_Event       e;
    Uint64          tick = SDL_GetTicks64(); 
    Uint64          fallTick = SDL_GetTicks64();
    for(int i = 0; i < 100; i++)
        s[i].Randomise();

    while(true)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_q:
                        exit(0);
                }
            }
        }

        SDL_RenderClear(rendMain);

        for(int i = 0; i < 100 ; i++)
        {
            for(int j = 0; j < s[i].length; j++)
            {
                Uint64 currentTime = SDL_GetTicks64();
                if(currentTime > tick + 200)
                {
                    tick = currentTime;
                    if(j == 0)
                    {
                        s[i].symbol[j]++;
                        if(s[i].symbol[j] == NR_OF_SYMBOLS)
                            s[i].symbol[j] = 0;
                    }
                    s[i].MoveSymbols();
                }
                if(currentTime > fallTick + 20)
                {
                    for(int k = 0; k < s[i].length; k++)
                        s[i].Y[k] += s[i].speed;
                    fallTick = currentTime;
                }
                s[i].rectSrc = {60 * s[i].symbol[j], 0, 60, 60};
                if(j == 0)
                {
                    s[i].rectDst = {s[i].X[j], s[i].Y[j], 12*s[i].size, 12*s[i].size};
                    SDL_RenderCopy(rendMain, textureSymbols_highlight, &s[i].rectSrc, &s[i].rectDst);
                }
                else
                {
                    s[i].rectDst = {s[i].X[j], s[i].Y[j], 10*s[i].size, 10*s[i].size};
                    SDL_RenderCopy(rendMain, textureSymbols, &s[i].rectSrc, &s[i].rectDst);
                }
                if(s[i].Y[s[i].length-1] > WIN_H)
                    s[i].Randomise();
            }
        }
        SDL_RenderPresent(rendMain);
    }
};

void Renderer::LoadSymbols()
{
    SDL_Surface*        spriteSurface = SDL_LoadBMP("sprite.bmp");
    if(spriteSurface == NULL)
    {
        printf("Failed to load BMP surface!\n");
        exit(0);
    }
    else
    {
       SDL_SetColorKey(spriteSurface, SDL_TRUE, SDL_MapRGB(spriteSurface->format, 0, 0, 0)); 
       textureSymbols = SDL_CreateTextureFromSurface(rendMain, spriteSurface);
    }

    SDL_FreeSurface(spriteSurface);
    
    spriteSurface = SDL_LoadBMP("sprite_alt.bmp");
    if(spriteSurface == NULL)
    {
        printf("Failed to load BMP surface!\n");
        exit(0);
    }
    else
    {
       SDL_SetColorKey(spriteSurface, SDL_TRUE, SDL_MapRGB(spriteSurface->format, 0, 0, 0)); 
       textureSymbols_highlight = SDL_CreateTextureFromSurface(rendMain, spriteSurface);
    }

    SDL_FreeSurface(spriteSurface);
};

void Renderer::MainLoop()
{
    Draw();
};