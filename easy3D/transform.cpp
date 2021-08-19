#include "transform.h"
//#include <math.h>

TransformMat easy3d::Transform::rotate(Point3 axis, double angle) {
    TransformMat R_xy = TransformMat::Identity(), R_z;
    R_z << cos(angle), -sin(angle), 0, 0,
        sin(angle), cos(angle), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1;
    // ���ж��Ƿ�� z �غ�
    if (axis(0) == 0 && axis(1) == 0) {
        return R_z;
    }
    // �� axis Ϊ ��Ϊ��z�� �����µ�����ϵ
    axis.normalize();
    Eigen::Vector3d z(0, 0, 1);
    Eigen::Vector3d new_y = axis.cross(z);
    new_y.normalize();
    Eigen::Vector3d new_x = new_y.cross(axis);
    new_y.normalize();
    // ��ֵ
    R_xy.block(2, 0, 1, 3) = axis.transpose();
    R_xy.block(1, 0, 1, 3) = new_y.transpose();
    R_xy.block(0, 0, 1, 3) = new_x.transpose();
    return R_xy.transpose() * R_z * R_xy;
}

// ƽ�ƾ���
TransformMat easy3d::Transform::translate(double dlt_x, double dlt_y, double dlt_z) {
    TransformMat T;
    T << 1, 0, 0, dlt_x,
        0, 1, 0, dlt_y,
        0, 0, 1, dlt_z,
        0, 0, 0, 1;
    return T;
}

// ���ž���
TransformMat easy3d::Transform::scale(double s_x, double s_y, double s_z) {
    TransformMat T;
    T << s_x, 0, 0, 0,
        0, s_y, 0, 0,
        0, 0, s_z, 0,
        0, 0, 0, 1;
    return T;
}

TransformMat easy3d::Transform::camera(Point3 eye, Vector3 center, Vector3 up) {
    // -lookat �ӽǷ����� -z
    Vector3 n = eye - center;
    n.normalize();
    // �����µ��Ӿ�����ϵ������
    Vector3 u = up.cross(n);
    Vector3 v = n.cross(u);
    u.normalize();
    v.normalize();
    // ��ȡ�任����
    TransformMat R = TransformMat::Identity();
    R.block(0, 0, 1, 3) = u.transpose();
    R.block(1, 0, 1, 3) = v.transpose();
    R.block(2, 0, 1, 3) = n.transpose();
    // ��Ҫƽ��
    R(0, 3) = -u.dot(eye);
    R(1, 3) = -v.dot(eye);
    R(2, 3) = -n.dot(eye);
    return R;
}

// ��ȡ͸��ͶӰ����
// ����ͨ����͸��ͶӰƽ��ͷ��ӳ��Ϊ�����壬֮��������ͶӰ
// ���ѹ��Ϊ -1~1����������
TransformMat easy3d::Transform::perspective() {
    // ��ӳ�����
    TransformMat R_map;
    R_map << 
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 1,
        0, 0, -1, 0;
    return R_map;
}

TransformMat easy3d::Transform::orth_uniform(double angle, double aspect, double z_near, double z_far) {
    // ��ȡԭʼƽ��ͷ��ӳ�䵽�������ķ�Χ
    double y_range = tan(angle / 2);
    double x_range = y_range * aspect;
    // z_near z_far ����Ӧ������ֵ������ת��Ϊ��ֵ�������� -z ����
    // z Խ��Խ�ӽ�
    double z_near_new = -(1 - 1 / z_near);
    double z_far_new = -(1 - 1 / z_far);
    // ������һ������
    TransformMat uniform_T = easy3d::Transform::translate(0, 0, -(z_near_new + z_far_new) / 2);
    TransformMat uniform_S = easy3d::Transform::scale(1 / x_range, 1 / y_range, 2 / (z_near_new - z_far_new));
    return uniform_S * uniform_T;
}
