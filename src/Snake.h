#ifndef SNAKE_H
#define SNAKE_H
#include <cstdint>
#include <vector>
#include <SDL2/SDL.h>
using namespace std;
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

const int directions[4][2]{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
typedef struct  {
  int x;
  int y;
} Point;
class Snake {
    public:
      explicit Snake(int, int);
      void increaseLength();
      void changeDirection(int);
      void update();
      const vector<Point>& getPath() const; 
    private:
      unsigned int length;
      int direction;
      vector<Point> path;
  };
#endif
