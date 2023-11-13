#include <stdio.h>
#include <SDL.h>
#include "game.hpp"

Game* game;

int WinMain(int argc, char* argv[])
{
    const int width = 960 * 1.5;
    const int height = 540 * 1.5;

    const int FPS = 60;
    const int FrameDelay = 1000 / FPS;
    Uint32 FrameStart;
    int FrameTime;
    int frameCount = 0;
    int lastTime = SDL_GetTicks();

    game = new Game();

    game->Init("Sand simulation", width, height);

    while (game->Running())
    {
        FrameStart = SDL_GetTicks();

        game->HandleEvents();
        game->Update();
        game->Render();

        frameCount++;

        FrameTime = SDL_GetTicks() - FrameStart;
        if (FrameDelay > FrameTime)
        {
            SDL_Delay(FrameDelay - FrameTime);
        }

        int currentTime = SDL_GetTicks();
        if (currentTime - lastTime >= 1000)
        {
            printf("FPS: %d\n", frameCount);

            frameCount = 0;
            lastTime = currentTime;
        }
    }

    game->Clear();

    return 0;
}