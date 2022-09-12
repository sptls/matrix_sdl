#include "renderer.h"

int Symbol::seed = 1;
int Symbol::screenWidth = 800;
int Symbol::screenHeight = 600;
bool Renderer::end = false;
Uint64 Renderer::endTimer = UINT64_MAX;

Renderer::Renderer()
{

};

void Renderer::Init(int nrOfScreens)
{
    SDL_Rect dispSize;
    SDL_GetDisplayBounds(nrOfScreens-1, &dispSize);
    Symbol::screenHeight = dispSize.h;
    Symbol::screenWidth = dispSize.w;
    symbolCount = Symbol::screenWidth/LINES_TO_WIDTH_RATIO;
    s = new Symbol[symbolCount];
    if(SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        printf("SDL init failed! Error: %s\n", SDL_GetError());
        exit(1);
    }
    else
    {
        window = SDL_CreateWindow("MATRIX", dispSize.x, dispSize.y, Symbol::screenWidth, Symbol::screenHeight, SDL_WINDOW_BORDERLESS);
        if(window == NULL)
        {
            printf("SDL failed creating window! Error: %s\n", SDL_GetError());
            exit(1);
        }
        else
        {
            SDL_SetWindowPosition(window, dispSize.x, dispSize.y);
            rendMain = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        }
    }
    LoadSymbols();
    Uint64          tick = SDL_GetTicks64(); 
    Uint64          fallTick = SDL_GetTicks64();
    for(int i = 0; i < symbolCount; i++)
    {
        s[i].Randomise();
        s[i].tick = tick;
        s[i].fallTick = fallTick;
    }
};

Renderer::~Renderer()
{
    SDL_DestroyWindow(window);
    delete[] s;
}

void Renderer::Draw()
{
    printf("draw started!\n");
    fflush(stdout);
    SDL_Event       e;
    Uint64          tick = SDL_GetTicks64(); 
    Uint64          fallTick = SDL_GetTicks64();
    for(int i = 0; i < symbolCount; i++)
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
                        endTimer = SDL_GetTicks64() + 3000;
                        end = true;
                }
            }
        }

        SDL_RenderClear(rendMain);

        for(int i = 0; i < symbolCount ; i++)
        {
            for(int j = 0; j < s[i].length; j++)
            {
                Uint64 currentTime = SDL_GetTicks64();
                if(!end)
                {
                    if(currentTime > s[i].tick + (400/s[i].speed))
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
                if(s[i].Y[s[i].length-1] > Symbol::screenHeight)
                    s[i].Randomise();
                if(end)
                {
                    SDL_Rect dst = {Symbol::screenWidth/2-END_SCREEN_W/2, Symbol::screenHeight/2-END_SCREEN_H/2, END_SCREEN_W, END_SCREEN_H};
                    SDL_Rect *src = NULL;
                    SDL_RenderCopy(rendMain, textureEndScreen, src, &dst);
                }
            }
        }
        SDL_RenderPresent(rendMain);
        SDL_Delay(10);
        if(SDL_GetTicks64() > endTimer)
            return;
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

    spriteSurface = SDL_LoadBMP("endscreen.bmp");
    if(spriteSurface == NULL)
    {
        printf("Failed to load BMP surface!\n");
        exit(0);
    }
    else
       textureEndScreen = SDL_CreateTextureFromSurface(rendMain, spriteSurface);

    SDL_FreeSurface(spriteSurface);
};

int Renderer::GetNumOfScreens()
{
    SDL_Init(SDL_INIT_VIDEO);
    int screens = SDL_GetNumVideoDisplays();
    if(screens < 1)
    {
        printf("Failed to get nr of screens! %s\n", SDL_GetError());
        return 0;
    }
    else
        return screens;
};

void Renderer::MainLoop(Renderer* r, int rCount)
{
    SDL_Event       e;
    while(true)
    {
        for(int rc = 0; rc < rCount; rc++)
        {
            while(SDL_PollEvent(&e) != 0)
            {
                if(e.type == SDL_KEYDOWN)
                {
                    switch(e.key.keysym.sym)
                    {
                        case SDLK_q:
                            Renderer::endTimer = SDL_GetTicks64() + 3000;
                            Renderer::end = true;
                    }
                }
            }

            SDL_RenderClear(r[rc].rendMain);

            for(int i = 0; i < r[rc].symbolCount ; i++)
            {
                for(int j = 0; j < r[rc].s[i].length; j++)
                {
                    Uint64 currentTime = SDL_GetTicks64();
                    if(!(r[rc].end))
                    {
                        if(currentTime > r[rc].s[i].tick + (400/r[rc].s[i].speed))
                        {
                            r[rc].s[i].tick = currentTime;
                            if(j == 0)
                            {
                                r[rc].s[i].symbol[j]++;
                                if(r[rc].s[i].symbol[j] == NR_OF_SYMBOLS)
                                    r[rc].s[i].symbol[j] = 0;
                            }
                            r[rc].s[i].MoveSymbols();
                        }
                        if(currentTime > r[rc].s[i].fallTick + 20)
                        {
                            for(int k = 0; k < r[rc].s[i].length; k++)
                                r[rc].s[i].Y[k] += r[rc].s[i].speed;
                            r[rc].s[i].fallTick = currentTime;
                        }
                    }
                    r[rc].s[i].rectSrc = {60 * r[rc].s[i].symbol[j], 0, 60, 60};
                    if(j == 0)
                    {
                        r[rc].s[i].rectDst = {r[rc].s[i].X[j], r[rc].s[i].Y[j], 12*r[rc].s[i].size, 12*r[rc].s[i].size};
                        SDL_RenderCopy(r[rc].rendMain, r[rc].textureSymbols_highlight, &r[rc].s[i].rectSrc, &r[rc].s[i].rectDst);
                    }
                    else
                    {
                        r[rc].s[i].rectDst = {r[rc].s[i].X[j], r[rc].s[i].Y[j], 10*r[rc].s[i].size, 10*r[rc].s[i].size};
                        SDL_RenderCopy(r[rc].rendMain, r[rc].textureSymbols, &r[rc].s[i].rectSrc, &r[rc].s[i].rectDst);
                    }
                    if(r[rc].s[i].Y[r[rc].s[i].length-1] > Symbol::screenHeight)
                        r[rc].s[i].Randomise();
                    if(r[rc].end)
                    {
                        SDL_Rect dst = {Symbol::screenWidth/2-END_SCREEN_W/2, Symbol::screenHeight/2-END_SCREEN_H/2, END_SCREEN_W, END_SCREEN_H};
                        SDL_Rect *src = NULL;
                        SDL_RenderCopy(r[rc].rendMain, r[rc].textureEndScreen, src, &dst);
                    }
                }
            }
            SDL_RenderPresent(r[rc].rendMain);
            SDL_Delay(10);
            if(SDL_GetTicks64() > r[rc].endTimer)
                return;
        }
    }
}