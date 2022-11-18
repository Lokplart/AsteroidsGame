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

void Bullet::update() {
	this->bullet_mat = glm::translate(this->bullet_mat, glm::vec3(0.0f, this->bullet_speed, 0.0f));
	if (this->status == 0 && Map::in_play_zone(this->x(), this->y())) {
		this->status = 1; 
	}
	else if (this->status == 1 && Map::in_spawn_zone(this->x(), this->y())) {
		this->status = 2;
	}
}

Bullet::~Bullet() {}
