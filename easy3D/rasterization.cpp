#include "rasterization.h"

easy3d::Rasteration::Rasteration(int width, int height):
    __width(width), __height(height), __buffer(nullptr) {
    this->__buffer = new COLORREF[width * height];
    // 默认为黑色背景
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

// 使用 Bresenham 算法生成直线
void easy3d::Rasteration::drawLine(double x1, double y1, double x2, double y2, COLORREF color) {
    // 传递进来的坐标需要保证在标准化坐标系中 -1~1

    // 转换到显示设备坐标系
    this->__toDisplayCoord(x1, y1, x1, y1);
    this->__toDisplayCoord(x2, y2, x2, y2);
    int x1_ = x1 + 0.5, y1_ = y1 + 0.5, x2_ = x2 + 0.5, y2_ = y2 + 0.5;
    int dx = abs(x2_ - x1_), dy = abs(y2_- y1_);
    bool flag = false;
    // 判断和 x 轴的角度，超过45度交换
    if (dx < dy) {
        flag = true;
        myswap(dx, dy);
    }

    int ix = (x2_ - x1_) > 0 ? 1 : -1;
    int iy = (y2_ - y1_) > 0 ? 1 : -1;

    int d = 2 * dy - dx;    // 迭代标志
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

// 扫描线填充法填充三角形
void easy3d::Rasteration::drawFillTriangle(double x1_, double y1_, double x2_, double y2_, double x3_, double y3_, COLORREF color) {
    // 转换到显示设备坐标系
    this->__toDisplayCoord(x1_, y1_, x1_, y1_);
    this->__toDisplayCoord(x2_, y2_, x2_, y2_);
    this->__toDisplayCoord(x3_, y3_, x3_, y3_);
    int x1 = x1_ + 0.5f, y1 = y1_ + 0.5f;
    int x2 = x2_ + 0.5f, y2 = y2_ + 0.5f;
    int x3 = x3_ + 0.5f, y3 = y3_ + 0.5f;
    // 确定三角形 y 取值范围
    int min_y = y1 < y2 ? y1 : y2;
    min_y = min_y < y3 ? min_y : y3;
    int max_y = y1 > y2 ? y1 : y2;
    max_y = max_y > y3 ? max_y : y3;
    // 遍历 y
    for (int y = min_y; y <= max_y; y++) {
        // 获取交点
        // 三角形只有两个交点，和x轴平行的需要单独考虑下
        // 使用参数表达式很容易判断交点是否在线段内

        // xnum: 已经确定的交点数量，cx1 cx2 确定的交点的x坐标
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
                // 判断是否和第一个相交了
                if (xnum == 0) {
                    cx1 = x2 + (x3 - x2) * t;
                }
                else {
                    cx2 = x2 + (x3 - x2) * t;
                }
                xnum++;
            }
        }
        // 此时必定和这段直线相交
        if (xnum != 2) {
            double t = (y - y3 * 1.0f) / (y1 - y3);
            cx2 = x3 + (x1 - x3) * t;
        }
        if (cx1 > cx2) {
            myswap(cx1, cx2);
        }
        // 填充
        for (int x = cx1; x <= cx2; x++) {
            this->__writePixel(x, y, color);
        }
    }

}

const DWORD* easy3d::Rasteration::getBuffer() {
    return this->__buffer;
}

// 给显示缓冲赋值
void easy3d::Rasteration::__writePixel(int x, int y, COLORREF color) {
    this->__buffer[(this->__height - y) * this->__width + x] = color;
    //COLORREF buffer_color = this->__buffer[y * this->__width + x];
    //SEE(color);
}

// 将标准成像坐标转换为显示设备坐标
void easy3d::Rasteration::__toDisplayCoord(double x, double y, double& _x, double& _y) {
    x = x + 1;
    y = y + 1;
    _x = x * (this->__width - 1) / 2 + 1;
    _y = y * (this->__height - 1) / 2 + 1;  
}