#include "BasicShaderProgram.h"

#include "LinearMath.h"

namespace YAR {
    void BasicShaderProgram::PreProcess() {
        YAM::Mat4 modelNoTrans = model;
        modelNoTrans[3] = YAM::Vector4{0.f, 0.f, 0.f, 1.f};
        
        invTransModel = modelNoTrans.Inverse().Transpose();
        modelToProjection = projection * view * model;

        viewPos = YAM::Vector3{view[3]};
    }

    void BasicShaderProgram::VertexShader(YAM::Triangle& outTriangle) const {
        outTriangle.Apply(modelToProjection);
        outTriangle.TransformNormal(invTransModel);
    }

    void BasicShaderProgram::PixelShader(YAM::Vector3& outColor, const YAM::Vector3& pos, const YAM::Vector3& nor, const YAM::Vector3& uv) const {
        // ambient
        const YAM::Vector3 ambient = ambientLight.color * ambientLight.strenght;
        
        YAM::Vector3 lightColor;

        auto calculateLight = [&] (const Light* light, const YAM::Vector3 lightDir) {
            const YAM::Vector3 diffuse = YAM::Sat(nor.Dot(lightDir)) * light->diffuseStrength * light->lightColor;
            const YAM::Vector3 reflect = YAM::Reflect(-lightDir, nor);
            const YAM::Vector3 viewDir = (viewPos - pos).Normal();
            const float specularStrenght = std::pow(std::max(YAM::Vector3::Dot(viewDir, reflect), 0.f), 16);
            const YAM::Vector3 specular = specularStrenght * light->specularStrenght * light->lightColor;

            lightColor += diffuse + specular;
        };

        // directional
        const YAM::Vector3 lightDir = -directionalLight.direction;
        calculateLight(&directionalLight, lightDir);

        for (const YAR::PointLight& light : pointLights) {
            const YAM::Vector3 lightDir = (light.position - pos).Normal();
            calculateLight(&light, lightDir);
        }
        
        outColor = ambient + lightColor;
        outColor = outColor.Sat();
    }
} // YAR