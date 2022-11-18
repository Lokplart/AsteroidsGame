#pragma once
#include <math.h>
#include "dependente\glm\gtc\matrix_transform.hpp"
#include "dependente\glm\gtc\type_ptr.hpp"
#include "map.h"

class Asteroid {
private:
	glm::mat4 ast_mat;
	glm::vec4 color = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);

	int state = 0;

public:
	Asteroid(glm::mat4 ast_mat);
	~Asteroid();

	glm::mat4 get_asteroid();
	glm::vec4 get_color();

	int get_state();

	void update();
};
