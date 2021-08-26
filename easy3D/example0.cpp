//@Time: 2021/8/26
//@Brief: 示例程序0，立方体的线框图的投影，裁剪，渲染管线
#include "examples.h"

void example0() {
    // 帧率
    const int FPS = 60;
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
    Point3 eye(0, 1, 1), center(0, 0, 0), up(0, 1, 0);
    // 相机
    TransformMat camera = easy3d::Transform::camera(eye, center, up);
    // 透视变换
    TransformMat perspective = easy3d::Transform::perspective();
    TransformMat F = perspective * camera;
    // 正交投影归一化矩阵
    TransformMat orth = easy3d::Transform::orth_uniform(3.14 / 4, 640.0 / 480, 0.01, 99);

    // 显示设备
    int width = 640, height = 480;
    easy3d::Rasteration raster(width, height);
    easy3d::GraphicsDevice device(width, height);

    double angle = 0;
    double angle_dlt = 2;// 弧度/s
    while (true) {
        // 清空
        clock_t last = clock();
        raster.clear(0xffffff);
        angle += angle_dlt / FPS;
        TransformMat rotate = easy3d::Transform::rotate(Point3(1, 1, 1), angle);
        vbo.setRotate(rotate);
        // 合并变化矩阵
        vbo.updateTrans();

        // 透视变换
        std::vector<Point4> points_new = vbo.doTrans(F);
        // 归一化
        for (auto iter = points_new.begin(); iter != points_new.end(); iter++) {
            *iter = orth * (*iter);
        }
        // 裁剪
        std::vector<Point3> p_clip = easy3d::Clip::clip(points_new, vbo.getPrimitive());
        // 显示线段
        int size = p_clip.size() / 2;
        for (int i = 0; i < size; i++) {
            int st = 2 * i;
            //std::cout << p_clip[st](0) << " " << p_clip[st](1) << "\n" << p_clip[st + 1](0) << " " << p_clip[st + 1](1) << "\n";
            raster.drawLine(p_clip[st](0), p_clip[st](1), p_clip[st + 1](0), p_clip[st + 1](1), 0x55FF55);
        }
        device.displayRaster(raster.getBuffer());
        // 显示瞬时帧率1s除以一帧需要的时间
        long dlt = clock() - last;
        device.outFPS(1000 / dlt);
        device.flush();
        // 延时保证FPS的帧率
        if (dlt < 1000 / FPS) {
            Sleep(1000 / FPS - dlt);
        }
    }
}
