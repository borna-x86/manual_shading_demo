#include "Mesh.hpp"
#include <map>
#include <set>


void Mesh::compute_planes()
{
	planes_.clear();

	for(auto face : faces_)
	{
		auto face_coords = get_vertices_for_face(face);

		const auto normal1 = (face_coords[1] - face_coords[0]);
		const auto normal2 = (face_coords[2] - face_coords[0]);
		auto normal = glm::cross(normal1, normal2);
		auto plane_coefficient_d = -face_coords[0][0] * normal[0] - face_coords[0][1] * normal[1] - face_coords[0][2] * normal[2];

		planes_.emplace_back(normal[0], normal[1], normal[2], plane_coefficient_d);
	}
}

void Mesh::compute_vtx_normals()
{
	using namespace std;
	using namespace glm;

	//vertex index to vector of face indices that use the vertex
	map<int, set<int>> vertex_to_faces;

	for(auto face_ind = 0u; face_ind < faces_.size(); ++face_ind)
	{
		for(auto vtx_ind = 0; vtx_ind < 3; ++vtx_ind)
		{
			vertex_to_faces[faces_[face_ind][vtx_ind]].insert(face_ind);
		}
	}

	for(auto i = 0u; i < vtxs_.size(); ++i)
	{
		vector<vec3> adjacent_normals;
		for(auto face_index : vertex_to_faces[i])
		{
			adjacent_normals.push_back(glm::normalize(vec3(planes_[face_index][0], planes_[face_index][1], planes_[face_index][2])));
		}

		vec3 vtx_normal{0, 0, 0};
		for(const auto normal : adjacent_normals)
		{
			vtx_normal += glm::normalize(normal);
		}

		vtx_normal = vtx_normal / static_cast<float>(adjacent_normals.size());

		vtx_normals_.push_back(glm::normalize(vtx_normal));
	}

}

Mesh::Mesh(std::vector<glm::vec3> vtxs, std::vector<face> faces) :
	vtxs_(std::move(vtxs)),
	faces_(std::move(faces))
{
	compute_planes();
	compute_vtx_normals();
}

Mesh Mesh::normalize()
{
	glm::vec3 mins(vtxs_[0][0], vtxs_[0][1], vtxs_[0][2]);
	glm::vec3 maxs(vtxs_[0][0], vtxs_[0][1], vtxs_[0][2]);
	// Find minimum and maximum x, y and z coordinates
	for(auto vtx : vtxs_)
	{
		for(auto axis = 0; axis < 3; ++axis)
		{
			if(vtx[axis] < mins[axis])
			{
				mins[axis] = vtx[axis];
			}

			if (vtx[axis] > maxs[axis])
			{
				maxs[axis] = vtx[axis];
			}

		}
	}

	//find center coordinates
	auto center((maxs - mins) / 2.0f);

	//find max range over coordinates
	auto max_range = maxs[0] - mins[0];
	for (auto i = 1; i < 3; ++i)
	{
		if ((maxs[i] - mins[i]) > max_range)
		{
			max_range = maxs[i] - mins[i];
		}
	}

	//update vertices
	for (auto& vtx : vtxs_) {
		for(auto i = 0; i < 3; i++)
		{
			vtx[i] = (vtx[i] - center[i]) * (2 / max_range);
		}
	}


	//recompute plane equations and normals
	compute_planes();
	compute_vtx_normals();

	return *this;
}

std::string Mesh::as_obj()
{
	std::stringstream result;

	for(auto vtx : vtxs_)
	{
		result << "v " 
			<< vtx[0] << ' ' << vtx[1] << ' ' << vtx[2] << '\n';
	}

	for (auto face : faces_)
	{
		result << "f " 
			<< face[0] + 1 << ' ' << face[1] + 1 << ' ' << face[2] + 1 << '\n';
	}

	return result.str();
}

Mesh Mesh::from_stream(std::istream& is)
{
	using namespace std;

	vector<glm::vec3> vtxs;
	vector<face> faces;

	for (string line; getline(is, line);)
	{
		stringstream sstream(line);
		auto entity_type = '\0';

		sstream >> entity_type;

		switch (entity_type)
		{

		case 'v': {

			float x = 0, y = 0, z = 0;
			if (!(sstream >> x >> y >> z))
			{
				throw domain_error("vertex format invalid");
			}

			vtxs.emplace_back(x, y, z);
			break;
		}
		case 'f': {

			int v1_ind = 0, v2_ind = 0, v3_ind;

			if (!(sstream >> v1_ind >> v2_ind >> v3_ind))
			{
				throw domain_error("face format invalid");
			}

			faces.push_back({ v1_ind - 1, v2_ind - 1, v3_ind - 1 });

			break;
		}
		default: {
			break;
		}
		}
	}

	return Mesh(vtxs, faces);
}

std::array<glm::vec3, 3> Mesh::get_vertices_for_face(face face) const
{

	return { vtxs_[face[0]], vtxs_[face[1]], vtxs_[face[2]] };
}

Mesh::Mesh(Mesh&& other) noexcept: vtxs_(std::move(other.vtxs_)),
                                   faces_(std::move(other.faces_)),
                                   planes_(std::move(other.planes_)),
								   vtx_normals_(std::move(other.vtx_normals_))
{
}

Mesh& Mesh::operator=(const Mesh& other)
{
	if (this == &other)
		return *this;
	vtxs_ = other.vtxs_;
	faces_ = other.faces_;
	planes_ = other.planes_;
	vtx_normals_ = other.vtx_normals_;
	return *this;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept
{
	if (this == &other)
		return *this;
	vtxs_ = std::move(other.vtxs_);
	faces_ = std::move(other.faces_);
	planes_ = std::move(other.planes_);
	vtx_normals_ = std::move(other.vtx_normals_);
	return *this;
}

const std::vector<glm::vec3>& Mesh::vtxs() const
{
	return vtxs_;
}

const std::vector<Mesh::face>& Mesh::faces() const
{
	return faces_;
}

const std::vector<glm::vec3>& Mesh::vtx_normals() const
{
	return vtx_normals_;
}

const std::vector<glm::vec4>& Mesh::planes() const
{
	return planes_;
}
