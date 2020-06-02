#include "Material.h"


Material::Material(const std::array<float, 3> ambient_emission, const std::array<float, 3> diffuse_emission,
                   const std::array<float, 3> specular_emission): 
		ambient_emission_(ambient_emission),
        diffuse_emission_(diffuse_emission),
        specular_emission_(specular_emission)
{
}

const std::array<float, 3>& Material::ambient_emission() const
{
	return ambient_emission_;
}

const std::array<float, 3>& Material::diffuse_emission() const
{
	return diffuse_emission_;
}

const std::array<float, 3>& Material::specular_emission() const
{
	return specular_emission_;
}
