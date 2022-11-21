#include "map.h"
#define PI 3.14159265

Map::Map(int width, int height) {
	this->width = width;
	this->height = height;	
	srand(static_cast <unsigned> (time(0)));
}


bool Map::check_collision_circle_triangle(float ast_x, float ast_y, float ship_x, float ship_y) {
	return sqrt(pow(ast_y - ship_y, 2) + pow(ast_x - ship_x, 2)) < 0.05f;
}

void Map::update_asteroids(float delta_time, float ship_x, float ship_y) {
	unsigned int asteroids_size = this->asteroids.size();
	unsigned int i = 0;

	Asteroid::asteroid_speed = Asteroid::asteroid_base_speed * delta_time;
	while (i < asteroids_size) {
		float x = this->asteroids[i].x(), y = this->asteroids[i].y();

		if (this->check_collision_circle_triangle(x ,y, ship_x, ship_y)) {
			this->asteroids[i].set_status(2);
			Persistent::isDestroyed = true;
			std::cout << "You Died :D\nYou got " << Persistent::score << " points this attempt, nice one!\n\nHit 'Enter' and give it another shot!";
		}
		int status = this->asteroids[i].get_status();
		
		if (status == 0 && Persistent::in_play_zone(x, y)) {
			this->asteroids[i].set_status(1);
			glm::mat4 ast_mat = glm::translate(this->asteroids[i].get_asteroid(), glm::vec3(this->asteroids[i].dir_x, this->asteroids[i].dir_y, 0.0f));
			this->asteroids[i++].set_asteroid(ast_mat);
		}
		else {
			if (status == 1 && Persistent::in_spawn_zone(x, y) || status == 2) {
				this->asteroids.erase(this->asteroids.begin() + i);
				asteroids_size--;
			}
			else {
				glm::mat4 ast_mat = glm::translate(this->asteroids[i].get_asteroid(), glm::vec3(this->asteroids[i].dir_x, this->asteroids[i].dir_y, 0.0f));
				this->asteroids[i++].set_asteroid(ast_mat);
			}
		}
	}
}

void Map::spawn_asteroids(float ship_x, float ship_y, double delta_time) {
	//float spawn_point = Map::play_zone_radius + static_cast <float> (rand()) / (static_cast<float>(RAND_MAX / (Map::spawn_zone_radius - Map::play_zone_radius)));

	double current_time = glfwGetTime();
	if (current_time - this->last_spawn_time > this->spawn_rate && this->asteroids.size() < this->wave_size) {
		float spawn_point_x = (10 + static_cast <float> (rand()) / (static_cast<float>(RAND_MAX / (30)))) / 10 - 2;
		float spawn_point_y = (10 + static_cast <float> (rand()) / (static_cast<float>(RAND_MAX / (30)))) / 10 - 2;
		
		//std::cout << spawn_point_x << " " << spawn_point_y << "\n---\n";
		if (spawn_point_x < 0.0f)	{ spawn_point_x -= 2.5; }
		else						{ spawn_point_x += 2.5; }
		if (spawn_point_y < 0.0f)	{ spawn_point_y -= 2.5; }
		else						{ spawn_point_y += 2.5; }

		//std::cout << spawn_point_x << " " << spawn_point_y << "\n________________\n";

		this->last_spawn_time = current_time;
		glm::mat4 ast_mat(1.0f); ast_mat[3][0] = spawn_point_x; ast_mat[3][1] = spawn_point_y;

		float ast_x_speed = (ship_x - spawn_point_x) * Asteroid::asteroid_speed * (float)delta_time;
		float ast_y_speed = (ship_y - spawn_point_y) * Asteroid::asteroid_speed * (float)delta_time;
		//std::cout << ast_x_speed << " " << ast_y_speed << "\n=================\n";

		if (std::abs(ast_x_speed) > Asteroid::asteroid_max_speed || std::abs(ast_y_speed) > Asteroid::asteroid_max_speed) {
			ast_x_speed /= 10;
			ast_y_speed /= 10;
		}
		else if (std::abs(ast_x_speed) < Asteroid::asteroid_min_speed || std::abs(ast_y_speed) < Asteroid::asteroid_min_speed) {
			ast_x_speed *= 10;
			ast_y_speed *= 10;
		}
		
		//std::cout << ship_y << " " << ship_y << " --- " << spawn_point_x << " " << spawn_point_y << "\n====\n";
		this->asteroids.push_back(Asteroid(ast_mat, ast_x_speed, ast_y_speed));
	}
}

void Map::update_game() {
	if (this->asteroids_destoryed == this->wave_size) { 
		if (wave_size != 0) {
			std::cout << "Watch out! It just got harder!\n";
		}
		this->wave_size += ++this->current_wave;
		this->difficulty += (int)(this->current_wave % 5 == 0);
		this->spawn_rate += (float)(this->difficulty / 10.0f);
		Persistent::score += this->asteroids_destoryed;
		std::cout << Persistent::score;
	}
}

void Map::reset() {
	this->difficulty = 1;
	this->wave_size = 9;
	this->current_wave = 0;
	this->asteroids_destoryed = 0;
	this->last_spawn_time = 0.0;
	this->spawn_rate = 1;
	Persistent::score = 0;
}