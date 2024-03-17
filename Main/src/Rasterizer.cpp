#include "Rasterizer.h"

#include "Algorithms.h"
#include "LinearMath.h"
#include "Material.h"
#include "TGAWriter.h"
#include "Vector3.h"

YAR::Rasterizer::Rasterizer(uint32_t resX, uint32_t resY)
    : colorBuffer(resX, resY) {}

void YAR::Rasterizer::Render() {
    colorBuffer.FillColor(0xff000000);

    YAM::Triangle triangle {
        YAM::Vector3{-0.8f, -0.3f, 0.f},
        YAM::Vector3{-0.5f, 0.5f, 0.f},
        YAM::Vector3{0.5f, 0.5f, 0.f},
    };

    Material material {};
    material.SetColor(YAM::Color{0xffff0000});

    RenderNDCTriangle(triangle, material);
    
    std::string outputPath = "result.tga";
    YAR::TGAWriter::Write(outputPath, colorBuffer.GetData(), colorBuffer.GetSizeX(), colorBuffer.GetSizeY());
}

void YAR::Rasterizer::RenderNDCTriangle(YAM::Triangle tri, Material material) {
    const int32_t sizeX = colorBuffer.GetSizeX(), sizeY = colorBuffer.GetSizeY();
    const int32_t x1 = (tri.posA.x + 1.f) * sizeX * 0.5f, x2 = (tri.posB.x + 1.f) * sizeX * 0.5f, x3 = (tri.posC.x + 1.f) * sizeX * 0.5f;
    const int32_t y1 = (tri.posA.y + 1.f) * sizeY * 0.5f, y2 = (tri.posB.y + 1.f) * sizeY * 0.5f, y3 = (tri.posC.y + 1.f) * sizeY * 0.5f;

    int32_t xMin = YAM::Algorithms::Min3(x1, x2, x3);
    int32_t yMin = YAM::Algorithms::Min3(y1, y2, y3);
    int32_t xMax = YAM::Algorithms::Max3(x1, x2, x3);
    int32_t yMax = YAM::Algorithms::Max3(y1, y2, y3);

    xMin = std::max(xMin, static_cast<int32_t>(0));
    yMin = std::max(yMin, static_cast<int32_t>(0));
    xMax = std::min(xMax, sizeX);
    yMax = std::min(yMax, sizeY);

    const int32_t dx12 = x1 - x2;
    const int32_t dx23 = x2 - x3;
    const int32_t dx31 = x3 - x1;
    
    const int32_t dy12 = y1 - y2;
    const int32_t dy23 = y2 - y3;
    const int32_t dy31 = y3 - y1;

    for (int32_t screenY = yMin; screenY < yMax; ++screenY) {
        for (int32_t screenX = xMin; screenX < xMax; ++screenX) {
            if (dx12 * (screenY - y1) - dy12 * (screenX - x1) > 0
                && dx23 * (screenY - y2) - dy23 * (screenX - x2) > 0
                && dx31 * (screenY - y3) - dy31 * (screenX - x3) > 0) {

                colorBuffer.SetPix(screenX, screenY, material.GetColor().hex);
            }
        }
    }
    
}
