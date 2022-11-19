#pragma once
#include <math.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include "dependente\glfw\glfw3.h"
#include "asteroid.h"



class Map {
private:
	int difficulty = 1;
	int wave_size = 9;
	int current_wave = 0;
	int asteroids_destoryed = 0;
	double last_spawn_time = 0.0;
	double spawn_rate = 1;

public:
	int width, height;
	const static double play_zone_radius;
	const static double spawn_zone_radius;
	static clock_t current_time;
	std::vector<Asteroid> asteroids;

	Map(int width, int height);

	static bool in_radius(double x, double y, double radius);
	static bool in_play_zone(double x, double y);
	static bool in_spawn_zone(double x, double y);

	void spawn_asteroids(float ship_x, float ship_y, double delta_time);

	void update_asteroids(float delta_time);
	void update_game();
};
