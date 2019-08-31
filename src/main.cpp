#include "Seed.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

void CalculateSeed();

static const int winSize = 800;
static std::vector<Seed> seeds;
static std::vector<Point> tree;
static bool seeding = true;

int main() {
  sf::RenderWindow window(sf::VideoMode(winSize, winSize),
                          "DIffusion Limited Visualization");

  sf::Image image;
  image.create(winSize, winSize, sf::Color(0, 0, 0));
  sf::Texture texture;
  sf::Sprite sprite;

  std::mt19937 rng;
  std::uniform_int_distribution<int> int_distributon(0, winSize);
  rng.seed(
      std::chrono::high_resolution_clock::now().time_since_epoch().count());

  Point startP{winSize / 2, winSize / 2};
  tree.push_back(startP);
  int maxSeeds = winSize * winSize / 9;
  seeds.reserve(maxSeeds);

  for (int i = 0; i < maxSeeds; i++)
    seeds.emplace_back(Seed(int_distributon(rng), int_distributon(rng)));

  std::thread worker(CalculateSeed);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
        seeding = false;
        worker.join();
      }
    }

    if (seeds.size() == 0) {
      seeding = false;
      worker.join();
    }

    for (int i = 0; i < tree.size(); i++) {
      image.setPixel(tree[i].x, tree[i].y, sf::Color(255, 255, 255));
    }
    texture.loadFromImage(image);
    sprite.setTexture(texture);

    window.clear();
    window.draw(sprite);
    window.display();
  }
}

void CalculateSeed() {
  auto start = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float> dt;

  while (seeds.size() > 0 && seeding) {
    for (auto i = seeds.begin(); i != seeds.end();) {
      // If the seed is near the tree branches, add it to tree and remove from
      // seed
      if (i->isCompleted(tree)) {
        tree.push_back(i->point());
        i = seeds.erase(i);
      } else {
        // If is not then get next update position
        i->move(winSize);
        ++i;
      }
    }
  }

  auto end = std::chrono::high_resolution_clock::now();
  dt = end - start;
  std::cout << "Seeding operation succedeed!" << std::endl;
  std::cout << "Time took: " << dt.count() * 1000.f << std::endl;
}
