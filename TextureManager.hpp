#include "game.hpp"
#include <SDL_Image.h>
#pragma once

class TextureManager
{
public:
    static SDL_Texture * TextureLoader(const char * path);

private:
    static SDL_Surface * surface;
    static SDL_Texture * texture;
};