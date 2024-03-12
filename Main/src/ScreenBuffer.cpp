#include "ScreenBuffer.h"

namespace YAR{
    ScreenBuffer::ScreenBuffer(uint32_t sizeX, uint32_t sizeY)
        : sizeX(sizeX),
          sizeY(sizeY) {
        colorBuf.resize(sizeX * sizeY);
        depthBuf.resize(sizeX * sizeY);

        FillColor(0x00000000);
        FillDepth(0.f);
    }

    void ScreenBuffer::FillColor(uint32_t color) {
        for (int pixelID = 0; pixelID < sizeX * sizeY; ++pixelID) {
            colorBuf[pixelID] = color;
        }
    }

    void ScreenBuffer::FillDepth(float depth) {
        for (int pixelID = 0; pixelID < sizeX * sizeY; ++pixelID) {
            depthBuf[pixelID] = depth;
        }
    }
}
