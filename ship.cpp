#include "ship.h"
#define PI 3.14159265

Ship::Ship() { this->ship_mat = glm::translate(this->ship_mat, glm::vec3(0.0f, 0.0f, 0.0f)); }

glm::mat4 Ship::get_ship()  { return this->ship_mat; }
glm::vec4 Ship::get_color() { return this->color;    }

float Ship::x() { return this->ship_mat[3][0]; }
float Ship::y() { return this->ship_mat[3][1]; }
double Ship::angle() {
	if ((acos(this->ship_mat[0][0])) * 180.0 / PI < 0) { 
		return -((asin(this->ship_mat[0][1])) * 180.0 / PI); 
	}
	else { 
		return  ((asin(this->ship_mat[0][1])) * 180.0 / PI);  
	}
}

void Ship::move_forward(float speed)   { this->ship_mat = glm::translate(this->ship_mat, glm::vec3(0.0f,  speed, 0.0f));    }
void Ship::move_backwards(float speed) { this->ship_mat = glm::translate(this->ship_mat, glm::vec3(0.0f, -speed, 0.0f));    }
void Ship::rotate_left(float angle)    { this->ship_mat = glm::rotate(this->ship_mat,  angle, glm::vec3(0.0f, 0.0f, 1.0f)); }
void Ship::rotate_right(float angle)   { this->ship_mat = glm::rotate(this->ship_mat, -angle, glm::vec3(0.0f, 0.0f, 1.0f)); }

void Ship::shoot() { this->bullets.push_back(Bullet(this->get_ship())); }

void Ship::update() {
	int bullets_size = this->bullets.size();
	int i = 0;
	while (i < bullets_size) {
		if (this->bullets[i].get_status() == 2) {
			this->bullets.erase(this->bullets.begin() + i);
			bullets_size--;
		}
		else {
			i++;
		}
	}
}

Ship::~Ship() {};