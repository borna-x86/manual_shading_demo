#pragma once
#include "Mesh.hpp"
#include <glm/glm.hpp>

class Scene
{
	Mesh object_;
	glm::vec3 eye_;
	glm::vec3 center_;
	glm::vec3 up_;
	float z_near_;
	float z_far_;
	float near_w_;
	float near_h_;


	void set_eye(const glm::vec3& eye);
	
public:

	Scene(Mesh object, 
		glm::vec3 eye, glm::vec3 center, glm::vec3 up, 
		float z_near = 1.0f, float z_far = 100.0f, float near_w = 1.0f, float near_h = 1.0f);
	Scene();

	static Scene empty_scene();
	void rotate_eye(double deg);

	const Mesh& object() const;
	const glm::vec3& eye() const;
	const glm::vec3& center() const;
	const glm::vec3& up() const;
	float z_near() const;
	float z_far() const;
	float near_w() const;
	float near_h() const;
};

