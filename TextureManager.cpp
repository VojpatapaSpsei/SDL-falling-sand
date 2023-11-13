#include "TextureManager.hpp"

SDL_Surface * TextureManager::surface=NULL;
SDL_Texture * TextureManager::texture=NULL;

SDL_Texture * TextureManager::TextureLoader(const char *path)
{
    surface= IMG_Load(path);
    texture=SDL_CreateTextureFromSurface(Game::renderer,surface);
    SDL_FreeSurface(surface);

    return texture;
}