#include "bit_field_filter.h"

void Gray_Box_Filter(Image &image){
    int _h = image.get_height();
    int _w = image.get_width();
    int **_pixels = image.get_pixels();
    
    
}

void Median_Filter_Gray(Image &image, int kernel) {
    int _h = image.get_height();
    int _w = image.get_width();
    int border = kernel / 2;
    int **_pixels = image.get_pixels();
    int **filtered_pixels = new int*[_h];

    for (int i = 0; i < _h; i++) {
        filtered_pixels[i] = new int[_w];
    }

    // 遍历图像的每一个像素（忽略边缘像素）
    for (int y = border; y < _h - border; y++) {
        for (int x = border; x < _w - border; x++) {
            vector<int> window;
            
            // 获取3x3窗口的像素值
            for (int ky = -border; ky <= border; ky++) {
                for (int kx = -border; kx <= border; kx++) {
                    window.push_back(_pixels[y + ky][x + kx]);
                }
            }

            // 对窗口中的像素值进行排序
            sort(window.begin(), window.end());

            // 获取中位数
            int median = window[window.size() / 2];

            // 将中位数赋值给滤波后的图像
            filtered_pixels[y][x] = median;
        }
    }

    // 将滤波结果复制回原图像
    for (int y = 1; y < _h - 1; y++) {
        for (int x = 1; x < _w - 1; x++) {
            _pixels[y][x] = filtered_pixels[y][x];
        }
    }

    // 释放分配的内存
    for (int i = 0; i < _h; i++) {
        delete[] filtered_pixels[i];
    }
    delete[] filtered_pixels;
}

void Sobel_Gradient_Filter_Gray(Image &image) {

    int Gx[3][3] = {
    { 1, 0, -1 },
    { 2, 0, -2 },
    { 1, 0, -1 }
    };

    int Gy[3][3] = {
    { 1,  2,  1 },
    { 0,  0,  0 },
    { -1, -2, -1 }
    };

    int _h = image.get_height();
    int _w = image.get_width();
    int **_pixels = image.get_pixels();

    int **gradient = new int*[_h];
    for (int i = 0; i < _h; i++) {
        gradient[i] = new int[_w];
    }

    for (int y = 1; y < _h - 1; y++) {
        for (int x = 1; x < _w - 1; x++) {
            int gx = 0;
            int gy = 0;

            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    gx += _pixels[y + ky][x + kx] * Gx[ky + 1][kx + 1];
                    gy += _pixels[y + ky][x + kx] * Gy[ky + 1][kx + 1];
                }
            }

            gradient[y][x] = sqrt(gx * gx + gy * gy);
        }
    }

    for (int y = 1; y < _h - 1; y++) {
        for (int x = 1; x < _w - 1; x++) {
            _pixels[y][x] = gradient[y][x];
        }
    }

    for (int i = 0; i < _h; i++) {
        delete[] gradient[i];
    }
    delete[] gradient;
}