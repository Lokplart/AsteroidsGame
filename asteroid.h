#pragma once
#include <math.h>
#include "dependente\glm\gtc\matrix_transform.hpp"
#include "dependente\glm\gtc\type_ptr.hpp"

class Asteroid {
private:
	glm::mat4 ast_mat;
	glm::vec4 color = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);

	float asteroid_speed = 0.01f;
	int status = 0;

public:
	Asteroid(glm::mat4 ast_mat);
	~Asteroid();

	glm::mat4 get_asteroid();
	void set_asteroid(glm::mat4 ast_mat);

	glm::vec4 get_color();

	int get_status();
	void set_status(int status);

	float get_speed();
	void set_speed(float speed);

	float x();
	float y();
	double angle();

	void update();
};
