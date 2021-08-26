//@Time: 2021/8/26
//@Brief: ʾ������0����������߿�ͼ��ͶӰ���ü�����Ⱦ����
#include "examples.h"

void example0() {
    // ֡��
    const int FPS = 60;
    easy3d::VBO vbo;
    // ����������
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
    // ��ȡ����
    Point3 eye(0, 1, 1), center(0, 0, 0), up(0, 1, 0);
    // ���
    TransformMat camera = easy3d::Transform::camera(eye, center, up);
    // ͸�ӱ任
    TransformMat perspective = easy3d::Transform::perspective();
    TransformMat F = perspective * camera;
    // ����ͶӰ��һ������
    TransformMat orth = easy3d::Transform::orth_uniform(3.14 / 4, 640.0 / 480, 0.01, 99);

    // ��ʾ�豸
    int width = 640, height = 480;
    easy3d::Rasteration raster(width, height);
    easy3d::GraphicsDevice device(width, height);

    double angle = 0;
    double angle_dlt = 2;// ����/s
    while (true) {
        // ���
        clock_t last = clock();
        raster.clear(0xffffff);
        angle += angle_dlt / FPS;
        TransformMat rotate = easy3d::Transform::rotate(Point3(1, 1, 1), angle);
        vbo.setRotate(rotate);
        // �ϲ��仯����
        vbo.updateTrans();

        // ͸�ӱ任
        std::vector<Point4> points_new = vbo.doTrans(F);
        // ��һ��
        for (auto iter = points_new.begin(); iter != points_new.end(); iter++) {
            *iter = orth * (*iter);
        }
        // �ü�
        std::vector<Point3> p_clip = easy3d::Clip::clip(points_new, vbo.getPrimitive());
        // ��ʾ�߶�
        int size = p_clip.size() / 2;
        for (int i = 0; i < size; i++) {
            int st = 2 * i;
            //std::cout << p_clip[st](0) << " " << p_clip[st](1) << "\n" << p_clip[st + 1](0) << " " << p_clip[st + 1](1) << "\n";
            raster.drawLine(p_clip[st](0), p_clip[st](1), p_clip[st + 1](0), p_clip[st + 1](1), 0x55FF55);
        }
        device.displayRaster(raster.getBuffer());
        // ��ʾ˲ʱ֡��1s����һ֡��Ҫ��ʱ��
        long dlt = clock() - last;
        device.outFPS(1000 / dlt);
        device.flush();
        // ��ʱ��֤FPS��֡��
        if (dlt < 1000 / FPS) {
            Sleep(1000 / FPS - dlt);
        }
    }
}
