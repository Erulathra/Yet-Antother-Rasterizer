#pragma once
#include "Buffer.h"
#include "Lights.h"
#include "Material.h"
#include "ShaderProgram.h"

namespace YAR{
    class ShaderProgram;
}

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

        void Render(Mesh* mesh, const ShaderProgram* shaderProgram);
        void Clear(YAM::Color color = {0xff000000});
        void Write();
        
    private:
        void RenderNDCTriangle(const YAM::Triangle& tri, const ShaderProgram* shaderProgram);
    };
    
}
