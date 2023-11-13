#include "game.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"

SDL_Renderer *  Game::renderer=NULL;
SDL_Window * Game::window=NULL;

Map * map;

bool Game::LeftClick=NULL;
bool Game::RightClick=NULL;
bool Game::ScrollUp=NULL;
bool Game::ScrollDown=NULL;

Game::Game()
{

}

Game::~Game()
{

}

void Game::Init(const char * title, int width, int height)
{
    window=SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_MOUSE_GRABBED);
     renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer,255,255,255,0);
    running=true;

    map=new Map(width,height,4);

    SDL_ShowCursor(SDL_DISABLE);

}

void Game::HandleEvents()
{
    ScrollUp = false;
    ScrollDown = false;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            running = false;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                LeftClick = true;
            }
            else if (event.button.button == SDL_BUTTON_RIGHT)
            {
                RightClick = true;
            }
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                LeftClick = false;
            }
            else if (event.button.button == SDL_BUTTON_RIGHT)
            {
                RightClick = false;
            }
        }
        else if (event.type == SDL_MOUSEWHEEL)
        {
            if (event.wheel.y > 0)
            {
                ScrollUp = true;
            }
            else if (event.wheel.y < 0)
            {
                ScrollDown = true;
            }
        }
    }
}


void Game::Update()
{
    map->Update();
}

void Game::Render()
{
    SDL_RenderClear(renderer);

    map->Render();

    SDL_RenderPresent(renderer);
}

bool Game::Running()
{
    return running;
}

void Game::Clear()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}