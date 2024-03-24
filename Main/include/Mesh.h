#pragma once

#include <vector>

#include "LinearMath.h"
#include "Vector3.h"

namespace YAR {

class Mesh {
private:
    std::vector<YAM::Vector3> verticies{};
    std::vector<uint32_t> vert_indicies{};
    
    std::vector<YAM::Vector3> normals{};
    std::vector<uint32_t> norm_indicies{};
    
    YAM::AABB boudingBox;
    
private:
    Mesh();
    
public:
    Mesh(const std::string& path);
    
    void GetTriangle(uint32_t index, YAM::Triangle& outTriangle) const;
    uint32_t GetNumTriangles() const {return vert_indicies.size() / 3.;} 
    
    const YAM::AABB& GetBoudingBox() const { return boudingBox; }

private:
    void ParseOBJ(const std::string& path);
    void CalculateBoundingBox(const std::vector<YAM::Vector3>& verticies);
};

} // YAR
