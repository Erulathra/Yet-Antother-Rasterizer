#include "Meshes/ConeMesh.h"

namespace YAR{
    ConeMesh::ConeMesh(float radius, float height, uint32_t segmentsNum) {
        // tip
        vertices.push_back(YAM::Vector3(0.f, height / 2.f, 0.f));

        // cap
        for (size_t i = 0; i < segmentsNum; i++) {
            YAM::flt ratio = static_cast<YAM::flt>(i) / (segmentsNum);
            YAM::flt r = ratio * (M_PI * 2.0);
            YAM::flt x = std::cos(r) * radius;
            YAM::flt y = std::sin(r) * radius;
            vertices.push_back(YAM::Vector3(x, -height / 2.f, y));
        }

        // base center
        vertices.push_back(YAM::Vector3(0.f, -height / 2.f, 0.f));

        // cap
        for (size_t i = 0; i < segmentsNum; i++) {
            uint32_t ii = (i + 1) % segmentsNum;
            vert_indicies.push_back(0);
            vert_indicies.push_back(i + 1);
            vert_indicies.push_back(ii + 1);
        }

        // reverse order for consistent face orientation
        std::reverse(vert_indicies.begin(), vert_indicies.end());

        // Base
        for (size_t i = 0; i < segmentsNum; i++) {
            uint32_t ii = (i + 1) % segmentsNum;
            vert_indicies.push_back(vertices.size() - 1);
            vert_indicies.push_back(i + 1);
            vert_indicies.push_back(ii + 1);
        }

        norm_indicies.insert(norm_indicies.end(), vert_indicies.begin(), vert_indicies.end());
        normals.resize(segmentsNum + 2, YAM::Vector3{0});

        for (const uint32_t& indice : norm_indicies) {
            normals[indice] = vertices[indice].Normal();
        }
    }
}
