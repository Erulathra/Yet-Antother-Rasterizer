#pragma once

#include <vector>

#include "LinearMath.h"
#include "Vector3.h"

namespace YAR {

class Mesh {
protected:
    std::vector<YAM::Vector3> verticies{};
    std::vector<uint32_t> vert_indicies{};
    
    std::vector<YAM::Vector3> normals{};
    std::vector<uint32_t> norm_indicies{};
protected:
    Mesh();
    
public:
    Mesh(const std::string& path);
    
    void GetTriangle(uint32_t index, YAM::Triangle& outTriangle) const;
    uint32_t GetNumTriangles() const {return vert_indicies.size() / 3.;} 

private:
    void ParseOBJ(const std::string& path);
};

} // YAR
