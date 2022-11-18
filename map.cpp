#include "map.h"

const double Map::play_zone_radius = 1.5;
const double Map::spawn_zone_radius = 2;

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

void Map::update() {
	unsigned int asteroids_size = this->asteroids.size();
	unsigned int i = 0;

	while (i < asteroids_size) {
		glm::mat4 ast_mat = glm::translate(this->asteroids[i].get_asteroid(), glm::vec3(0.0f, this->asteroids[i].get_speed(), 0.0f));
		int status = this->asteroids[i].get_status(); 
		float x = ast_mat[3][0], y = ast_mat[3][1];
		if (status == 0 && Map::in_play_zone(x, y)) {
			this->asteroids[i].set_status(1);
		}
		else {
			if (status == 1 && Map::in_spawn_zone(x, y)) {
				this->asteroids.erase(this->asteroids.begin() + i);
			}
			else {
				this->asteroids[i++].set_asteroid(ast_mat);
			}
		}
		
		
	}
}