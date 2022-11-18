#include "map.h"

const double Map::play_zone_radius = 1;
const double Map::spawn_zone_radius = 1.5;

Map::Map(int width, int height) {
	this->width = width;
	this->height = height;	
}


bool Map::in_radius(double x, double y, double radius) {
	return pow(x, 2) + pow(y, 2) <= pow(radius, 2);
}

bool Map::in_play_zone(double x, double y) {
	return Map::in_radius(x, y, Map::play_zone_radius);
}

bool Map::in_spawn_zone(double x, double y) {
	return Map::in_radius(x, y, Map::spawn_zone_radius) && !Map::in_radius(x, y, Map::play_zone_radius);
}