//@Date: 2021-08-13
//@Brief: 光栅化相关实现
//@Class: 
//    - Rasteration


#ifndef __RASTERATION__H__
#define __RASTERATION__H__

#include "utility.h"

namespace easy3d {
    class Rasteration {
    public:
        Rasteration(int width, int height);
        ~Rasteration();

        // 使用指定颜色清空
        void clear(COLORREF color = 0);
        // 画线
        void drawLine(float x1, float y1, float x2, float y2, COLORREF color = 0xffffff);
        // 填充三角形
        void drawFillTriangle(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_, COLORREF color = 0xffffff);
        // 返回显示缓冲
        const DWORD* getBuffer();

    private:
        void __writePixel(int x, int y, COLORREF color);
        void __toDisplayCoord(float x, float y, float& _x, float& _y);

    private:
        int __width;
        int __height;
        int __size;
        COLORREF* __buffer;   // 虚拟显示缓冲
    };
}

#endif // !__RASTERATION__H__