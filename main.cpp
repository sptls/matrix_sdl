#include "src/symbol.h"
#include "src/renderer.h"

#if defined(__linux__)
    int main(int argc, char **argv)
#else
    int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#endif
{
    int nrOfScreens = Renderer::GetNumOfScreens();
    printf("%i\n", nrOfScreens);
    Renderer* r = new Renderer[nrOfScreens];

    for(int i = 1; i <= nrOfScreens; i++)
        r[i-1].Init(i);

    for(int i = 1; i <= nrOfScreens; i++)
        r[i-1].Draw();

    delete[] r;

    return 0;
}