//@Brief: 一些公用的定义和工具包

#ifndef __UTILITY__H__
#define __UTILITY__H__

#include <iostream>
#include "Eigen3/Dense"

#define SEE(x) std::cout << #x << " " << x << std::endl;

typedef unsigned long DWORD;
// 定义颜色类型，匹配 easyx
typedef DWORD COLORREF;
typedef unsigned int uint;

// --------- 重定义定义常用数据类型 -----------------
// 定义点类型
typedef Eigen::Vector2d Point2;
typedef Eigen::Vector3d Point3;
// 齐次坐标
typedef Eigen::Vector4d Point4;
// 向量
typedef Point3 Vector3;
// 4*4 变换矩阵
typedef Eigen::Matrix4d TransformMat;

// -------------- 工具函数 -----------------------
// 交换两个数
template<typename T>
void myswap(T& a, T& b) {
    T temp = b;
    b = a;
    a = temp;
}

// 定义图元
enum class Primitive {
    LINES,          // 线段
    LINES_CLOSE,    // 闭合线段
    TRIANGLE_FILL   // 三角形填充
};

template<typename T>
T linearInterpolation(const T& p0, const T& p1, double t) {
    return p0 + (p1 - p0) * t;
}


#endif // !__UTILITY__H__