#include "src/symbol.h"
#include "src/renderer.h"

#if defined(__linux__)
int main(int argc, char **argv)
#else
int WinMain(int argc, char **argv)
#endif
{
    Renderer r;
    r.Draw();

    return 0;
}