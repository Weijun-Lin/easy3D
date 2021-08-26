//@Brief: �ü������ʵ��

#ifndef __CLIP_H__
#define __CLIP_H__

#include "utility.h"
#include "vbo.h"
#include <vector>

namespace easy3d {
    class Clip {
    public:
        static std::vector<Point3> clip(const std::vector<Point4>& points, Primitive type);
    private:
        // �߶μ���
        static std::vector<Point3> __clipLine(const std::vector<Point4> &points);
        // ��ȡ��ά�������
        static unsigned char __getRegionCode(Point2 p);
        // Cyrus Beck ����ü��߶� ��XYƽ����вü�
        static bool __Cyrus_Beck(Point3& p0, Point3& p1);
        // XYƽ��ü����Z��ü�
        static bool __z_clip(Point3& p0, Point3& p1);

    };

}

#endif