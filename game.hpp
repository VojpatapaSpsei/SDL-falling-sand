#include <stdio.h>
#include <SDL.h>
#include <iostream>
#include <math.h>
#pragma once

class Game
{
public:
    Game();

    ~Game();

    void Init(const char * title, int width, int height);

    void HandleEvents();

    void Update();

    void Render();

    void Clear();

    bool Running();

    static SDL_Renderer * renderer;

    static bool LeftClick;
    static bool RightClick;
    static bool ScrollUp;
    static bool ScrollDown;

private:
    SDL_Event event;
    bool running;

    static SDL_Window * window;



};