#include "Shaders/VertexLightingShaderProgram.h"

void YAR::VertexLightingShaderProgram::PreProcess() {
    YAM::Mat4 modelNoTrans = model;
    modelNoTrans[3] = YAM::Vector4{0.f, 0.f, 0.f, 1.f};

    invTransModel = modelNoTrans.Inverse().Transpose();
    modelToProjection = projection * view * model;

    viewPos = YAM::Vector3{view[3]};
}

void YAR::VertexLightingShaderProgram::VertexShader(YAM::Triangle& outTriangle) const {
    outTriangle.Apply(modelToProjection);
    outTriangle.TransformNormal(invTransModel);

    auto calculateColor = [&](YAM::Vector3& pos, YAM::Vector3& nor, YAM::Vector3& color) {
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

        for (const YAR::SpotLight& light : spotLights) {
            const YAM::Vector3 vertDir = (light.position - pos).Normal();
            const float theta = std::acos(YAM::Vector3::Dot(light.direction, vertDir));

            if (theta < light.angle) {
                calculateLight(&light, lightDir);
            }
        }

        color = (ambient + lightColor).Mul(YAM::Vector3(1.f));
    };

    calculateColor(outTriangle.posA, outTriangle.norA, outTriangle.colorA);
    calculateColor(outTriangle.posB, outTriangle.norB, outTriangle.colorB);
    calculateColor(outTriangle.posC, outTriangle.norC, outTriangle.colorC);
}

void YAR::VertexLightingShaderProgram::PixelShader(YAM::Vector3& outColor, const YAM::Vector3& pos, const YAM::Vector3& nor, const YAM::Vector3& uv, const YAM::Vector3& col) const {
    outColor = col;
}
