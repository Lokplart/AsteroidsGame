#pragma once
#include <math.h>
#include <vector>
#include <iostream>
#include "dependente\glm\gtc\matrix_transform.hpp"
#include "dependente\glm\gtc\type_ptr.hpp"
#include "persistent.h"
#include "asteroid.h"


class Bullet {
private:
	glm::mat4 bullet_mat;
	glm::vec4 color = glm::vec4(0.8f, 0.0f, 0.0f, 1.0f);

	float bullet_speed = 0.05f;
	int status = 0;

public:
	Bullet(glm::mat4 bullet_mat);
	~Bullet();

	glm::mat4 get_bullet();
	glm::vec4 get_color();

	int get_status();
	// void set_active(bool val);
	int check_collision_circle_square(std::vector<Asteroid> asteroids);

	float x();
	float y();
	double angle();

	int update(std::vector<Asteroid> asteroids);
};