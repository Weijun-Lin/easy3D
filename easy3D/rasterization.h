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
        void drawLine(double x1, double y1, double x2, double y2, COLORREF color = 0xffffff);
        // 填充三角形
        void drawFillTriangle(double x1_, double y1_, double x2_, double y2_, double x3_, double y3_, COLORREF color = 0xffffff);
        // 返回显示缓冲
        const DWORD* getBuffer();

    private:
        void __writePixel(int x, int y, COLORREF color);
        void __toDisplayCoord(double x, double y, double& _x, double& _y);

    private:
        int __width;
        int __height;
        int __size;
        COLORREF* __buffer;   // 虚拟显示缓冲
    };
}

#endif // !__RASTERATION__H__