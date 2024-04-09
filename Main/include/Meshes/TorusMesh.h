#pragma once

#include <cstdint>

#include "Defines.h"
#include "Mesh.h"

namespace YAR{
    class TorusMesh : public Mesh{
    public:
        TorusMesh(YAM::flt radius, YAM::flt thickness, uint32_t radialSegments, uint32_t tubularSegments);
    };
} // YAR
