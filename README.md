# Easy3D

## 类

> 暂定类

- 图元
    - 线
    - 三角形
- 摄像机
- 投影
- 裁剪
- 光栅化 Rasterization
    - 使用easyx作为最后的显示
    - 使用`DWORD* GetImageBuffer(IMAGE* pImg = NULL);`直接操作缓冲区
    - 不涉及到纹理的线