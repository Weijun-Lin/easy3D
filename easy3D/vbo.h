//@Brief: 定义顶点缓冲对象

#ifndef __VBO_H__
#define __VBO_H__

#include "utility.h"
#include <vector>

namespace easy3d {
    class VBO {
    public: 
        VBO();
        //~VBO();
        // 矩阵设置
        void setTranslate(TransformMat translate);
        void setRotate(TransformMat rotate);
        void setScale(TransformMat scale);
        void updateTrans();
        // 数据添加
        void addPoints(std::vector<double> points);
        // 设置图元
        void setPrimitive(Primitive primitive);
        std::vector<Point4> doTrans(TransformMat trans);
        Primitive getPrimitive() const;
        const std::vector<Point4>& getData() const;
    private:
        // 变换矩阵，变换到世界坐标系的变换矩阵
        TransformMat __translate;
        TransformMat __rotate;
        TransformMat __scale;
        // 上面三个的汇总
        TransformMat __trans;
        // 点数据
        std::vector<Point4> __points;
        // 点的渲染形式，图元
        Primitive __primitive;
    };
}



#endif // !__VBO_H__