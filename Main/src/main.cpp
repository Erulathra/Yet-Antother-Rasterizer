#include "Buffer.h"
#include "TGAWriter.h"

int main(int argc, char* argv[]) {
    std::string outputPath = "result.tga";
    YAR::Buffer screenBuffer {256, 256};

    screenBuffer.FillColor(0xff00ffff);
    
    YAR::TGAWriter::Write(outputPath, screenBuffer.GetData(), screenBuffer.GetSizeX(), screenBuffer.GetSizeY());
}
