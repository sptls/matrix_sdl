#include "renderer.h"

int Symbol::seed = 1;

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
            rendMain = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    }
    LoadSymbols();
};

void Renderer::Draw()
{
    SDL_Event       e;
    Uint64          tick = SDL_GetTicks64(); 
    Uint64          fallTick = SDL_GetTicks64();
    for(int i = 0; i < NR_OF_LINES; i++)
    {
        s[i].Randomise();
        s[i].tick = tick;
        s[i].fallTick = fallTick;
    }

    while(true)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_q:
                        SDL_DestroyWindow(window);
                        exit(0);
                }
            }
        }

        SDL_RenderClear(rendMain);

        for(int i = 0; i < NR_OF_LINES ; i++)
        {
            for(int j = 0; j < s[i].length; j++)
            {
                Uint64 currentTime = SDL_GetTicks64();
                if(currentTime > s[i].tick + 200)
                {
                    s[i].tick = currentTime;
                    if(j == 0)
                    {
                        s[i].symbol[j]++;
                        if(s[i].symbol[j] == NR_OF_SYMBOLS)
                            s[i].symbol[j] = 0;
                    }
                    s[i].MoveSymbols();
                }
                if(currentTime > s[i].fallTick + 20)
                {
                    for(int k = 0; k < s[i].length; k++)
                        s[i].Y[k] += s[i].speed;
                    s[i].fallTick = currentTime;
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
        SDL_Delay(10);
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

    spriteSurface = SDL_LoadBMP("background.bmp");
    if(spriteSurface == NULL)
    {
        printf("Failed to load BMP surface!\n");
        exit(0);
    }
    else
    {
       SDL_SetColorKey(spriteSurface, SDL_TRUE, SDL_MapRGB(spriteSurface->format, 0, 0, 0)); 
       textureBackground = SDL_CreateTextureFromSurface(rendMain, spriteSurface);
    }

    SDL_FreeSurface(spriteSurface);
};