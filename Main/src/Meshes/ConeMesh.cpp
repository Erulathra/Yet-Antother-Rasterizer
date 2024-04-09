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
}
