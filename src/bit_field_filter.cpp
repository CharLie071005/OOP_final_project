#include "bit_field_filter.h"

void loadCase(int8_t option, Image &image){
    if(option & GRAY_BOX)
        Gray_Box_Filter(image, 3);
    if(option & GRAY_TWO)
        Median_Filter_Gray(image);
    if(option & GRAY_THREE)
        Sobel_gradient_Filter_Gray(image);
    if(option & GRAY_FOUR)
        //printf("Case 4 detected\n");
    if(option & RGB_BOX)
        RGB_Box_Filter(image, 3);
    if(option & RGB_TWO)
        //printf("Case 2 detected\n");
    if(option & RGB_THREE)
        //printf("Case 3 detected\n");
    if(option & RGB_FOUR)
        //printf("Case 4 detected\n");
    std::cout << endl;
}
void Gray_Box_Filter(Image &image, int kernelSize){
    int _h = image.get_height();
    int _w = image.get_width();
    int **_pixels = image.get_pixels(); 
    
    int **tmp_pixels = new int*[_h];
    for (int i=0 ; i < _h; i++){
        tmp_pixels[i] = new int [_w];
    }
    
    int bound = kernelSize / 2;  //bound表示要取平均值的範圍 
                                 //ex:kernel =3， 表示要取+-3/2範圍，即3*3的矩陣
    for (int y = 0; y < _h; ++y) {
        for (int x = 0; x < _w; ++x) {
            int sum =0, count =0;
            for (int K_y = -bound; K_y <= bound; ++K_y) {  //K_x, K_y指出kernel矩陣的範圍
                for (int K_x = -bound; K_x <= bound; ++K_x) {
                    int ny = y + K_y;  
                    int nx = x + K_x;
                    if (ny >= 0 && ny < _h && nx >= 0 && nx < _w) {
                        sum += _pixels[ny][nx];
                        ++count;
                    }
                }
            }
            tmp_pixels[y][x] = sum / count;
        }
    }
    for (int y=0; y < _h; ++y){
        for (int x=0; x < _w; ++x){
            _pixels[y][x] = tmp_pixels[y][x];
        }
    }
    //delete tmp_pixels
    for (int i=0 ; i < _h; i++){
        delete [] tmp_pixels[i];
    }
    delete [] tmp_pixels;

}

void RGB_Box_Filter(Image &image, int kernelSize){
    int _h = image.get_height();
    int _w = image.get_width();
    int **_pixels = image.get_pixels(); 
    
    int **tmp_pixels = new int*[_h];
    for (int i=0 ; i < _h; i++){
        tmp_pixels[i] = new int [_w];
    }
    
    int bound = kernelSize / 2;  //bound表示要取平均值的範圍 
                                 //ex:kernel =3， 表示要取+-3/2範圍，即3*3的矩陣
    for (int y = 0; y < _h; ++y) {
        for (int x = 0; x < _w; ++x) {
            int sum =0, count =0;
            for (int K_y = -bound; K_y <= bound; ++K_y) {  //K_x, K_y指出kernel矩陣的範圍
                for (int K_x = -bound; K_x <= bound; ++K_x) {
                    int ny = y + K_y;  
                    int nx = x + K_x;
                    if (ny >= 0 && ny < _h && nx >= 0 && nx < _w) {
                        sum += _pixels[ny][nx];
                        ++count;
                    }
                }
            }
            tmp_pixels[y][x] = sum / count;
        }
    }
    for (int y=0; y < _h; ++y){
        for (int x=0; x < _w; ++x){
            _pixels[y][x] = tmp_pixels[y][x];
        }
    }
    //delete tmp_pixels
    for (int i=0 ; i < _h; i++){
        delete [] tmp_pixels[i];
    }
    delete [] tmp_pixels;

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

void Linear_Motion_Blur(Image &image, double angle, int kernel_size) {
    int width = image.get_width();
    int height = image.get_height();
    int **pixels = image.get_pixels();

    // Generate motion blur kernel
    std::vector<double> kernel(kernel_size, 1.0 / kernel_size); // Simple averaging kernel

    // Compute motion direction components
    double angle_rad = angle * M_PI / 180.0;
    double dx = cos(angle_rad);
    double dy = sin(angle_rad);

    // Apply the kernel in the direction specified
    int half_size = kernel_size / 2;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double sum = 0.0;
            for (int k = -half_size; k <= half_size; k++) {
                int new_x = x + round(k * dx);
                int new_y = y + round(k * dy);
                if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height) {
                    sum += kernel[k + half_size] * pixels[new_y][new_x];
                }
            }
            pixels[y][x] = round(sum);
        }
    }
}