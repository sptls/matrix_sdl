#ifndef SYMBOL_H_
#define SYMBOL_H_

#define SYMBOL_MAX_SPEED 20
#define SYMBOL_MAX_SIZE 20
#define SYMBOL_MAX_LEN 20
#define SYMBOL_ARR_SIZE 20

class Symbol
{
    public:
        Symbol();
        int         speed;
        int         size;
        int         length;
        int         X, Y;
        int         symbol[SYMBOL_ARR_SIZE];
        bool        visible = false;
};


#endif