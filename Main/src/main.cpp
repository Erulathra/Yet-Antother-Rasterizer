#include "Buffer.h"
#include "Rasterizer.h"
#include "TGAWriter.h"

int main(int argc, char* argv[]) {
    
    YAR::Rasterizer rasterizer {64, 64};
    rasterizer.Render();
    
}
