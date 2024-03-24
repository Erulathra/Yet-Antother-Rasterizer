#include "Mesh.h"
#include "Rasterizer.h"

int main(int argc, char* argv[]) {
    YAR::Rasterizer rasterizer {512, 512};

    YAR::Material material{};
    material.SetColor({0xffffffff});

    YAM::Mat4 camera = YAM::Mat4{1.f};
    // camera *= YAM::Mat4::Perspective(YAM::ToRad(60.f), 1.f, 0.01f, 100.f);
    camera *= YAM::Mat4::LookAt({2.0f, 2.f, 2.f}, YAM::Vector3::Zero, YAM::Vector3::Up);
    
    YAR::Mesh mesh{"res/plumber.obj"};
    YAM::Mat4 transform = camera * (YAM::Mat4::Translation(0.f, 0.f, 0.f) * YAM::Mat4::Scale(0.5f, 0.5f, 0.5f));

    auto vertexShader = [&transform](YAM::Triangle& triangle) {
        triangle.Apply(transform);
    };
    
    YAM::Vector3 sun {-1, -1, -1};
    sun = sun.Normal();
    
    auto pixelShader = [&sun](YAM::Vector3& outColor, const YAM::Vector3& pos, const YAM::Vector3& nor, const YAM::Vector3& uv) {
        outColor = YAM::Vector3{1.f} * nor.Dot(-sun);
        // outColor = nor;
    };

    rasterizer.Clear();
    rasterizer.Render(&mesh, vertexShader, pixelShader);
    rasterizer.Write();
}
