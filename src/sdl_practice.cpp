#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

#define WIDTH 640
#define HEIGHT 480
#define X_POS SDL_WINDOWPOS_CENTERED
#define Y_POS SDL_WINDOWPOS_CENTERED

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

int main() {
  if(SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
    g_pWindow = SDL_CreateWindow("Window", X_POS, Y_POS, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  }

  if(g_pWindow != 0) {
    g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
  } else {
    return 1;
  }

  SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);
  SDL_RenderClear(g_pRenderer);

  SDL_RenderPresent(g_pRenderer);
  SDL_Delay(5000);

  SDL_Quit();

  return 0;

}
