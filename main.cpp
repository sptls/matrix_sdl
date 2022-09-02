#include "src/symbol.h"
#include "src/renderer.h"

int WinMain(int argc, char **argv)
{
    Renderer r;
    while(true)
    {
        r.MainLoop();
    }
    return 0;
}