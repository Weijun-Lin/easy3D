#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "utility.h"
#include <string.h>
#include <easyx.h>


namespace easy3d {
    // ��ʾ�豸
    class GraphicsDevice {
    public:
        GraphicsDevice(int width, int height);
        ~GraphicsDevice();
        
        // ��ʾ��դ�����
        void displayRaster(const DWORD* buffer);
        // ��ʾ֡��
        void outFPS(uint fps);
        // ˢ�»���
        void flush();
    private:
        // ��ʾ��������ݻ���
        DWORD* __display_buffer;
        // ��ʾ���Ĵ�С
        int __width;
        int __height;
        int __size;
    };
}


#endif // !__DEVICE_H__
