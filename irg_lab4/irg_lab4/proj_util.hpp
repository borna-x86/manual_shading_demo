#pragma once
#include <iostream>
#include <glm/glm.hpp>


inline bool is_face_cw(const glm::vec2 v1, const glm::vec2 v2, const glm::vec2 v3)
{
	const auto b1 = v2 - v1;
	const auto b2 = v3 - v2;
	const auto b3 = v1 - v3;

	const auto p1 = glm::dot(b1, v3);
	const auto p2 = glm::dot(b2, v1);
	const auto p3 = glm::dot(b3, v2);

	return p1 <= 0 && p2 <= 0 && p3 <= 0;
}

inline glm::vec4 vec3_to_vec4(glm::vec3 v3)
{
	return { v3[0], v3[1], v3[2], 1 };
}

inline glm::vec3 transform_vtx(const glm::vec3 vtx, const glm::mat4& look_at, const glm::mat4& frustum)
{
	const auto vtx4 = vec3_to_vec4(vtx);
	const auto transformed4 = vtx4 * look_at * frustum;
	return { transformed4[0] / transformed4[3], transformed4[1] / transformed4[3], transformed4[2]/transformed4[3]};
}

inline glm::vec3 transform_normal(const glm::vec3 normal, const glm::mat4& look_at, const glm::mat4& frustum)
{
	const auto normal_transform = glm::transpose(glm::inverse(look_at));

	const auto normal4 = vec3_to_vec4(normal);
	const auto transformed4 = normal4 * normal_transform;

	return glm::normalize(glm::vec3{ transformed4[0] / transformed4[3],
									 transformed4[1] / transformed4[3],
									 transformed4[2] / transformed4[3] });
}


inline void print_vec3(glm::vec3 v)
{

	std::cout << v[0] << " " << v[1] << " " << v[2];
}


inline glm::mat4 translate_manual(double dx, double dy, double dz)
{
	return {
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ dx, dy, dz, 1 }
	};
}

inline glm::mat4 frustum_manual(const double l, const double r, 
								const double b, const double t,
								const double n, const double f)
{
	return glm::transpose(glm::mat4{
		{2*n/(l-r), 0, 0, 0},
		{0, 2*n/(t-b), 0, 0},
		{(r+l)/(r-l), (t+b)/(t-b), -(f+n)/(f-n), -1},
		{0, 0, -2*f*n/(f-n), 0}
	});
}

inline glm::mat4 look_at_manual(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	const auto vec_z = glm::normalize(center - eye);
	const auto vec_x = glm::normalize(glm::cross(vec_z, up));
	const auto vec_y = glm::normalize(glm::cross(vec_x, vec_z));

	const auto t = translate_manual(-eye[0], -eye[1], -eye[2]);
	const glm::mat4 cord = {
		{ vec_x[0],  vec_y[0], -vec_z[0], 0 },
	{ vec_x[1],  vec_y[1], -vec_z[1], 0 },
	{ vec_x[2],  vec_y[2], -vec_z[2], 0 },
	{ 0,         0,        0,        1 }
	};


	return glm::transpose(t) * glm::transpose(cord);
}