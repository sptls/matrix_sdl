#include "renderer.h"

int Symbol::seed = 1;
int Symbol::screenWidth = 800;
int Symbol::screenHeight = 600;

Renderer::Renderer()
{
    Renderer::GetScreenRes();
    symbolCount = Symbol::screenWidth/LINES_TO_WIDTH_RATIO;
    s = new Symbol[symbolCount];
    if(SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        printf("SDL init failed! Error: %s\n", SDL_GetError());
        exit(1);
    }
    else
    {
        window = SDL_CreateWindow("TEST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Symbol::screenWidth, Symbol::screenHeight, SDL_WINDOW_BORDERLESS);
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

Renderer::~Renderer()
{
    SDL_DestroyWindow(window);
    delete[] s;
}

void Renderer::Draw()
{
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

void Renderer::GetScreenRes()
{
    #if defined(__linux__)
        Display         *d = XOpenDisplay(NULL);
        Screen          *s = DefaultScreenOfDisplay(d);
        
        Symbol::screenHeight = s->height;
        Symbol::screenWidth = s->width;
        //Symbol::screenWidth = 2560;
        printf("Resolution: %ix%i\n", Symbol::screenWidth, Symbol::screenHeight);
    #else
        Symbol::screenWidth = 1920;
        Symbol::screenHeight = 1080;
        //windows get res function here!
    #endif
};