#pragma once
#include "Buffer.h"
#include "Material.h"

namespace YAM{
    struct Triangle;
}

namespace YAR{
    class Rasterizer {
        Buffer colorBuffer;
        
    public:
        Rasterizer(uint32_t resX, uint32_t resY);

        void Render();
        
    private:
        void RenderNDCTriangle(YAM::Triangle tri, Material material);
    };
    
}
