#include "asteroid.h"
#define PI 3.14159265


float Asteroid::asteroid_speed = 0.05f;

Asteroid::Asteroid(glm::mat4 ast_mat, float dir_x, float dir_y) {
	this->ast_mat = ast_mat;
	this->dir_x = dir_x;
	this->dir_y = dir_y;
}

glm::mat4 Asteroid::get_asteroid() {
	return this->ast_mat;
}
void Asteroid::set_asteroid(glm::mat4 ast_mat) {
	this->ast_mat = ast_mat;
	
}


glm::vec4 Asteroid::get_color() {
	return this->color;
}

int Asteroid::get_status() {
	return this->status;
}
void Asteroid::set_status(int status) {
	this->status = status;
}

float Asteroid::get_speed() {
	return this->asteroid_speed;
}

//aici luam direct speed fara Asteroid::asteroid_speed
void Asteroid::set_speed(float speed) {
	this->asteroid_speed = speed;
}


float Asteroid::x() { return this->ast_mat[3][0]; }
float Asteroid::y() { return this->ast_mat[3][1]; }
double Asteroid::angle() {
	if ((acos(this->ast_mat[0][0])) * 180.0 / PI < 0) {
		return -((asin(this->ast_mat[0][1])) * 180.0 / PI);
	}
	else {
		return  ((asin(this->ast_mat[0][1])) * 180.0 / PI);
	}
}

void update() {

}

Asteroid::~Asteroid() {}