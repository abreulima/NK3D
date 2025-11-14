#ifndef MANAGER_MESH_H
#define MANAGER_MESH_H

#include <unordered_map>
#include <string>
#include <memory>

struct MeshData
{
    unsigned int VAO;
    unsigned int VBO[3];
    unsigned int EBO;
    int vertex_count;
    int index_count;
};

class ManagerMesh
{
    public:
        std::unordered_map<std::string, std::shared_ptr<MeshData>> meshes;
        std::shared_ptr<MeshData> load_mesh_data(const std::string& name, const float *vertices, int vertex_count, const unsigned int *index, int index_count);
        std::shared_ptr<MeshData> load_mesh_from_file(const std::string& name, const char *file);
        std::shared_ptr<MeshData> get_mesh_data(const std::string& name);
};

#endif
