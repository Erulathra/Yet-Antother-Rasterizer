#pragma once
#include "Vector3.h"

namespace YAR{
    class Light {
    public:
        YAM::Vector3 lightColor;
        YAM::flt diffuseStrength;
        YAM::flt specularStrenght;

        Light()
            : lightColor(1.f)
              , diffuseStrength(0.8f)
              , specularStrenght(0.5f) {}
    };

    class DirectionalLight : public Light {
    public:
        YAM::Vector3 direction;

        DirectionalLight()
            : Light()
              , direction((YAM::Vector3{-1.f, -1.f, 1.f}).Normal()) {}
    };

    class PointLight : public Light {
    public:
        YAM::Vector3 position;

        PointLight()
            : Light()
              , position(YAM::Vector3{0.f}) {}
    };
    
    struct AmbientLight {
        YAM::Vector3 color;
        YAM::flt strenght;

        AmbientLight()
          : color(YAM::Vector3{1.f})
            , strenght(0.1) {}
    };
} // YAR
