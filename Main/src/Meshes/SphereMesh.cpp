#include "Meshes/SphereMesh.h"

#include "spdlog/fmt/bundled/format.h"

namespace YAR{
    SphereMesh::SphereMesh(uint32_t segmentsNum) {
        const uint32_t vert = segmentsNum;
        const uint32_t horiz = segmentsNum;
        
        const uint32_t vSize = vert * (horiz + 2);
        const uint32_t tSize = 2 * vert * horiz;

        verticies.resize(vSize);

        for (uint32_t yy = 0; yy <= horiz + 1; ++yy) {
            const float y = std::cos(static_cast<float>(yy) * static_cast<float>(M_PI) / (horiz + 1.f));
            const float r = std::sqrt(1.f - y * y);

            for (uint32_t rr = 0; rr < vert; ++rr) {
                const float x = r * std::cos(2.f * M_PI * static_cast<float>(rr) / vert);
                const float z = r * std::sin(2.f * M_PI * rr / vert);

                verticies[rr + yy * vert] = YAM::Vector3{x, y, z};
            }
        }

        vert_indicies.resize(tSize * 3);

        for (uint32_t yy = 0; yy < horiz; ++yy) {
            for (int rr = 0; rr < vert; ++rr) {
                
                uint32_t index = (rr + 2 * yy * vert) * 3;
                vert_indicies[index + 2] = (rr + 1) % vert + yy * vert;
                vert_indicies[index + 1] = rr + vert + yy * vert;
                vert_indicies[index] = (rr + 1) % vert + vert + yy * vert;

                index = (rr + vert + 2 * yy * vert) * 3;
                vert_indicies[index + 2] = rr + vert + yy * vert;
                vert_indicies[index + 1] = rr + 2 * vert + yy * vert;
                vert_indicies[index] = (rr + 1) % vert + vert + yy * vert;
            }
        }

        norm_indicies.insert(norm_indicies.end(), vert_indicies.begin(), vert_indicies.end());
        normals.resize(vSize, YAM::Vector3{0});

        // for (uint32_t i = 0; i < tSize * 3; i += 3) {
        //     YAM::Vector3 normal =
        //         YAM::Vector3::Cross(
        //             verticies[vert_indicies[i + 2]] - verticies[vert_indicies[i]],
        //             verticies[vert_indicies[i + 1]] - verticies[vert_indicies[i]]
        //         ).Normal();
        //
        //     normals[vert_indicies[i]] += normal;
        //     normals[vert_indicies[i + 1]] += normal;
        //     normals[vert_indicies[i + 2]] += normal;
        // }
        //
        // for (YAM::Vector3& normal : normals) {
        //     normal = -normal.Normal();
        // }
        
        for (uint32_t i = 0; i < norm_indicies.size(); ++i) {
            normals[norm_indicies[i]] = verticies[norm_indicies[i]].Normal();
        }

    }
} // YAR
