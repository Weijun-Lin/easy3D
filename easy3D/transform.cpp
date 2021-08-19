#include "transform.h"
//#include <math.h>

TransformMat easy3d::Transform::rotate(Point3 axis, double angle) {
    TransformMat R_xy = TransformMat::Identity(), R_z;
    R_z << cos(angle), -sin(angle), 0, 0,
        sin(angle), cos(angle), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1;
    // 先判断是否和 z 重合
    if (axis(0) == 0 && axis(1) == 0) {
        return R_z;
    }
    // 以 axis 为 作为新z轴 构建新的坐标系
    axis.normalize();
    Eigen::Vector3d z(0, 0, 1);
    Eigen::Vector3d new_y = axis.cross(z);
    new_y.normalize();
    Eigen::Vector3d new_x = new_y.cross(axis);
    new_y.normalize();
    // 赋值
    R_xy.block(2, 0, 1, 3) = axis.transpose();
    R_xy.block(1, 0, 1, 3) = new_y.transpose();
    R_xy.block(0, 0, 1, 3) = new_x.transpose();
    return R_xy.transpose() * R_z * R_xy;
}

// 平移矩阵
TransformMat easy3d::Transform::translate(double dlt_x, double dlt_y, double dlt_z) {
    TransformMat T;
    T << 1, 0, 0, dlt_x,
        0, 1, 0, dlt_y,
        0, 0, 1, dlt_z,
        0, 0, 0, 1;
    return T;
}

// 缩放矩阵
TransformMat easy3d::Transform::scale(double s_x, double s_y, double s_z) {
    TransformMat T;
    T << s_x, 0, 0, 0,
        0, s_y, 0, 0,
        0, 0, s_z, 0,
        0, 0, 0, 1;
    return T;
}

TransformMat easy3d::Transform::camera(Point3 eye, Vector3 center, Vector3 up) {
    // -lookat 视角方向是 -z
    Vector3 n = eye - center;
    n.normalize();
    // 构建新的视景坐标系基向量
    Vector3 u = up.cross(n);
    Vector3 v = n.cross(u);
    u.normalize();
    v.normalize();
    // 获取变换矩阵
    TransformMat R = TransformMat::Identity();
    R.block(0, 0, 1, 3) = u.transpose();
    R.block(1, 0, 1, 3) = v.transpose();
    R.block(2, 0, 1, 3) = n.transpose();
    // 需要平移
    R(0, 3) = -u.dot(eye);
    R(1, 3) = -v.dot(eye);
    R(2, 3) = -n.dot(eye);
    return R;
}

// 获取透视投影矩阵
// 这里通过将透视投影平截头体映射为立方体，之后做正交投影
// 最后压缩为 -1~1的正方体中
TransformMat easy3d::Transform::perspective() {
    // 重映射矩阵
    TransformMat R_map;
    R_map << 
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 1,
        0, 0, -1, 0;
    return R_map;
}

TransformMat easy3d::Transform::orth_uniform(double angle, double aspect, double z_near, double z_far) {
    // 获取原始平截头体映射到立方体后的范围
    double y_range = tan(angle / 2);
    double x_range = y_range * aspect;
    // z_near z_far 给的应该是正值，这里转换为负值，成像在 -z 区域
    // z 越大越接近
    double z_near_new = -(1 - 1 / z_near);
    double z_far_new = -(1 - 1 / z_far);
    // 构建归一化矩阵
    TransformMat uniform_T = easy3d::Transform::translate(0, 0, -(z_near_new + z_far_new) / 2);
    TransformMat uniform_S = easy3d::Transform::scale(1 / x_range, 1 / y_range, 2 / (z_near_new - z_far_new));
    return uniform_S * uniform_T;
}
