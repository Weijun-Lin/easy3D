//@Brief: һЩ���õĶ���͹��߰�

#ifndef __UTILITY__H__
#define __UTILITY__H__

#include <iostream>
#include "Eigen3/Dense"

#define SEE(x) std::cout << #x << " " << x << std::endl;

typedef unsigned long DWORD;
// ������ɫ���ͣ�ƥ�� easyx
typedef DWORD COLORREF;
typedef unsigned int uint;

// --------- �ض��嶨�峣���������� -----------------
// ���������
typedef Eigen::Vector2d Point2;
typedef Eigen::Vector3d Point3;
// �������
typedef Eigen::Vector4d Point4;
// ����
typedef Point3 Vector3;
// 4*4 �任����
typedef Eigen::Matrix4d TransformMat;

// -------------- ���ߺ��� -----------------------
// ����������
template<typename T>
void myswap(T& a, T& b) {
    T temp = b;
    b = a;
    a = temp;
}

// ����ͼԪ
enum class Primitive {
    LINES,          // �߶�
    LINES_CLOSE,    // �պ��߶�
    TRIANGLE_FILL   // ���������
};

template<typename T>
T linearInterpolation(const T& p0, const T& p1, double t) {
    return p0 + (p1 - p0) * t;
}


#endif // !__UTILITY__H__