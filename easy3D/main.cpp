#include "device.h"
#include "rasterization.h"
#include "transform.h"
#include "vbo.h"
#include <conio.h>

int main() {
    easy3d::VBO vbo;
    // 立方体数据
    std::vector<double> points = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };
    vbo.addPoints(points);

    // 获取矩阵
    Point3 eye(0, 0, 4), center(0, 0, 0), up(0, 1, 0);
    TransformMat camera = easy3d::Transform::camera(eye, center, up);
    TransformMat perspective = easy3d::Transform::perspective();
    TransformMat F = perspective * camera;
    TransformMat orth = easy3d::Transform::orth_uniform(3.14 / 4, 640.0/480, 0.01, 99);

    // 显示设备
    int width = 640, height = 480;
    easy3d::Rasteration raster(width, height);
    easy3d::GraphicsDevice device(width, height);

    double angle = 0;
    while (true) {
        raster.clear(0xffffff);
        angle += 0.005;
        TransformMat rotate = easy3d::Transform::rotate(Point3(1, 1, 1), angle);
        vbo.setRotate(rotate);
        vbo.updateTrans();

        // 透视变换
        std::vector<Point4> points_new = vbo.doTrans(F);
        // 归一化
        for (auto iter = points_new.begin(); iter != points_new.end(); iter++) {
            *iter = orth * (*iter);
        }

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 5; j++) {
                int st =  6 * i + j;
                raster.drawLine(points_new[st](0), points_new[st](1), points_new[st + 1](0), points_new[st + 1](1), 0x55FF55);
            }
        }
        device.display(raster.getBuffer());
    }
    return 0;
}
