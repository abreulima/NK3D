#include <manager_mesh.h>
#include <memory>
#include <GL/glew.h>

std::shared_ptr<MeshData> ManagerMesh::load_mesh_data(const std::string& name, const float *vertices, int vertex_count, const unsigned int *indices, int index_count)
{
    auto mesh = std::make_shared<MeshData>();
    mesh->vertex_count = vertex_count;
    mesh->index_count = index_count;

    glGenVertexArrays(1, &mesh->VAO);
    glGenBuffers(1, &mesh->VBO);
    glGenBuffers(1, &mesh->EBO);

    glBindVertexArray(mesh->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
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
