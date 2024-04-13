#include "Rasterizer.h"

#include "Algorithms.h"
#include "LinearMath.h"
#include "Mesh.h"
#include "TGAWriter.h"
#include "Vector3.h"
#include "ShaderProgram.h"

YAR::Rasterizer::Rasterizer(uint32_t resX, uint32_t resY)
    : colorBuffer(resX, resY) {
}

void YAR::Rasterizer::Clear(YAM::Color color) {
    colorBuffer.FillColor(color.hex);
    colorBuffer.FillDepth(std::numeric_limits<float>::max());
}

void YAR::Rasterizer::Write() {
    std::string outputPath = "res/output/result.tga";
    YAR::TGAWriter::Write(outputPath, colorBuffer.GetData(), colorBuffer.GetSizeX(), colorBuffer.GetSizeY());
}

void YAR::Rasterizer::Render( Mesh* mesh, const ShaderProgram* shaderProgram) {
    YAM::Triangle triangle {};

    for (int trisId = 0; trisId < mesh->GetNumTriangles(); ++trisId) {
        mesh->GetTriangle(trisId,triangle);
        shaderProgram->VertexShader(triangle);
        
        RenderNDCTriangle(triangle, shaderProgram);
    }
}

void YAR::Rasterizer::RenderNDCTriangle(const YAM::Triangle& tri, const ShaderProgram* shaderProgram ) {
    const int32_t sizeX = colorBuffer.GetSizeX(), sizeY = colorBuffer.GetSizeY();
    const int32_t x1 = (tri.posA.x + 1.f) * sizeX * 0.5f, x2 = (tri.posB.x + 1.f) * sizeX * 0.5f, x3 = (tri.posC.x + 1.f) * sizeX * 0.5f;
    const int32_t y1 = (tri.posA.y + 1.f) * sizeY * 0.5f, y2 = (tri.posB.y + 1.f) * sizeY * 0.5f, y3 = (tri.posC.y + 1.f) * sizeY * 0.5f;
    const float z1 = tri.posA.z, z2 = tri.posB.z, z3 = tri.posC.z;

    int32_t xMin = YAM::Min3(x1, x2, x3);
    int32_t yMin = YAM::Min3(y1, y2, y3);
    int32_t xMax = YAM::Max3(x1, x2, x3);
    int32_t yMax = YAM::Max3(y1, y2, y3);

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
                const float barU = (dy23 * dxs3 + dx32 * dys3) * barUDenominator;
                const float barV = (dy31 * dxs3 + dx13 * dys3) * barVDenominator;
                const float barW = 1.f - barU - barV;

                const float screenDepth = colorBuffer.GetDepth(screenX, screenY);
                const float currentDepth = barU * z1 + barV * z2 + barW * z3;

                if (currentDepth < screenDepth) {
                    YAM::Vector3 pixColor {0.f};
                    
                    YAM::Vector3 interpPosition = barU * tri.posA + barV * tri.posB + barW * tri.posC;
                    YAM::Vector3 interpNormal = barU * tri.norA + barV * tri.norB + barW * tri.norC;
                    YAM::Vector3 interpColor = barU * tri.colorA + barV * tri.colorB + barW * tri.colorC;
                    interpNormal = interpNormal.Normal();
                    
                    YAM::Vector3 interpUV = barU * tri.uvA / tri.posA.z
                                          + barV * tri.uvB / tri.posB.z
                                          + barW * tri.uvC / tri.posC.z;

                    shaderProgram->PixelShader(pixColor, interpPosition, interpNormal, interpUV, interpColor);

                    colorBuffer.SetPix(screenX, screenY, YAM::Color::FromVector(pixColor).hex);
                    colorBuffer.SetDepth(screenX, screenY, currentDepth);
                }
            }
        }
    }
    
}
