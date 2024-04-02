#include "Mesh.h"

#include <cstdint>
#include <fstream>

#include "spdlog/spdlog.h"

namespace YAR{
    Mesh::Mesh() {}

    Mesh::Mesh(const std::string& path) {
        ParseOBJ(path);
    }

    void Mesh::GetTriangle(uint32_t index, YAM::Triangle& outTriangle) const {
        uint32_t indiceID = index * 3;

        const uint32_t v1 = vert_indicies[indiceID];
        const uint32_t v2 = vert_indicies[indiceID + 1];
        const uint32_t v3 = vert_indicies[indiceID + 2];

        const uint32_t n1 = norm_indicies[indiceID];
        const uint32_t n2 = norm_indicies[indiceID + 1];
        const uint32_t n3 = norm_indicies[indiceID + 2];

        const uint32_t uv1 = uv_indicies[indiceID];
        const uint32_t uv2 = uv_indicies[indiceID + 1];
        const uint32_t uv3 = uv_indicies[indiceID + 2];

        outTriangle.posA = verticies[v1];
        outTriangle.posC = verticies[v2];
        outTriangle.posB = verticies[v3];
        
        outTriangle.norA = normals[n1];
        outTriangle.norC = normals[n2];
        outTriangle.norB = normals[n3];

        outTriangle.uvA = uvs[uv1];
        outTriangle.uvB = uvs[uv3];
        outTriangle.uvC = uvs[uv2];
    }

    void Mesh::ParseOBJ(const std::string& path) {
        std::ifstream objFile{path};

        // Parse file
        std::string fileLine;
        while (std::getline(objFile, fileLine)) {
            
            // skip comments
            if (fileLine[0] == '#') {
                continue;
            }

            char command[3];
            char parameters[30];

            std::sscanf(fileLine.c_str(), "%s %[^\t\n]", command, parameters);
            
            if (strcmp(command, "v") == 0) {
                YAM::Vector3 vertex;
                std::sscanf(parameters, "%f %f %f", &vertex.x, &vertex.y, &vertex.z);
                verticies.push_back(vertex);
            }
            if (strcmp(command, "vn") == 0) {
                YAM::Vector3 normal;
                std::sscanf(parameters, "%f %f %f", &normal.x, &normal.y, &normal.z);
                normals.push_back(normal);
            }
            if (strcmp(command, "vt") == 0) {
                YAM::Vector3 uv{0};
                std::sscanf(parameters, "%f %f", &uv.x, &uv.y);
                uvs.push_back(uv);
            }
            if (strcmp(command, "f") == 0) {
                uint32_t v1, v2, v3;
                uint32_t t1, t2, t3;
                uint32_t n1, n2, n3;

                std::sscanf(parameters,
                           "%i/%i/%i %i/%i/%i %i/%i/%i",
                           &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3);

                vert_indicies.push_back(v1 - 1);
                vert_indicies.push_back(v2 - 1);
                vert_indicies.push_back(v3 - 1);
                
                norm_indicies.push_back(n1 - 1);
                norm_indicies.push_back(n2 - 1);
                norm_indicies.push_back(n3 - 1);

                uv_indicies.push_back(t1 - 1);
                uv_indicies.push_back(t2 - 1);
                uv_indicies.push_back(t3 - 1);
            }
        }

    }
} // YAR
