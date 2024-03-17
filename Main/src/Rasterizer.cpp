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
        YAM::Vector3{-0.5f, 0.5f, 0.f},
        YAM::Vector3{0.5f, -0.5f, 0.f},
        YAM::Vector3{-0.5f, -0.5f, 0.f},
    };
    YAM::Triangle triangle2 {
        YAM::Vector3{-0.5f, 0.5f, 0.f},
        YAM::Vector3{0.5f, 0.5f, 0.f},
        YAM::Vector3{0.5f, -0.5f, 0.f},
    };

    Material material {};
    material.SetColor(YAM::Color{0xffff0000});

    RenderNDCTriangle(triangle, material);
    RenderNDCTriangle(triangle2, material);
    
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
    const int32_t dx13 = x1 - x3;
    const int32_t dx23 = x2 - x3;
    const int32_t dx31 = x3 - x1;
    const int32_t dx32 = x3 - x2;
    
    const int32_t dy12 = y1 - y2;
    const int32_t dy13 = y1 - y3;
    const int32_t dy23 = y2 - y3;
    const int32_t dy31 = y3 - y1;

    const bool tl1 = (dy12 < 0 || (dy12 == 0 && dx12 > 0));
    const bool tl2 = (dy23 < 0 || (dy23 == 0 && dx23 > 0));
    const bool tl3 = (dy31 < 0 || (dy31 == 0 && dx31 > 0));

    const float barUDenominator = 1.f / (dy23 * dx13 + dx32 * dy13);
    const float barVDenominator = 1.f / (dy31 * dx23 + dx13 * dy23);

    for (int32_t screenY = yMin; screenY < yMax; ++screenY) {
        for (int32_t screenX = xMin; screenX < xMax; ++screenX) {
            const int32_t dxs3 = screenX - x3;
            const int32_t dys3 = screenY - y3;

            float edge1 = dx12 * (screenY - y1) - dy12 * (screenX - x1);
            float edge2 = dx23 * (screenY - y2) - dy23 * (screenX - x2);
            float edge3 = dx31 * dys3 - dy31 * dxs3;

            if ((edge1 > 0 || (edge1 >= 0 && tl1))
                && (edge2 > 0 || (edge2 >= 0 && tl2))
                && (edge3 > 0 || (edge3 >= 0 && tl3))) {

                // Calculate baricentric coordinates
                float barU = (dy23 * dxs3 + dx32 * dys3) * barUDenominator;
                float barV = (dy31 * dxs3 + dx13 * dys3) * barVDenominator;
                float barW = 1.f - barU - barV;

                YAM::Vector3 color1 = YAM::Color{0xffff0000}.ToVector();
                YAM::Vector3 color2 = YAM::Color{0xff00ff00}.ToVector();
                YAM::Vector3 color3 = YAM::Color{0xff0000ff}.ToVector();

                YAM::Vector3 pixColor = barU * color1 + barV * color2 + barW * color3;

                colorBuffer.SetPix(screenX, screenY, YAM::Color::FromVector(pixColor).hex);
            }
        }
    }
    
}
