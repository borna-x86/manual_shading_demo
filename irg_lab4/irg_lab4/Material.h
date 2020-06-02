#pragma once
#include <array>

class Material
{
	std::array<float, 3> ambient_emission_;
	std::array<float, 3> diffuse_emission_;
	std::array<float, 3> specular_emission_;

public:


	Material(std::array<float, 3> ambient_emission, std::array<float, 3> diffuse_emission,
	         std::array<float, 3> specular_emission);


	const std::array<float, 3>& ambient_emission() const;
	const std::array<float, 3>& diffuse_emission() const;
	const std::array<float, 3>& specular_emission() const;

	
};

