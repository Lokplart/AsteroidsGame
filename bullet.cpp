#include "bullet.h"
#define PI 3.14159265

Bullet::Bullet(glm::mat4 bullet_mat) { this->bullet_mat = bullet_mat; }

glm::mat4 Bullet::get_bullet() { return this->bullet_mat; }
glm::vec4 Bullet::get_color()  { return this->color;      }

float Bullet::x() { return this->bullet_mat[3][0]; }
float Bullet::y() { return this->bullet_mat[3][1]; }
double Bullet::angle() {
	if ((acos(this->bullet_mat[0][0])) * 180.0 / PI < 0) {
		return -((asin(this->bullet_mat[0][1])) * 180.0 / PI);
	}
	else {
		return  ((asin(this->bullet_mat[0][1])) * 180.0 / PI);
	}
}

int Bullet::get_status() { return this->status; }

int Bullet::check_collision_circle_square(std::vector<Asteroid> asteroids) {
	for (unsigned int i = 0; i < asteroids.size(); i++) {
		if (sqrt(pow(asteroids[i].y() - this->y(), 2) + pow(asteroids[i].x() - this->x(), 2)) < 0.05f) {
			return i;
		}
	}
	return -1;
};

int Bullet::update(std::vector<Asteroid> asteroids) {
	this->bullet_mat = glm::translate(this->bullet_mat, glm::vec3(0.0f, this->bullet_speed, 0.0f));
	if (this->status == 0 && Persistent::in_play_zone(this->x(), this->y())) {
		this->status = 1; 
		return -1;
	}
	else {
		int ast_index = this->check_collision_circle_square(asteroids);
		if (this->status == 1 && Persistent::in_spawn_zone(this->x(), this->y())) {
			this->status = 2;
		}
		else if (ast_index != -1) {
			this->status = 2;
			return ast_index;
		}
		return -1;
	}
}



Bullet::~Bullet() {}
