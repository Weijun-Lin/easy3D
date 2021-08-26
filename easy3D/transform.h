//@brief: �ṩ�任����

#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "Eigen3/Dense"
#include "utility.h"

namespace easy3d {
    class Transform {
    public:
        // ��ת
        static TransformMat rotate(Point3 axis, double angle);
        // ƽ��
        static TransformMat translate(double dlt_x, double dlt_y, double dlt_z);
        // ����
        static TransformMat scale(double s_x, double s_y, double s_z);

        // ��������ϵ -> �Ӿ�����ϵ
        static TransformMat camera(Point3 eye, Vector3 center, Vector3 up);
        // ƽ��ͷ���������
        static TransformMat perspective();
        // ����ӳ��ȷ��������ͶӰ���󣬹�һ�����꣬��ƽ��ͷ���Ϊ-1~1������
        // angle ��ֱ���Ž� 
        // aspect ���ݱ�
        // z_near z_far ��Զƽ��
        static TransformMat orth_uniform(double angle, double aspect, double z_near, double z_far);
    };
}

#endif // !__TRANSFORM_H__

