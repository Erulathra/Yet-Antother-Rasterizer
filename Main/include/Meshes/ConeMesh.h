#pragma once

#include "Mesh.h"

namespace YAR{
    class ConeMesh : public YAR::Mesh {
    public:
        ConeMesh(float widith, float height, uint32_t segmentsNum);
    };
}
