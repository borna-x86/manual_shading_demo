#pragma once
#include<glm/glm.hpp>
#include <array>

class Light
{
	glm::vec3 pos_;
	std::array<float, 3> ambient_intensities_;
	std::array<float, 3> diffuse_intesities_;
	std::array<float, 3> specular_intensities_;

public:

	Light(glm::vec3 pos, std::array<float, 3> ambient_intensities,
	      std::array<float, 3> diffuse_intesities,
	      std::array<float, 3> specular_intensities);


	const glm::vec3& pos() const;
	const std::array<float, 3>& ambient_intensities() const;
	const std::array<float, 3>& diffuse_intesities() const;
	const std::array<float, 3>& specular_intensities() const;
};

