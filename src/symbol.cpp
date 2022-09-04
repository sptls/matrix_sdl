#include "symbol.h"


Symbol::Symbol()
{

}

void Symbol::SetY()
{
    for(int i = 1; i < length; i++)
    {
        Y[i] = Y[i-1] - (10*size);
        X[i] = X[i-1];
    }
}

void Symbol::MoveSymbols()
{
    for(int i = length; i > 0; i--)
        symbol[i] = symbol[i-1];
}

void Symbol::Randomise()
{
    seed++;
    srand(time(NULL) + seed);

    speed = rand() % SYMBOL_MAX_SPEED + 1;
    size = rand() % SYMBOL_MAX_SIZE + 1;
    length = rand() % SYMBOL_MAX_LEN + 1;
    if(length < 5)
        length = 5;
    symbol[0] = rand() % NR_OF_SYMBOLS;
    X[0] = rand() % WIN_W;
    Y[0] = (rand() % 100) - 200;
    SetY();
}