#include "Seed.h"
#include <iostream>

bool Seed::isCompleted(std::vector<Point> tree) {
  bool completed = false;
  for (Point p : tree) {
    int sqDistance = (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y);
    if (sqDistance == 1 || sqDistance == 2) {
      completed = true;
      break;
    }
  }

  return completed;
}

void Seed::move(int winSize) {
  std::mt19937 rng;
  std::uniform_int_distribution<int> int_distr(0, 1); // 8 is comprehended
  rng.seed(
      std::chrono::high_resolution_clock::now().time_since_epoch().count());
  int dx, dy;
  do {
    dx = int_distr(rng) == 0 ? -1 : 1;
    dy = int_distr(rng) == 0 ? -1 : 1;
  } while (x + dx < 0 || x + dx > winSize || y + dy < 0 || y + dy > winSize);

  x += dx;
  y += dy;
}
