#pragma once
#include "Mesh.h"

namespace YAR {

class SphereMesh : public Mesh {
public:
    SphereMesh(uint32_t segmentsNum, float radius);
    SphereMesh(uint32_t segmentsNum);
};

} // YAR
