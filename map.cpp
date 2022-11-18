#include "map.h"
#define PI 3.14159265
const double Map::play_zone_radius = 1.5;
const double Map::spawn_zone_radius = 2;

Map::Map(int width, int height) {
	this->width = width;
	this->height = height;	
	srand(static_cast <unsigned> (time(0)));

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

void Map::update_asteroids() {
	unsigned int asteroids_size = this->asteroids.size();
	unsigned int i = 0;
	//cat e ceasul? cat tie nasul hahaha
	double current_frame = glfwGetTime();
	double last_frame = current_frame;
	double delta_time;
	double speed = 0.005;
	while (i < asteroids_size) {
		int status = this->asteroids[i].get_status();
		float x = this->asteroids[i].x(), y = this->asteroids[i].y();
		//scuza-ma pentru gluma anterioara ar trebui sa imi vad de lungul nasului
		current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		last_frame = current_frame;

		std::cout << (float)(delta_time * speed) << "==================================\n";//test 1...2...3 esti gay

		if (status == 0 && Map::in_play_zone(x, y)) {
			this->asteroids[i].set_status(1);
			this->asteroids[i].set_speed((float)(delta_time * speed)); //folosim functia pe care ai abandonat-o cum isi abandoneaza si barbatii negrii copiii
			glm::mat4 ast_mat = glm::translate(this->asteroids[i].get_asteroid(), glm::vec3(this->asteroids[i].dir_x, this->asteroids[i].dir_y, 0.0f));
			this->asteroids[i++].set_asteroid(ast_mat);
		}
		else {
			if (status == 1 && Map::in_spawn_zone(x, y) || status == 2) {
				this->asteroids.erase(this->asteroids.begin() + i);
				asteroids_size--;
			}
			else {
				this->asteroids[i].set_speed((float)(delta_time * speed));//inainte de translateuri ca asa e politicos
				glm::mat4 ast_mat = glm::translate(this->asteroids[i].get_asteroid(), glm::vec3(this->asteroids[i].dir_x, this->asteroids[i].dir_y, 0.0f));
				this->asteroids[i++].set_asteroid(ast_mat);
			}
		}
	}
}

void Map::spawn_asteroids(float ship_x, float ship_y) {
	//float spawn_point = Map::play_zone_radius + static_cast <float> (rand()) / (static_cast<float>(RAND_MAX / (Map::spawn_zone_radius - Map::play_zone_radius)));
	double current_time = glfwGetTime();
	if (current_time - this->last_spawn_time > this->spawn_rate && this->asteroids.size() < this->wave_size) {
		float spawn_point_x = (0 + static_cast <float> (rand()) / (static_cast<float>(RAND_MAX / (2)))) - 1;
		float spawn_point_y = (0 + static_cast <float> (rand()) / (static_cast<float>(RAND_MAX / (2)))) - 1;
		
		
		if (spawn_point_x < 0)	{ spawn_point_x -= 2.5; }
		else					{ spawn_point_x += 2.5; }
		if (spawn_point_y < 0)	{ spawn_point_y -= 2.5; }
		else					{ spawn_point_x += 2.5; }
		
		float delta_time = current_time - this->last_spawn_time; //ti am furat current_time ul ca de ce nu
		float speed = 0.005;
		this->last_spawn_time = current_time;
		glm::mat4 ast_mat(1.0f); 
		ast_mat[3][0] = spawn_point_x; ast_mat[3][1] = spawn_point_y;
		this->asteroids.push_back(Asteroid(ast_mat, (ship_x - spawn_point_x) * 0.002f, (ship_y - spawn_point_y) * 0.002f));//am inlocuit Asteroid::asteroid_speed dar puteam sa pun si delta time * speed acolo,doar sa nu fie prea mica sau prea mare viteza
		std::cout << (float)(delta_time * speed) << "==================================\n";
	}
}

void Map::update_game() {
	if (this->asteroids_destoryed == this->wave_size) { 
		this->wave_size += ++this->current_wave;
		this->difficulty += (int)(this->current_wave % 5 == 0);
		this->spawn_rate += (float)(this->difficulty / 10.0f);
	}
}

