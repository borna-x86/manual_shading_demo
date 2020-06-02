#pragma once
#include<vector>
#include<array>
#include<sstream>
#include<glm/glm.hpp>

class Mesh
{
	typedef std::array<int, 3> face;

	std::vector<glm::vec3> vtxs_;
	std::vector<face> faces_;
	std::vector<glm::vec4> planes_;
	std::vector<glm::vec3> vtx_normals_;

	void compute_planes();
	void compute_vtx_normals();
	

public:
	Mesh(std::vector<glm::vec3> vtxs, std::vector<face> faces);
	~Mesh() = default;

	Mesh normalize();

	std::string as_obj();
	static Mesh from_stream(std::istream& is);
	std::array<glm::vec3, 3> get_vertices_for_face(face face) const;

	//Operators
	Mesh(const Mesh& other) = default;
	Mesh(Mesh&& other) noexcept;
	Mesh& operator=(const Mesh& other);
	Mesh& operator=(Mesh&& other) noexcept;

	//Getters
	const std::vector<glm::vec3>& vtxs() const;

	const std::vector<face>& faces() const;

	const std::vector<glm::vec3>& vtx_normals() const;

	const std::vector<glm::vec4>& planes() const;
};


