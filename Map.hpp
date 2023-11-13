#include "game.hpp"
#include "TextureManager.hpp"
#include <time.h>

class Map
{
public:
    Map(int width, int height, int Cwidth);
    ~Map();
    void Update();
    void Render();

    struct tile
    {
        int Material;
        int Selected;
    }**map;

private:

    struct temptile
    {
        int x;
        int y;
    }*tempmap;

    int i,j,k,l,temp,wi,he,Cwi;
    int mx,my;
    float brushsize=10.0;

    SDL_Rect dst;
    SDL_Rect src;

    SDL_Texture * sand;
    SDL_Texture * selected;

    void Physics();
    void Mouse();
};