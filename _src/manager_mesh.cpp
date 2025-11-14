#include "glm/ext/vector_float3.hpp"
#include <manager_mesh.h>
#include <memory>
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>


std::shared_ptr<MeshData> ManagerMesh::load_mesh_from_file(const std::string& name, const char *file)
{
    auto mesh = std::make_shared<MeshData>();

    tinyobj::attrib_t attributes;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warning;
	std::string error;

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> text_coords;
    std::vector<glm::vec3> normals;

	if (!tinyobj::LoadObj(
		&attributes,
		&shapes,
		&materials,
		&warning,
		&error,
		file)
	)
	{
		throw std::runtime_error("ast::assets::loadOBJFile: Error: " + warning + error);
	}

	for (const auto &shape: shapes)
	{
		for (const auto &index: shape.mesh.indices)
		{
			glm::vec3 position{
				attributes.vertices[3 * index.vertex_index + 0],
				attributes.vertices[3 * index.vertex_index + 1],
				attributes.vertices[3 * index.vertex_index + 2]
			};
			positions.push_back(position);

			if (index.texcoord_index >= 0)
			{
				glm::vec2 text_coord
			    {
					attributes.texcoords[2 * index.texcoord_index + 0],
					attributes.texcoords[2 * index.texcoord_index + 1]
				};
				text_coords.push_back(text_coord);
			}

			if (index.normal_index >= 0)
		    {
				glm::vec3 normal
			    {
					attributes.normals[3 * index.normal_index + 0],
					attributes.normals[3 * index.normal_index + 1],
					attributes.normals[3 * index.normal_index + 2]

				};
				normals.push_back(normal);
			}
		}
	}

	glGenVertexArrays(1, &mesh->VAO);
	glGenBuffers(3, mesh->VBO);

	glBindVertexArray(mesh->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), positions.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(0);

	// Normals Attribute
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(1);

	// Tex. Coords. Attribute
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, text_coords.size() * sizeof(glm::vec2), text_coords.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	mesh->vertex_count = positions.size();

    meshes[name] = mesh;
    return mesh;

}

std::shared_ptr<MeshData> ManagerMesh::load_mesh_data(const std::string& name, const float *vertices, int vertex_count, const unsigned int *indices, int index_count)
{
    auto mesh = std::make_shared<MeshData>();
    mesh->vertex_count = vertex_count;
    mesh->index_count = index_count;

    glGenVertexArrays(1, &mesh->VAO);
    glGenBuffers(1, &mesh->VBO[0]);
    glGenBuffers(1, &mesh->EBO);

    glBindVertexArray(mesh->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(float), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    meshes[name] = mesh;
    return mesh;
}

std::shared_ptr<MeshData> ManagerMesh::get_mesh_data(const std::string& name)
{
    return meshes.at(name);
}
