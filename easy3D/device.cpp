#include "device.h"

easy3d::GraphicsDevice::GraphicsDevice(int width, int height)
    :__width(width), __height(height) {
    initgraph(width, height, EW_SHOWCONSOLE);
    this->__display_buffer = GetImageBuffer();
    this->__size = width * height;
}

easy3d::GraphicsDevice::~GraphicsDevice() {
    closegraph();
}

void easy3d::GraphicsDevice::display(const DWORD* buffer) {
    for (int i = 0; i < this->__size; i++) {
        this->__display_buffer[i] = BGR(buffer[i]);
    }
}
