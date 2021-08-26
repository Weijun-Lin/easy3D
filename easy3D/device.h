#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "utility.h"
#include <string.h>
#include <easyx.h>


namespace easy3d {
    // 显示设备
    class GraphicsDevice {
    public:
        GraphicsDevice(int width, int height);
        ~GraphicsDevice();
        
        // 显示光栅化结果
        void displayRaster(const DWORD* buffer);
        // 显示帧率
        void outFPS(uint fps);
        // 刷新画面
        void flush();
    private:
        // 显示区域的数据缓冲
        DWORD* __display_buffer;
        // 显示区的大小
        int __width;
        int __height;
        int __size;
    };
}


#endif // !__DEVICE_H__
