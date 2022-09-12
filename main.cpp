#include "src/symbol.h"
#include "src/renderer.h"

#if defined(__linux__)
    int main(int argc, char **argv)
#else
    #include <windows.h>
    int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#endif
{
    int nrOfScreens = Renderer::GetNumOfScreens();
    if(nrOfScreens < 0)
        return -1;
    Renderer* r = new Renderer[nrOfScreens];

    for(int i = 1; i <= nrOfScreens; i++)
        r[i-1].Init(i);

    Renderer::MainLoop(r, nrOfScreens);

    delete[] r;

    return 0;
}