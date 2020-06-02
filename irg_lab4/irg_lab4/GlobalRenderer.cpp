#include "GlobalRenderer.hpp"

GlobalRenderer& GlobalRenderer::instance()
{
	static GlobalRenderer instance;
	return instance;
}
