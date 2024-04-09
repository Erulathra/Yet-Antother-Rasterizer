#include "Meshes/TorusMesh.h"

#include <cmath>

#include "Vector3.h"

namespace YAR{
    TorusMesh::TorusMesh(YAM::flt radius, YAM::flt thickness, uint32_t radialSegments, uint32_t tubularSegments) {
        // generate vertices
        for (size_t i = 0; i < radialSegments; i++) {
            for (size_t j = 0; j < tubularSegments; j++) {
                YAM::flt u = static_cast<YAM::flt>(j) / tubularSegments * M_PI * 2.0;
                YAM::flt v = static_cast<YAM::flt>(i) / radialSegments * M_PI * 2.0;
                YAM::flt x = (radius + thickness * std::cos(v)) * std::cos(u);
                YAM::flt y = (radius + thickness * std::cos(v)) * std::sin(u);
                YAM::flt z = thickness * std::sin(v);
                vertices.push_back(YAM::Vector3(x, y, z));
            }
        }

        // add quad faces
        for (size_t i = 0; i < radialSegments; i++) {
            uint32_t i_next = (i + 1) % radialSegments;
            
            for (size_t j = 0; j < tubularSegments; j++) {
                uint32_t j_next = (j + 1) % tubularSegments;
                uint32_t i0 = i * tubularSegments + j;
                uint32_t i1 = i * tubularSegments + j_next;
                uint32_t i2 = i_next * tubularSegments + j_next;
                uint32_t i3 = i_next * tubularSegments + j;

                vert_indicies.push_back(i0);
                vert_indicies.push_back(i1);
                vert_indicies.push_back(i2);
                
                vert_indicies.push_back(i0);
                vert_indicies.push_back(i2);
                vert_indicies.push_back(i3);
            }
        }
        
        norm_indicies.insert(norm_indicies.end(), vert_indicies.begin(), vert_indicies.end());
        normals.resize(vertices.size(), YAM::Vector3{0});

        for (const uint32_t& indice : norm_indicies) {
            normals[indice] = vertices[indice].Normal();
        }

        for (YAM::Vector3& normal : normals) {
            normal = YAM::Vector3::Zero;
        }

        for (int i = 0; i < vert_indicies.size(); i += 3) {
            YAM::Vector3 normal = YAM::Vector3::Cross(
                (vertices[vert_indicies[i]] - vertices[vert_indicies[i + 1]]),
                (vertices[vert_indicies[i]] - vertices[vert_indicies[i + 2]])
                ).Normal();

            normals[vert_indicies[i]] += normal;
            normals[vert_indicies[i + 1]] += normal;
            normals[vert_indicies[i + 2]] += normal;
        }

        for (YAM::Vector3& normal : normals) {
            normal = normal.Normal();
        }
    }
} // YAR
