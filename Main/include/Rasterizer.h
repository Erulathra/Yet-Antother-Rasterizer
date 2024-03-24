#pragma once
#include "Buffer.h"
#include "Material.h"

namespace YAR{
    class Mesh;
}

namespace YAM{
    struct Triangle;
}

namespace YAR{
    class Rasterizer {
        Buffer colorBuffer;

    public:
        Rasterizer(uint32_t resX, uint32_t resY);

        void Render(Mesh* mesh, Material* material, const YAM::Mat4& transform);
        void Clear(YAM::Color color = {0xff000000});
        void Write();
        
    private:
        void RenderNDCTriangle(const YAM::Triangle& tri, const Material& material);
    };
    
}
