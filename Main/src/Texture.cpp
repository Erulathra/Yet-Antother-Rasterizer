#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "spdlog/spdlog.h"

YAR::Texture::Texture(const std::string& path): sizeX(0), sizeY(0) {
    Load(path);
}

YAM::Color YAR::Texture::Sample(const YAM::Vector3& UV) const {
    float u = std::clamp(UV.x, 0.f, 1.f);
    float v = std::clamp(UV.y, 0.f, 1.f);
    
    const uint32_t x = std::round(u * (sizeX - 1));
    const uint32_t y = std::round((sizeY - 1) - v * (sizeY - 1));
    const uint32_t hex = GetPix(x, y);
    return {hex};
}

void YAR::Texture::Load(const std::string& path) {
    int32_t channels;
    unsigned char* data = stbi_load(path.c_str(), &sizeX, &sizeY, &channels, 3);

    if (data == nullptr) {
        spdlog::error("Error during loading texture");
        return;
    }

    colorBuf.resize(sizeX * sizeY);
    for (int32_t imageX = 0; imageX < sizeX; ++imageX) {
        for (int32_t imageY = 0; imageY < sizeY; ++imageY) {
            const int32_t byteNumber = 3 * (imageX + sizeX * imageY);
            
            YAM::Color color {};
            color.bytes[3] = 255.f;
            color.bytes[2] = data[byteNumber + 0];
            color.bytes[1] = data[byteNumber + 1];
            color.bytes[0] = data[byteNumber + 2];
            
            SetPix(imageX, imageY, color.hex);
        }
    }

    delete[] data;
}
