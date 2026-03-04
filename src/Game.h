#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <random>
#include "Snake.h"
#include <memory>

#define WIDTH 640
#define HEIGHT 480
#define X_POS SDL_WINDOWPOS_CENTERED
#define Y_POS SDL_WINDOWPOS_CENTERED

class Game {
  public:
    Game();
    bool init(const char*, int, int, int, int, int);
    bool is_running();
    void render();
    void update();
    int handleEvents();
    void clean();
    void clear();
    void renderSnake(const Snake& s);
    bool foodEaten();
    void spawnFood();
    bool checkCollision(Snake& s);
    void handleCollision(Snake& s);
    bool checkTerminalState(Snake& s);
    SDL_Renderer* g_pRenderer;
  private:
    bool running;
    SDL_Window* g_pWindow;
    int screenWidth, screenHeight;
    unique_ptr<unique_ptr<int[]>[]> pixelMap;
    Point foodPos;
};
#endif
