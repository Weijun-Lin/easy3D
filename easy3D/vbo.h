//@Brief: ���嶥�㻺�����

#ifndef __VBO_H__
#define __VBO_H__

#include "utility.h"
#include <vector>

namespace easy3d {
    class VBO {
    public: 
        VBO();
        //~VBO();
        // ��������
        void setTranslate(TransformMat translate);
        void setRotate(TransformMat rotate);
        void setScale(TransformMat scale);
        void updateTrans();
        // �������
        void addPoints(std::vector<double> points);
        // ����ͼԪ
        void setPrimitive(Primitive primitive);
        std::vector<Point4> doTrans(TransformMat trans);
        Primitive getPrimitive() const;
        const std::vector<Point4>& getData() const;
    private:
        // �任���󣬱任����������ϵ�ı任����
        TransformMat __translate;
        TransformMat __rotate;
        TransformMat __scale;
        // ���������Ļ���
        TransformMat __trans;
        // ������
        std::vector<Point4> __points;
        // �����Ⱦ��ʽ��ͼԪ
        Primitive __primitive;
    };
}



#endif // !__VBO_H__