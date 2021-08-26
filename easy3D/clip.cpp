#include "clip.h"

std::vector<Point3> easy3d::Clip::clip(const std::vector<Point4>& points, Primitive type) {
    if (type == Primitive::LINES) {
        return Clip::__clipLine(points);
    }
    return std::vector<Point3>();
}

// �߶βü�
std::vector<Point3> easy3d::Clip::__clipLine(const std::vector<Point4>& points) {
    std::vector<Point3> res;
    // ǰ�����������㹹��ֱ�ߣ����ص��������� ��������Ե��߶�
    int size = points.size();
    Point3 p0, p1;
    for (int i = 0; i < size - 1; i++) {
        p0 = points[i].head(3);
        p1 = points[i + 1].head(3);
        // ����������
        unsigned char code1 = Clip::__getRegionCode(points[i].head(2));
        unsigned char code2 = Clip::__getRegionCode(points[i + 1].head(2));
        // �򵥽���
        if ((code1 | code2) == 0) {
            // ��Ȼ��Ҫ��Z�����ü�
            if (Clip::__z_clip(p0, p1)) {
                res.push_back(p0);
                res.push_back(p1);
            }
            continue;
        }
        // ���ų�
        unsigned char temp = code1 & code2;
        if (temp == 1 || temp == 2 || temp == 4 || temp == 8) {
            continue;
        }
        // ���� Cyrus-Beck �㷨 ����Z�����ü�
        if (Clip::__Cyrus_Beck(p0, p1)) {
            if (Clip::__z_clip(p0, p1)) {
                res.push_back(p0);
                res.push_back(p1);
            }
        }
    }
    return res;
}

unsigned char easy3d::Clip::__getRegionCode(Point2 p) {
    double x = p(0), y = p(1);
    // ������
    if (x <= 1 && x >= -1 && y <= 1 && y >= -1) {
        return 0; // 0000
    }
    // ������ �������
    if (x <= -1) {
        if (y <= -1) {
            return 5; // 0101 ����
        }
        if (y >= 1) {
            return 9;   // 1001 ����
        }
        return 1; // 0001 ����
    }
    //������ �ұ�����
    if (x >= 1) {
        if (y <= -1) {
            return 6; // 0110 ����
        }
        if (y >= 1) {
            return 10; // 1010 ����
        }
        return 2;   // 0010 ����
    }
    // �м�����
    if (y <= -1) {
        return 4;   // 0100 ����
    }
    if (y >= 1) {
        return 8;   // 1000 ����
    }
}

// ���ؽضϺ���߶�
bool easy3d::Clip::__Cyrus_Beck(Point3& p0, Point3& p1) {
    // �����ĸ��߽��ߵĽ���
    double x0 = p0(0), y0 = p0(1), x1 = p1(0), y1 = p1(1);
    Point2 p01 = p1.head(2) - p0.head(2);
    double t[4];
    // ����
    if (x0 == x1) {
        t[0] = t[1] = -1;
    }
    else {
        t[0] = -(x0 + 1) / (x1 - x0);
        t[1] = -(x0 - 1) / (x1 - x0);
    }
    // ˮƽ��
    if (y0 == y1) {
        t[2] = t[3] = -1;
    }
    else {
        t[2] = -(y0 + 1) / (y1 - y0);
        t[3] = -(y0 - 1) / (y1 - y0);
    }
    // ���������ĸ�����ķ�����
    Point2 normal[4] = { Point2(-1, 0), Point2(1,0), Point2(0,-1), Point2(0,1) };
    // ���ݽ������뿪���ȡ����ȡ���߶Σ��ֱ��ʼ��01����ͳһ����ˮƽ��ֱ�������
    double t_PE = 0, t_PL = 1;
    for (int i = 0; i < 4; i++) {
        if (t[i] == -1) {
            continue;
        }
        if (normal[i].dot(p01) < 0 && t[i] > t_PE) {
            t_PE = t[i];
        }
        if (normal[i].dot(p01) > 0 && t[i] < t_PL) {
            t_PL = t[i];
        }
    }
    // ���������Բ�ֵ
    Point3 a_temp = linearInterpolation(p0, p1, t_PE);
    Point3 b_temp = linearInterpolation(p0, p1, t_PL);
    // �ų�б����Ȼ�����������ֱ��
    if (a_temp(0) > 1 || a_temp(1) > 1 || b_temp(0) > 1 || b_temp(1) > 1 ||
        a_temp(0) < -1 || a_temp(1) < -1 || b_temp(0) < -1 || b_temp(1) < -1) {
        return false;
    }
    p0 = a_temp;
    p1 = b_temp;
    return true;
}

// ��Z����вü�����������оټ���
bool easy3d::Clip::__z_clip(Point3& p0, Point3& p1) {
    double z0 = p0(2), z1 = p1(2);
    // ����������
    if (z0 >= -1 && z0 <= 1 && z1 >= -1 && z1 <= 1) {
        return true;
    }
    // ���������⣬����߶ξ�Ӧ�ñ��ų�
    if ((z0 < -1 && z1 < -1) || (z0 > 1 && z1 > 1)) {
        return false;
    }
    // ��Ҫ�ü������
    int flag0 = (z0 >= -1 && z0 <= 1) ? 1 : -1;
    int flag1 = (z1 >= -1 && z1 <= 1) ? 1 : -1;
    
    // �����㶼����������������ֵ
    double t0 = (1 - p0(2)) / (p1(2) - p0(2));
    double t1 = (-1 - p0(2)) / (p1(2) - p0(2));
    // һ���������� һ��������
    if(flag0 * flag1 == -1) { 
        // ��֤p0�����棬p1������
        if (flag0 == -1) {
            myswap(p0, p1);
        }
        // ��֤ t1 �ǺϷ��ģ���Ϊ�ض���һ���ǺϷ���, t0 = 0��t1 �����Ǹ��Ϸ���
        if (t0 >= -1 && t0 <= 1) {
            t1 = t0;
        }
        // t0�����Լ������
        t0 = 0;
    }
    // ���������Բ�ֵ
    Point3 a_temp = linearInterpolation(p0, p1, t0);
    Point3 b_temp = linearInterpolation(p0, p1, t1);
    p0 = a_temp;
    p1 = b_temp;
    return true;
}
