#include "CubeMesh.h"

namespace YAR{
    CubeMesh::CubeMesh(YAM::Vector3 size) {
        verticies.push_back(YAM::Vector3{0.5, 0.5, -0.5}.Mul(size));
        verticies.push_back(YAM::Vector3{0.5, -0.5, -0.5}.Mul(size));
        verticies.push_back(YAM::Vector3{0.5, 0.5, 0.5}.Mul(size));
        verticies.push_back(YAM::Vector3{0.5, -0.5, 0.5}.Mul(size));
        verticies.push_back(YAM::Vector3{-0.5, 0.5, -0.5}.Mul(size));
        verticies.push_back(YAM::Vector3{-0.5, -0.5, -0.5}.Mul(size));
        verticies.push_back(YAM::Vector3{-0.5, 0.5, 0.5}.Mul(size));
        verticies.push_back(YAM::Vector3{-0.5, -0.5, 0.5}.Mul(size));

        uint32_t vert_indicies[] = {
            4, 2, 0, 
            2, 7, 3, 
            6, 5, 7, 
            1, 7, 5,
            0, 3, 1, 
            4, 1, 5, 
            4, 6, 2, 
            2, 6, 7, 
            6, 4, 5, 
            1, 3, 7,
            0, 2, 3, 
            4, 0, 1, 
        };

        this->vert_indicies.insert(this->vert_indicies.begin(), std::begin(vert_indicies), std::end(vert_indicies));

        normals.push_back(YAM::Vector3{0., 1., 0.}.Mul(size));
        normals.push_back(YAM::Vector3{0., 0., 1.}.Mul(size));
        normals.push_back(YAM::Vector3{-1, 0, 0}.Mul(size));
        normals.push_back(YAM::Vector3{0, -1, 0}.Mul(size));
        normals.push_back(YAM::Vector3{1, 0, 0}.Mul(size));
        normals.push_back(YAM::Vector3{0, 0, -1}.Mul(size));


        uint32_t norm_indicies[] = {
            0, 0, 0,
            1, 1, 1,
            2, 2, 2,
            3, 3, 3,
            4, 4, 4,
            5, 5, 5,
            0, 0, 0,
            1, 1, 1,
            2, 2, 2,
            3, 3, 3,
            4, 4, 4,
            5, 5, 5,
        };

        this->norm_indicies.insert(this->norm_indicies.begin(), std::begin(norm_indicies), std::end(norm_indicies));
    }
} // YAR
