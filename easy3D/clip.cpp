#include "clip.h"

std::vector<Point3> easy3d::Clip::clip(const std::vector<Point4>& points, Primitive type) {
    if (type == Primitive::LINES) {
        return Clip::__clipLine(points);
    }
    return std::vector<Point3>();
}

// 线段裁剪
std::vector<Point3> easy3d::Clip::__clipLine(const std::vector<Point4>& points) {
    std::vector<Point3> res;
    // 前后相邻两个点构成直线，返回的是两个点 两个点配对的线段
    int size = points.size();
    Point3 p0, p1;
    for (int i = 0; i < size - 1; i++) {
        p0 = points[i].head(3);
        p1 = points[i + 1].head(3);
        // 获得区域编码
        unsigned char code1 = Clip::__getRegionCode(points[i].head(2));
        unsigned char code2 = Clip::__getRegionCode(points[i + 1].head(2));
        // 简单接收
        if ((code1 | code2) == 0) {
            // 仍然需要对Z轴做裁剪
            if (Clip::__z_clip(p0, p1)) {
                res.push_back(p0);
                res.push_back(p1);
            }
            continue;
        }
        // 简单排斥
        unsigned char temp = code1 & code2;
        if (temp == 1 || temp == 2 || temp == 4 || temp == 8) {
            continue;
        }
        // 其它 Cyrus-Beck 算法 并对Z轴做裁剪
        if (Clip::__Cyrus_Beck(p0, p1)) {
            if (Clip::__z_clip(p0, p1)) {
                res.push_back(p0);
                res.push_back(p1);
            }
        }
    }
    return res;
}

unsigned char easy3d::Clip::__getRegionCode(Point2 p) {
    double x = p(0), y = p(1);
    // 区域内
    if (x <= 1 && x >= -1 && y <= 1 && y >= -1) {
        return 0; // 0000
    }
    // 区域外 左边区域
    if (x <= -1) {
        if (y <= -1) {
            return 5; // 0101 左下
        }
        if (y >= 1) {
            return 9;   // 1001 左上
        }
        return 1; // 0001 左中
    }
    //区域外 右边区域
    if (x >= 1) {
        if (y <= -1) {
            return 6; // 0110 右下
        }
        if (y >= 1) {
            return 10; // 1010 右上
        }
        return 2;   // 0010 右中
    }
    // 中间区域
    if (y <= -1) {
        return 4;   // 0100 中下
    }
    if (y >= 1) {
        return 8;   // 1000 中上
    }
}

// 返回截断后的线段
bool easy3d::Clip::__Cyrus_Beck(Point3& p0, Point3& p1) {
    // 求解和四个边界线的交点
    double x0 = p0(0), y0 = p0(1), x1 = p1(0), y1 = p1(1);
    Point2 p01 = p1.head(2) - p0.head(2);
    double t[4];
    // 垂线
    if (x0 == x1) {
        t[0] = t[1] = -1;
    }
    else {
        t[0] = -(x0 + 1) / (x1 - x0);
        t[1] = -(x0 - 1) / (x1 - x0);
    }
    // 水平线
    if (y0 == y1) {
        t[2] = t[3] = -1;
    }
    else {
        t[2] = -(y0 + 1) / (y1 - y0);
        t[3] = -(y0 - 1) / (y1 - y0);
    }
    // 左右下上四个朝外的法向量
    Point2 normal[4] = { Point2(-1, 0), Point2(1,0), Point2(0,-1), Point2(0,1) };
    // 根据进入点和离开点获取被截取的线段，分别初始化01用于统一处理水平垂直两种情况
    double t_PE = 0, t_PL = 1;
    for (int i = 0; i < 4; i++) {
        if (t[i] == -1) {
            continue;
        }
        if (normal[i].dot(p01) < 0 && t[i] > t_PE) {
            t_PE = t[i];
        }
        if (normal[i].dot(p01) > 0 && t[i] < t_PL) {
            t_PL = t[i];
        }
    }
    // 两个点线性插值
    Point3 a_temp = linearInterpolation(p0, p1, t_PE);
    Point3 b_temp = linearInterpolation(p0, p1, t_PL);
    // 排除斜着仍然在区域外面的直线
    if (a_temp(0) > 1 || a_temp(1) > 1 || b_temp(0) > 1 || b_temp(1) > 1 ||
        a_temp(0) < -1 || a_temp(1) < -1 || b_temp(0) < -1 || b_temp(1) < -1) {
        return false;
    }
    p0 = a_temp;
    p1 = b_temp;
    return true;
}

// 对Z轴进行裁剪，情况较少列举即可
bool easy3d::Clip::__z_clip(Point3& p0, Point3& p1) {
    double z0 = p0(2), z1 = p1(2);
    // 都在区域内
    if (z0 >= -1 && z0 <= 1 && z1 >= -1 && z1 <= 1) {
        return true;
    }
    // 都在区域外，这个线段就应该被排除
    if ((z0 < -1 && z1 < -1) || (z0 > 1 && z1 > 1)) {
        return false;
    }
    // 需要裁剪的情况
    int flag0 = (z0 >= -1 && z0 <= 1) ? 1 : -1;
    int flag1 = (z1 >= -1 && z1 <= 1) ? 1 : -1;
    
    // 两个点都在外面就是下面这个值
    double t0 = (1 - p0(2)) / (p1(2) - p0(2));
    double t1 = (-1 - p0(2)) / (p1(2) - p0(2));
    // 一个点在外面 一个在里面
    if(flag0 * flag1 == -1) { 
        // 保证p0在里面，p1在外面
        if (flag0 == -1) {
            myswap(p0, p1);
        }
        // 保证 t1 是合法的，因为必定有一个是合法的, t0 = 0，t1 就是那个合法的
        if (t0 >= -1 && t0 <= 1) {
            t1 = t0;
        }
        // t0就是自己这个点
        t0 = 0;
    }
    // 两个点线性插值
    Point3 a_temp = linearInterpolation(p0, p1, t0);
    Point3 b_temp = linearInterpolation(p0, p1, t1);
    p0 = a_temp;
    p1 = b_temp;
    return true;
}
