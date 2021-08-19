//@Brief: һЩ���õĶ���͹��߰�

#ifndef __UTILITY__H__
#define __UTILITY__H__

#include <iostream>
#include "Eigen3/Core"

#define SEE(x) std::cout << #x << " " << x << std::endl;

typedef unsigned long DWORD;
// ������ɫ���ͣ�ƥ�� easyx
typedef DWORD COLORREF;
typedef unsigned int uint;

// --------- �ض��嶨�峣���������� -----------------
// ���������
typedef Eigen::Vector2d Point2;
typedef Eigen::Vector3d Point3;
// ����
typedef Point3 Vector3;
// �������
typedef Eigen::Vector4d Point4;
// 4*4 �任����
typedef Eigen::Matrix4d TransformMat;

// -------------- ���ߺ��� -----------------------
// ������������
inline void swap_int(int& a, int& b) {
    int temp = b;
    b = a;
    a = temp;
}

// ����ͼԪ
enum class Primitive {
    LINES,          // �߶�
    LINES_CLOSE,    // �պ��߶�
    TRIANGLE_FILL   // ���������
};

#endif // !__UTILITY__H__
