#pragma once
#include <math.h>
#include "dependente\glm\gtc\matrix_transform.hpp"
#include "dependente\glm\gtc\type_ptr.hpp"

class Asteroid {
private:
	glm::mat4 ast_mat;
	glm::vec4 color = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);

	int status = 0;

public:
	static float asteroid_speed;
	static float asteroid_max_speed;
	float dir_x = 0.0f;
	float dir_y = 0.0f;
	Asteroid(glm::mat4 ast_mat, float dir_x, float dir_y);
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
