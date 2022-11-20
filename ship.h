#pragma once
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "bullet.h"
#include "dependente\glm\gtc\matrix_transform.hpp"
#include "dependente\glm\gtc\type_ptr.hpp"

class Ship {
private:
	unsigned int current_active_bullets = 0;
	glm::mat4 ship_mat = glm::mat4(1.0f);
	glm::vec4 color = glm::vec4(0.8f, 0.0f, 0.0f, 1.0f);

public:
	std::vector<Bullet> bullets;
	Ship();
	~Ship();

	glm::mat4 get_ship();
	glm::vec4 get_color();

	float x();
	float y();
	double angle();

	Bullet get_available_bullet();

	

	void move_forward(float speed);
	void move_backwards(float speed);
	void rotate_left(float angle);
	void rotate_right(float angle);
	void shoot();

	void update();
};
