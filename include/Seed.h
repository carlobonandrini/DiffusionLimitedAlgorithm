#pragma once
#include<vector>
#include<chrono>
#include<random>

struct Point
{
	int x, y;
};

class Seed
{
public:
	Seed() : x(0), y(0) {}
	Seed(int x, int y) : x(x), y(y) {}

	bool isCompleted(std::vector<Point> tree);

	Point point() { return Point{ x, y }; }

	void move(int winSize);
private:
	int x, y;
};

