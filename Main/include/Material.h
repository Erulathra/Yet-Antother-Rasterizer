#pragma once
#include "LinearMath.h"

namespace YAR{
    class Material {
    private:
        YAM::Color color;

    public:
        Material() = default;

        YAM::Color GetColor() const { return color; }
        void SetColor(const YAM::Color& newColor) { color = newColor; }
    };
}
