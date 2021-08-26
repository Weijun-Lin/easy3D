//@brief: 提供变换矩阵

#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "Eigen3/Dense"
#include "utility.h"

namespace easy3d {
    class Transform {
    public:
        // 旋转
        static TransformMat rotate(Point3 axis, double angle);
        // 平移
        static TransformMat translate(double dlt_x, double dlt_y, double dlt_z);
        // 缩放
        static TransformMat scale(double s_x, double s_y, double s_z);

        // 世界坐标系 -> 视景坐标系
        static TransformMat camera(Point3 eye, Vector3 center, Vector3 up);
        // 平截头体拉伸矩阵
        static TransformMat perspective();
        // 由重映射确定的正交投影矩阵，归一化坐标，将平截头体变为-1~1正方体
        // angle 垂直视张角 
        // aspect 横纵比
        // z_near z_far 近远平面
        static TransformMat orth_uniform(double angle, double aspect, double z_near, double z_far);
    };
}

#endif // !__TRANSFORM_H__

