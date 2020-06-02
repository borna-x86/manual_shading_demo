#include "Light.h"

Light::Light(const glm::vec3 pos, const std::array<float, 3> ambient_intensities,
             const std::array<float, 3> diffuse_intesities,
             const std::array<float, 3> specular_intensities): 
				pos_(pos),
                ambient_intensities_(ambient_intensities),
                diffuse_intesities_(diffuse_intesities),
                specular_intensities_(specular_intensities)
{
}

const glm::vec3& Light::pos() const
{
	return pos_;
}

const std::array<float, 3>& Light::ambient_intensities() const
{
	return ambient_intensities_;
}

const std::array<float, 3>& Light::diffuse_intesities() const
{
	return diffuse_intesities_;
}

const std::array<float, 3>& Light::specular_intensities() const
{
	return specular_intensities_;
}
