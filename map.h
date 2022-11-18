#pragma once
#include <math.h>
#include <vector>
#include "dependente\glfw\glfw3.h"
#include "asteroid.h"

class Map {
private:
	std::vector<Asteroid> asteroids;
	int difficulty = 0;

public:
	int width, height;
	const static double play_zone_radius;
	const static double spawn_zone_radius;

	Map(int width, int height);

	static bool in_radius(double x, double y, double radius);
	static bool in_play_zone(double x, double y);
	static bool in_spawn_zone(double x, double y);
};
