#pragma once
#include <math.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "dependente\glfw\glfw3.h"
#include "persistent.h"
#include "asteroid.h"
#include "ship.h"

class Map {
private:
	int difficulty = 1;
	int wave_size = 0;
	int current_wave = 0;
	double last_spawn_time = 0.0;
	double spawn_rate = 1;

public:
	int width, height;
	int asteroids_destoryed = 0;

	std::vector<Asteroid> asteroids;

	Map(int width, int height);

	bool check_collision_circle_triangle(float ast_x, float ast_y, float ship_x, float ship_y);

	void spawn_asteroids(float ship_x, float ship_y, double delta_time);

	void update_asteroids(float delta_time, float ship_x, float ship_y);
	void update_game();
	void reset();
};
