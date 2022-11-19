#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "dependente\glew\glew.h"
#include "dependente\glfw\glfw3.h"
#include "dependente\glm\glm.hpp"
#include "dependente\glm\gtc\matrix_transform.hpp"
#include "dependente\glm\gtc\type_ptr.hpp"
#include "shader.hpp"
#include "map.h"
#include "ship.h"

GLFWwindow* window;
Map map = Map(1024, 768);
Ship ship = Ship();


float get_delta_time() {
	float current_time = glfwGetTime();
	float delta_time = current_time - Map::current_time;
	Map::current_time = current_time;
	return delta_time;
}


float rotation_speed = 3.0f;
float movement_speed = 0.005f;
double shot_time = 0;
void handle_input() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		ship.move_forward(movement_speed);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		ship.move_backwards(movement_speed);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		ship.rotate_left(rotation_speed);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		ship.rotate_right(rotation_speed);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		double current_time = glfwGetTime();
		if (current_time - shot_time > 0.5) {
			ship.shoot();
			shot_time = current_time;
		}
	}
}

void draw_object(glm::mat4 object, glm::vec4 color, GLuint shader, GLuint vao, int indices) {
	glUseProgram(shader);
	glUniformMatrix4fv(glGetUniformLocation(shader, "transform"), 1, GL_FALSE, glm::value_ptr(object));
	glUniform4fv(glGetUniformLocation(shader, "color"), 1, glm::value_ptr(color));
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, 0);
}

void window_callback(GLFWwindow* window, int new_width, int new_height) { glViewport(0, 0, new_width, new_height); }

int main(void) {
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}
	window = glfwCreateWindow(map.width, map.height, "3D demo", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, map.width, map.height);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	GLuint ship_shader = LoadShaders("ship.ver", "ship.frg");
	float ship_vertices[] = {
		0.0f,   0.05f, 0.0f,
		0.03f,  0.0f,  0.0f,
		-0.03f,  0.0f,  0.0f,
	};
	unsigned int ship_indices[] = {
		0, 1, 2
	};
	GLuint ship_vbo, ship_vao, ship_ibo;
	glGenVertexArrays(1, &ship_vao); glGenBuffers(1, &ship_vbo); glGenBuffers(1, &ship_ibo); glBindVertexArray(ship_vao);
	glBindBuffer(GL_ARRAY_BUFFER, ship_vbo); glBufferData(GL_ARRAY_BUFFER, sizeof(ship_vertices), ship_vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ship_ibo); glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ship_indices), ship_indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); glEnableVertexAttribArray(0); glBindVertexArray(0);

	GLuint bullet_shader = LoadShaders("bullet.ver", "bullet.frg");
	float bullet_vertices[] = {
		-0.005f, 0.04f, 0.0f, // top left
		 0.005f, 0.04f, 0.0f, // top right
		-0.005f, 0.0f,  0.0f, // bot left
		 0.005f, 0.0f,  0.0f  // bot right
	};
	unsigned int bullet_indices[] = {
		0, 1, 2,
		1, 2, 3
	};
	GLuint bullet_vbo, bullet_vao, bullet_ibo;
	glGenVertexArrays(1, &bullet_vao); glGenBuffers(1, &bullet_vbo); glGenBuffers(1, &bullet_ibo); glBindVertexArray(bullet_vao);
	glBindBuffer(GL_ARRAY_BUFFER, bullet_vbo); glBufferData(GL_ARRAY_BUFFER, sizeof(bullet_vertices), bullet_vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bullet_ibo); glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bullet_indices), bullet_indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); glEnableVertexAttribArray(0); glBindVertexArray(0);

	GLuint asteroid_shader = LoadShaders("asteroid.ver", "asteroid.frg");
	float asteroid_vertices[] = {
		 0.0f,    0.0f,    0.0f, 
		-0.05f,   0.0f,    0.0f,
		-0.033f,   0.0373f, 0.0f,
		 0.0f,    0.05f,   0.0f,
		 0.033f,   0.0373f, 0.0f,
		 0.05f,   0.0f,    0.0f,
		 0.033f,  -0.0373f, 0.0f,
		 0.0f,   -0.05f,   0.0f,
		 -0.033f, -0.0373f, 0.0f,
	};
	unsigned int asteroid_indices[] = {
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 5,
		0, 5, 6,
		0, 6, 7,
		0, 7, 8,
		0, 8, 1
	};
	GLuint asteroid_vbo, asteroid_vao, asteroid_ibo;
	glGenVertexArrays(1, &asteroid_vao); glGenBuffers(1, &asteroid_vbo); glGenBuffers(1, &asteroid_ibo); glBindVertexArray(asteroid_vao);
	glBindBuffer(GL_ARRAY_BUFFER, asteroid_vbo); glBufferData(GL_ARRAY_BUFFER, sizeof(asteroid_vertices), asteroid_vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, asteroid_ibo); glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(asteroid_indices), asteroid_indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); glEnableVertexAttribArray(0); glBindVertexArray(0);

	glfwSetFramebufferSizeCallback(window, window_callback);



	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window); glfwPollEvents(); glClear(GL_COLOR_BUFFER_BIT); handle_input();

		float delta_time = get_delta_time();

		draw_object(ship.get_ship(), ship.get_color(), ship_shader, ship_vao, 3); glBindVertexArray(0);
		ship.update();

		//std::cout << ship.bullets.size() << "\n";
		for (unsigned int i = 0; i < ship.bullets.size(); i++) {
			draw_object(ship.bullets[i].get_bullet(), ship.bullets[i].get_color(), bullet_shader, bullet_vao, 6);
			ship.bullets[i].update();
		}
		glBindVertexArray(0);
		map.update_game();
		map.spawn_asteroids(ship.x(), ship.y(), delta_time);
		//std::cout << ship.angle() << "\n";
		for (unsigned int i = 0; i < map.asteroids.size(); i++) {
//			glm::mat4 ast_mat = map.asteroids[i].get_asteroid();
//			std::cout << ast_mat[3][0] << " " << ast_mat[3][1] << "\n---\n";
//			std::cout << map.asteroids[i].dir_x << " " << map.asteroids[i].dir_y << "\n---\n";
			draw_object(map.asteroids[i].get_asteroid(), map.asteroids[i].get_color(), asteroid_shader, asteroid_vao, 24);
		}
		glBindVertexArray(0);
		map.update_asteroids(delta_time);
	}

	glDeleteBuffers(1, &ship_vbo);   glDeleteBuffers(1, &ship_ibo);   glDeleteVertexArrays(1, &ship_vao);   glDeleteProgram(ship_shader);
	glDeleteBuffers(1, &bullet_vbo); glDeleteBuffers(1, &bullet_ibo); glDeleteVertexArrays(1, &bullet_vao); glDeleteProgram(bullet_shader);
	glfwTerminate(); 
	return 0;
}