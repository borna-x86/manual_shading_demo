#include "GlobalRenderer.hpp"
#include "Mesh.hpp"
#include <iostream>
#include "Scene.h"
#include "Renderer.hpp"
#include <GL/glut.h>
#include <fstream>



int main(int argc, char *argv[])
{	
	std::string fname;
	
	if (argc == 2) {
		fname = argv[1];
	}
	else {
		fname = "teddy.obj";
	}

	auto obj_stream = std::ifstream(fname);

	const auto object_normalized = Mesh::from_stream(obj_stream).normalize();
	const auto renderer = GlobalRenderer::instance().renderer;
	renderer.init(argc, argv, "Manual Shading & OpenGL Legacy");
	Renderer::set_scene({ object_normalized,{ 3, 4, 1 },{ 0, 0, 0 },{ 0, 1, 0 } });
	glutMainLoop();
	return 0;
}
