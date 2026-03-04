#include "Game.h"
#include <random>

Game::Game() : g_pWindow(nullptr), g_pRenderer(nullptr), running(false) 
{
  int screenWidth = WIDTH;
  int screenHeight = HEIGHT;
  pixelMap = make_unique<unique_ptr<int[]>[]>(WIDTH);
  for(size_t i = 0; i < WIDTH; i++) {
    pixelMap[i] = make_unique<int[]>(HEIGHT);
  }
}

bool Game::init(
    const char* title,
    int xpos,
    int ypos,
    int width,
    int height,
    int flags) 
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
    return -1;
  }
  if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    g_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags); 

    if(g_pWindow != 0) {
      g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
      if(g_pRenderer != 0) {
        SDL_SetRenderDrawColor(g_pRenderer,
        0, 0,255, 255);
      } else {
        return false;
      }
    } else {
      return false;
    }
  } else {
    return false;
  }
  running = true;
  return true;
}
int Game::handleEvents() {
  SDL_Event event;
  if(SDL_PollEvent(&event))
  {
    switch(event.type) {
      case SDL_QUIT:
        running = false;
        break;
      case SDL_KEYDOWN:
        switch(event.key.keysym.sym) {
          case SDLK_UP:
            return 0;
          case SDLK_DOWN:
            return 1;
          case SDLK_LEFT:
            return 2;
          case SDLK_RIGHT:
            return 3;
          default:
            break;

        }
      default:
      break;
    }
  }
  return -1;
}

void Game::render() {
  SDL_RenderPresent(g_pRenderer);
}

void Game::clear() {
  SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 255, 255);
  SDL_RenderClear(g_pRenderer);
}

void Game::clean()
{
  std::cout << "cleaning game\n";
  SDL_DestroyWindow(g_pWindow);
  SDL_DestroyRenderer(g_pRenderer);
  SDL_Quit();
}

bool Game::is_running() {
  return running;
}

void Game::renderSnake(const Snake& s) {
  for(auto& p: s.getPath()) {
    SDL_Rect pixel = {p.x, p.y, 8, 8};
    SDL_SetRenderDrawColor(g_pRenderer, 255, 0, 0, 255);
    SDL_RenderFillRect(g_pRenderer, &pixel);
  }
}

bool Game::foodEaten() {
  return pixelMap[foodPos.x][foodPos.y] == 0;
}

void Game::spawnFood() {
  int x, y;
  if(foodEaten()) {
    srand(static_cast<int>(time(NULL)));
  
    x = rand() % (WIDTH - 2); 
    y = rand() % (HEIGHT - 2);

    pixelMap[x][y] = -1;
    foodPos = Point{x, y};
  } else {
    x = foodPos.x;
    y = foodPos.y;
  }


  SDL_Rect food = {x, y, 8, 8};
  SDL_RenderFillRect(g_pRenderer, &food);
}

bool Game::checkCollision(Snake& s) {
  vector<Point> path = s.getPath();
  return (abs(path[0].x - foodPos.x) < 8) && (abs(path[0].y - foodPos.y) < 8);
}

bool Game::checkTerminalState(Snake& s) {
  //check for wall collision
  vector<Point> path = s.getPath();
  // initialize width, height members properly !!!!
  if(path[0].x < 0 || path[0].x > WIDTH || path[0].y < 0 || path[0].y > HEIGHT) {
    //cout << "(" << path[0].x << "," << path[0].y << ")" << endl;
    return true;
  }

  if(path.size() > 1) {
    for(int i = 1; i < path.size(); i++) {
      if(path[i].x == path[0].x && path[i].y == path[0].y) {
        return true;
      }
    }
    return false;
  }

  return false;
}

void Game::handleCollision(Snake& s) {
  if(checkCollision(s)) {
    s.increaseLength();
    pixelMap[foodPos.x][foodPos.y] = 0;

  }

}


int main() {
  Game g_game;
  bool success = g_game.init("First game", X_POS, Y_POS, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

  if(!success) return 1;
  int x = (WIDTH - 1) / 2;
  int y = (HEIGHT - 1) / 2;

  Snake s{x, y};
  while(g_game.is_running()) {
    int direction = g_game.handleEvents();
    if(direction != -1) {

      s.changeDirection(direction);
    }
    s.update();

    g_game.clear();
    if(g_game.checkTerminalState(s)) {
      g_game.clean();
      exit(0);
    }
    vector<Point> path = s.getPath();  
    cout << "(" << path[0].x << "," << path[0].y << ")" << endl;
    cout << g_game.checkTerminalState(s) << endl;

    g_game.handleCollision(s);
    g_game.renderSnake(s);
    g_game.spawnFood();
    g_game.render();
    SDL_Delay(70);
  }
  g_game.clean();


}
