#include "vbo.h"

easy3d::VBO::VBO() {
    this->__translate = TransformMat::Identity();
    this->__rotate = TransformMat::Identity();
    this->__scale = TransformMat::Identity();
    this->__trans = TransformMat::Identity();
    this->__primitive = Primitive::LINES;
}

void easy3d::VBO::setTranslate(TransformMat translate) {
    this->__translate = translate;
}

void easy3d::VBO::setRotate(TransformMat rotate) {
    this->__rotate = rotate;
}

void easy3d::VBO::setScale(TransformMat scale) {
    this->__scale = scale;
}

void easy3d::VBO::updateTrans() {
    this->__trans = this->__translate * this->__rotate * this->__scale;
}


void easy3d::VBO::addPoints(std::vector<double> points) {
    uint nums = points.size() / 3;
    for (uint i = 0; i < nums; i++) {
        Point4 temp(points[i * 3 + 0], points[i * 3 + 1], points[i * 3 + 2], 1.0);
        this->__points.push_back(temp);
    }
}

void easy3d::VBO::setPrimitive(Primitive primitive) {
    this->__primitive = primitive;
}

std::vector<Point4> easy3d::VBO::doTrans(TransformMat trans) {
    std::vector<Point4> res;
    Point4 temp;
    for (auto iter = this->__points.begin(); iter != this->__points.end(); iter++) {
        temp = trans * this->__trans * (*iter);
        temp /= temp(3);
        res.push_back(temp);
    }
    return res;
}

Primitive easy3d::VBO::getPrimitive() const {
    return this->__primitive;
}
const std::vector<Point4>& easy3d::VBO::getData() const {
    return this->__points;
}
