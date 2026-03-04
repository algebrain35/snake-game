#include "Snake.h"
#include <SDL2/SDL_render.h>
#include <iostream>

void printPoint(Point p) {
  cout << "(" << p.x << "," << p.y << ")" << endl;
}
Snake::Snake(int startX, int startY) {
  length = 1;
  direction = 0;
  path.push_back(Point{startX, startY});
}

void Snake::changeDirection(int newDirection) {
  int state = (1 << direction) | (1 << newDirection);

  if(state == 3 || state == 12) {
    cout << "Not changing" << endl;
    return;
  } else {
    direction = newDirection;
  }
}

const vector<Point>& Snake::getPath() const {
  return path;
}

void Snake::increaseLength() {
  length += 2;
}
void Snake::update() {
 Point head = path.front();
 head = {
   head.x + 8 * directions[direction][0],
   head.y + 8 * directions[direction][1]
 };
 path.insert(path.begin(), head);
 while(path.size() > length) {
   path.pop_back();
 }
}

