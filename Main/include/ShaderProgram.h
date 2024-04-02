#pragma once

namespace YAM{
    class Vector3;
    struct Triangle;
}

namespace YAR{
    class ShaderProgram {
    public:
        virtual ~ShaderProgram();
        
        virtual void PreProcess() = 0;
        
        virtual void VertexShader(YAM::Triangle& outTriangle) const = 0;
        virtual void PixelShader(YAM::Vector3& outColor, const YAM::Vector3& pos, const YAM::Vector3& nor, const YAM::Vector3& uv) const = 0;
    };
} // YAR
