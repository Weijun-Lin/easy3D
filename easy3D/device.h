#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "utility.h"
#include <easyx.h>


namespace easy3d {
    // ��ʾ�豸
    class GraphicsDevice {
    public:
        GraphicsDevice(int width, int height);
        ~GraphicsDevice();
        
        void display(const DWORD* buffer);
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
