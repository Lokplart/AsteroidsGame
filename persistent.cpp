#include "persistent.h"

const double Persistent::play_zone_radius = 1.5;
const double Persistent::spawn_zone_radius = 2;
clock_t Persistent::current_time = clock();
bool Persistent::isDestroyed = false;
int Persistent::score = 0;

bool Persistent::in_radius(double x, double y, double radius) {
	return pow(x, 2) + pow(y, 2) <= pow(radius, 2);
}

bool Persistent::in_play_zone(double x, double y) {
	return Persistent::in_radius(x, y, Persistent::play_zone_radius);
}

bool Persistent::in_spawn_zone(double x, double y) {
	return Persistent::in_radius(x, y, Persistent::spawn_zone_radius) && !Persistent::in_radius(x, y, Persistent::play_zone_radius);
}