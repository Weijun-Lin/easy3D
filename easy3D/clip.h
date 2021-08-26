//@Brief: 裁剪的相关实现

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
        // 线段剪裁
        static std::vector<Point3> __clipLine(const std::vector<Point4> &points);
        // 获取二维区域编码
        static unsigned char __getRegionCode(Point2 p);
        // Cyrus Beck 编码裁剪线段 对XY平面就行裁剪
        static bool __Cyrus_Beck(Point3& p0, Point3& p1);
        // XY平面裁剪后对Z轴裁剪
        static bool __z_clip(Point3& p0, Point3& p1);

    };

}

#endif