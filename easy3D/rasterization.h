//@Date: 2021-08-13
//@Brief: ��դ�����ʵ��
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

        // ʹ��ָ����ɫ���
        void clear(COLORREF color = 0);
        // ����
        void drawLine(double x1, double y1, double x2, double y2, COLORREF color = 0xffffff);
        // ���������
        void drawFillTriangle(double x1_, double y1_, double x2_, double y2_, double x3_, double y3_, COLORREF color = 0xffffff);
        // ������ʾ����
        const DWORD* getBuffer();

    private:
        void __writePixel(int x, int y, COLORREF color);
        void __toDisplayCoord(double x, double y, double& _x, double& _y);

    private:
        int __width;
        int __height;
        int __size;
        COLORREF* __buffer;   // ������ʾ����
    };
}

#endif // !__RASTERATION__H__