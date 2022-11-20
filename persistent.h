#pragma once
#include <ctime>
#include <math.h>

class Persistent {
public:
	const static double play_zone_radius;
	const static double spawn_zone_radius;
	static clock_t current_time;
	static bool isDestroyed;
	static int score;

	static bool in_radius(double x, double y, double radius);
	static bool in_play_zone(double x, double y);
	static bool in_spawn_zone(double x, double y);
};