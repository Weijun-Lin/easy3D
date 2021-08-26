#include "device.h"

easy3d::GraphicsDevice::GraphicsDevice(int width, int height)
    :__width(width), __height(height) {
    initgraph(width, height, EW_SHOWCONSOLE);
    this->__display_buffer = GetImageBuffer();
    this->__size = width * height;
    BeginBatchDraw();
}

easy3d::GraphicsDevice::~GraphicsDevice() {
    closegraph();
}

void easy3d::GraphicsDevice::displayRaster(const DWORD* buffer) {
    for (int i = 0; i < this->__size; i++) {
        this->__display_buffer[i] = BGR(buffer[i]);
    }
}

void easy3d::GraphicsDevice::outFPS(uint fps) {
    TCHAR str[50] = L"";
    //wcs
    swprintf_s(str, L"FPS:%d", fps);
    outtextxy(10, 10, str);
}

void easy3d::GraphicsDevice::flush() {
    FlushBatchDraw();
}
