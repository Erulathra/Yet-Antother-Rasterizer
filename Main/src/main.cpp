#include "Mesh.h"
#include "Rasterizer.h"

int main(int argc, char* argv[]) {
    YAR::Rasterizer rasterizer {512, 512};

    YAR::Material material{};
    material.SetColor({0xffffffff});

    YAM::Mat4 camera = YAM::Mat4{1.f};
    // camera *= YAM::Mat4::Perspective(YAM::ToRad(30.f), 1.f, 0.01f, 100.f);
    camera *= YAM::Mat4::LookAt({5.0f, 5.f, 10.f}, YAM::Vector3::Zero, YAM::Vector3::Up);
    
    YAR::Mesh mesh{"res/plumber.obj"};
    YAM::Mat4 transform = camera * (YAM::Mat4::Translation(0.f, 0.f, 0.f) * YAM::Mat4::Scale(0.5f, 0.5f, 0.5f));
    // YAM::Mat4 transform = camera;

    rasterizer.Clear();
    rasterizer.Render(&mesh, &material, transform);
    rasterizer.Write();
}
