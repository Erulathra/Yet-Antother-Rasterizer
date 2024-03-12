#pragma once
#include <cstdint>
#include <vector>

namespace YAR{
    class ScreenBuffer {
    private:
        std::vector<uint32_t> colorBuf;
        std::vector<float> depthBuf;

        const uint32_t sizeX;
        const uint32_t sizeY;

    public:
        ScreenBuffer(uint32_t sizeX, uint32_t sizeY);

        uint32_t GetSizeX() const { return sizeX; }
        uint32_t GetSizeY() const { return sizeY; }

        void FillColor(uint32_t color);
        void FillDepth(float depth);

        const std::vector<uint32_t>& GetData() { return colorBuf; }
    };
}
