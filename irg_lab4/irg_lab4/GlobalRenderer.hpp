#pragma once
#include "Renderer.hpp"
#include <memory>

class GlobalRenderer
{
	GlobalRenderer() = default;
	

public:
	static GlobalRenderer & instance();
	Renderer renderer;
};

