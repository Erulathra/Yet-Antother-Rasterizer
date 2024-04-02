#pragma once
#include <memory>
#include <vector>

#include "Lights.h"
#include "Mat4.h"
#include "ShaderProgram.h"

namespace YAR {
    class Texture;

class BasicShaderProgram : public ShaderProgram {
    YAM::Mat4 model;
    YAM::Mat4 view;
    YAM::Mat4 projection;
    
    YAM::Mat4 modelToProjection;
    YAM::Mat4 invTransModel;

    YAM::Vector3 viewPos;

    AmbientLight ambientLight;
    DirectionalLight directionalLight;
    std::vector<PointLight> pointLights;

    std::shared_ptr<Texture> texture;
public:
    void PreProcess() override;
    
    void VertexShader(YAM::Triangle& outTriangle) const override;
    void PixelShader(YAM::Vector3& outColor, const YAM::Vector3& pos, const YAM::Vector3& nor, const YAM::Vector3& uv) const override;

    void SetModel(const YAM::Mat4& newModel) { model = newModel; PreProcess(); }
    void SetView(const YAM::Mat4& newView) { view = newView; PreProcess(); }
    void SetProjection(const YAM::Mat4& newProjection) { projection = newProjection; PreProcess(); }

    void SetAmbientLight(const AmbientLight& newAmbientLight) { ambientLight = newAmbientLight; }
    void SetDirectionalLight(const DirectionalLight& newDirectionalLight) { directionalLight = newDirectionalLight; }
    void AddPointLight(const PointLight& newPointLight) { pointLights.push_back(newPointLight); }

    void SetTexture(const std::shared_ptr<Texture>& newTexture) { texture = newTexture; }
};

} // YAR
