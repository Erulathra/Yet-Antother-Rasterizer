#pragma once
#include "Buffer.h"
#include "Material.h"

typedef std::function<void(YAM::Triangle&)> VertexShader;
typedef std::function<void(YAM::Vector3&, const YAM::Vector3&, const YAM::Vector3&, const YAM::Vector3& )> PixelShader;

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

        void Render(Mesh* mesh, const VertexShader& vertexShader, const PixelShader& pixelShader);
        void Clear(YAM::Color color = {0xff000000});
        void Write();
        
    private:
        void RenderNDCTriangle(const YAM::Triangle& tri, const PixelShader& pixelShader);
    };
    
}
