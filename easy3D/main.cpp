#include "device.h"
#include "rasterization.h"
#include <conio.h>


int main() {
    int width = 640, height = 480;
    easy3d::Rasteration raster(width, height);
    easy3d::GraphicsDevice device(width, height);
    raster.clear(0x888888);
    raster.drawLine(-0.5, 0.5, -0.4, -1);
    raster.drawLine(-1, 1, 1, -1, 0x0000AA);
    raster.drawLine(-1, 0, 1, 0, 0xAAAA00);
    raster.drawLine(0.5, 0.5, -0.5, -0.5, 0x55FFFF);
    raster.drawFillTriangle(0, 0.5, -0.5, -0.5, 0.5, -0.5);
    raster.drawFillTriangle(-1, 1, -1, 0.5, -0.5, 0.75, 0xFF5555);
    raster.drawFillTriangle(0.1, 0.5, 1, 0.5, -0.5, 0.75, 0xFF5555);
    device.display(raster.getBuffer());
    _getch();
    return 0;
}
