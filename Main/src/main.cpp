#include "BasicShaderProgram.h"
#include "Mesh.h"
#include "Rasterizer.h"
#include "Texture.h"
#include "Meshes/ConeMesh.h"
#include "Meshes/CubeMesh.h"
#include "Meshes/SphereMesh.h"

int main(int argc, char* argv[]) {
    YAR::Rasterizer rasterizer{512, 512};

    YAR::Material material{};
    material.SetColor({0xffffffff});

    std::unique_ptr<YAR::BasicShaderProgram> shaderProgram = std::make_unique<YAR::BasicShaderProgram>();
    YAR::AmbientLight ambientLight{};
    shaderProgram->SetAmbientLight(ambientLight);
    
    YAR::DirectionalLight directionalLight;
    directionalLight.direction = YAM::Vector3{-0, 0, -1}.Normal();
    directionalLight.diffuseStrength = 0.5f;
    directionalLight.specularStrenght = 0.5f;
    shaderProgram->SetDirectionalLight(directionalLight);
    
    YAR::PointLight pointLight{};
    pointLight.position = YAM::Vector3{1.f, 0.f, 1.f};
    pointLight.lightColor = {1.f, 0.f, 0.f};
    
    YAR::PointLight pointLight1{};
    pointLight1.position = YAM::Vector3{-1.f, 0.f, 1.f};
    pointLight1.lightColor = {0.f, 0.f, 1.f};

    shaderProgram->AddPointLight(pointLight);
    shaderProgram->AddPointLight(pointLight1);

    shaderProgram->SetProjection(YAM::Mat4::Perspective(YAM::ToRad(60.f), 1.f, 0.01f, 100.f));
    shaderProgram->SetView(YAM::Mat4::LookAt({0.f, 0.f, 6.f}, YAM::Vector3::Zero, YAM::Vector3::Up));
    
    rasterizer.Clear();
    
    YAM::Mat4 model;
    
    YAR::Mesh mesh{"res/plumber.obj"};
    model = (YAM::Mat4::Translation(0.f, 0.f, 0.f) * YAM::Mat4::Scale(0.5f, 0.5f, 0.5f));
    shaderProgram->SetModel(model);
    rasterizer.Render(&mesh, shaderProgram.get());
    
    YAR::ConeMesh ConeMesh(1.f, 2.f, 6);
    model = YAM::Mat4::Translation(2,-2, 0) * YAM::Mat4::RotationX(YAM::ToRad(-45.f)) * YAM::Mat4::Scale(0.5, 0.5, 0.5);
    shaderProgram->SetModel(model);
    rasterizer.Render(&ConeMesh, shaderProgram.get());
    
    YAR::SphereMesh sphereMesh(16);
    model = YAM::Mat4::Translation(-2,2, 0) * YAM::Mat4::Scale(0.5, 0.5, 0.5);
    shaderProgram->SetModel(model);
    rasterizer.Render(&sphereMesh, shaderProgram.get());
    
    YAR::Mesh sphereObj{"res/cube.obj"};
    model = YAM::Mat4::Translation(-2,-2, 0) * YAM::Mat4::Scale(0.5, 0.5, 0.5);
    shaderProgram->SetModel(model);
    rasterizer.Render(&sphereObj, shaderProgram.get());
    
    model = YAM::Mat4::Translation(2,2, 0) * YAM::Mat4::RotationY(YAM::ToRad(90.f)) * YAM::Mat4::Scale(1.f, 1.f, 1.f);
    shaderProgram->SetModel(model);
    std::shared_ptr<YAR::Texture> texture = std::make_shared<YAR::Texture>("res/textures/cat.png");
    shaderProgram->SetTexture(texture);
    rasterizer.Render(&sphereObj, shaderProgram.get());
    
    rasterizer.Write();
}
