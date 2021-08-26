#include "rasterization.h"

easy3d::Rasteration::Rasteration(int width, int height):
    __width(width), __height(height), __buffer(nullptr) {
    this->__buffer = new COLORREF[width * height];
    // Ĭ��Ϊ��ɫ����
    memset(this->__buffer, 0, sizeof(COLORREF) * height * width);
    this->__size = width * height;
}

easy3d::Rasteration::~Rasteration() {
    delete[]this->__buffer;
}

void easy3d::Rasteration::clear(COLORREF color) {
    for (int i = 0; i < this->__size; i++) {
        this->__buffer[i] = color;
    }
}

// ʹ�� Bresenham �㷨����ֱ��
void easy3d::Rasteration::drawLine(double x1, double y1, double x2, double y2, COLORREF color) {
    // ���ݽ�����������Ҫ��֤�ڱ�׼������ϵ�� -1~1

    // ת������ʾ�豸����ϵ
    this->__toDisplayCoord(x1, y1, x1, y1);
    this->__toDisplayCoord(x2, y2, x2, y2);
    int x1_ = x1 + 0.5, y1_ = y1 + 0.5, x2_ = x2 + 0.5, y2_ = y2 + 0.5;
    int dx = abs(x2_ - x1_), dy = abs(y2_- y1_);
    bool flag = false;
    // �жϺ� x ��ĽǶȣ�����45�Ƚ���
    if (dx < dy) {
        flag = true;
        myswap(dx, dy);
    }

    int ix = (x2_ - x1_) > 0 ? 1 : -1;
    int iy = (y2_ - y1_) > 0 ? 1 : -1;

    int d = 2 * dy - dx;    // ������־
    int incrE = 2 * dy;
    int incrNE = 2 * (dy - dx);
    int x = x1_, y = y1_;
    this->__writePixel(x, y, color);
    if (flag) {
        while (y != y2_) {
            if (d <= 0) {
                d += incrE;
            }
            else {
                d += incrNE;
                x += ix;
            }
            y += iy;
            this->__writePixel(x, y, color);
        }
    }
    else {
        while (x != x2_) {
            if (d <= 0) {
                d += incrE;
            } else {
                d += incrNE;
                y += iy;
            }
            x += ix;
            this->__writePixel(x, y, color);
        }
    }
}

// ɨ������䷨���������
void easy3d::Rasteration::drawFillTriangle(double x1_, double y1_, double x2_, double y2_, double x3_, double y3_, COLORREF color) {
    // ת������ʾ�豸����ϵ
    this->__toDisplayCoord(x1_, y1_, x1_, y1_);
    this->__toDisplayCoord(x2_, y2_, x2_, y2_);
    this->__toDisplayCoord(x3_, y3_, x3_, y3_);
    int x1 = x1_ + 0.5f, y1 = y1_ + 0.5f;
    int x2 = x2_ + 0.5f, y2 = y2_ + 0.5f;
    int x3 = x3_ + 0.5f, y3 = y3_ + 0.5f;
    // ȷ�������� y ȡֵ��Χ
    int min_y = y1 < y2 ? y1 : y2;
    min_y = min_y < y3 ? min_y : y3;
    int max_y = y1 > y2 ? y1 : y2;
    max_y = max_y > y3 ? max_y : y3;
    // ���� y
    for (int y = min_y; y <= max_y; y++) {
        // ��ȡ����
        // ������ֻ���������㣬��x��ƽ�е���Ҫ����������
        // ʹ�ò������ʽ�������жϽ����Ƿ����߶���

        // xnum: �Ѿ�ȷ���Ľ���������cx1 cx2 ȷ���Ľ����x����
        int xnum = 0, cx1, cx2;
        if (y1 != y2) {
            double t = (y - y1*1.0f)/(y2 - y1);
            if (t >= 0 && t <= 1) {
                xnum++;
                cx1 = x1 + (x2 - x1) * t;
            }
        }
        if (y2 != y3) {
            double t = (y - y2 * 1.0f) / (y3 - y2);
            if (t >= 0 && t <= 1) {
                // �ж��Ƿ�͵�һ���ཻ��
                if (xnum == 0) {
                    cx1 = x2 + (x3 - x2) * t;
                }
                else {
                    cx2 = x2 + (x3 - x2) * t;
                }
                xnum++;
            }
        }
        // ��ʱ�ض������ֱ���ཻ
        if (xnum != 2) {
            double t = (y - y3 * 1.0f) / (y1 - y3);
            cx2 = x3 + (x1 - x3) * t;
        }
        if (cx1 > cx2) {
            myswap(cx1, cx2);
        }
        // ���
        for (int x = cx1; x <= cx2; x++) {
            this->__writePixel(x, y, color);
        }
    }

}

const DWORD* easy3d::Rasteration::getBuffer() {
    return this->__buffer;
}

// ����ʾ���帳ֵ
void easy3d::Rasteration::__writePixel(int x, int y, COLORREF color) {
    this->__buffer[(this->__height - y) * this->__width + x] = color;
    //COLORREF buffer_color = this->__buffer[y * this->__width + x];
    //SEE(color);
}

// ����׼��������ת��Ϊ��ʾ�豸����
void easy3d::Rasteration::__toDisplayCoord(double x, double y, double& _x, double& _y) {
    x = x + 1;
    y = y + 1;
    _x = x * (this->__width - 1) / 2 + 1;
    _y = y * (this->__height - 1) / 2 + 1;  
}