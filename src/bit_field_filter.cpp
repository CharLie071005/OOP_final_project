#include "bit_field_filter.h"

void loadCase(int8_t option, Image *image){
    if(option & GRAY_BOX){
        std::cout << endl << endl << "Load Gray Box" << endl << endl;
        Gray_Box_Filter(image, 5);
    }
    if(option & GRAY_TWO){
        std::cout << endl << endl << "Load Gray Two" << endl << endl;
        Median_Filter_Gray(image, 3);
    }    
    if(option & GRAY_THREE){
        std::cout << endl << endl << "Load Gray Three" << endl << endl;
        Sobel_Gradient_Filter_Gray(image);
    }
    if(option & GRAY_FOUR){
        std::cout << endl << endl << "Load Gray Four" << endl << endl;
        Linear_Motion_Blur_Gray(image, 0.0, 5);
    }
    if(option & RGB_BOX){
        std::cout << endl << endl << "Load RGB Box" << endl << endl;
        RGB_Box_Filter(image, 5);
    }
    if(option & RGB_TWO){
        std::cout << endl << endl << "Load RGB Two" << endl << endl;
        Median_Filter_RGB(image, 3);
    }
    if(option & RGB_THREE)
        //printf("Case 3 detected\n");
    if(option & RGB_FOUR)
        //printf("Case 4 detected\n");
    std::cout << endl;
}

void Gray_Box_Filter(Image *image, int kernelSize){
    int _h = image->get_height();
    int _w = image->get_width();
    int **_pixels = image->get_pixels(); 
    
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

void RGB_Box_Filter(Image *image, int kernelSize){
    int _h = image->get_height();
    int _w = image->get_width();
    int ***_pixels = image->get_3D_pixels(); 
    
    int ***tmp_pixels = new int**[_h];
    for (int i=0 ; i < _h; i++){
        tmp_pixels[i] = new int *[_w];
        for (int j=0; j < _w; j++){
            tmp_pixels[i][j] = new int [3];
        }
    }
    
    int bound = kernelSize / 2;  //bound表示要取平均值的範圍 
                                 //ex:kernel =3， 表示要取+-3/2範圍，即3*3的矩陣
    for (int y = 0; y < _h; ++y) {
        for (int x = 0; x < _w; ++x) {
            int sumR =0,sumG =0,sumB =0, count =0;
            for (int K_y = -bound; K_y <= bound; ++K_y) {  //K_x, K_y指出kernel矩陣的範圍
                for (int K_x = -bound; K_x <= bound; ++K_x) {
                    int ny = y + K_y;  
                    int nx = x + K_x;
                    if (ny >= 0 && ny < _h && nx >= 0 && nx < _w) {
                        sumR += _pixels[ny][nx][0];
                        sumG += _pixels[ny][nx][1];
                        sumB += _pixels[ny][nx][2];
                        ++count;
                    }
                }
            }
            tmp_pixels[y][x][0] = sumR / count;
            tmp_pixels[y][x][1] = sumG / count;
            tmp_pixels[y][x][2] = sumB / count;
        }
    }
    for (int y=0; y < _h; ++y){
        for (int x=0; x < _w; ++x){
            for (int i=0; i<3; ++i){
            _pixels[y][x][i] = tmp_pixels[y][x][i];
            }
        }
    }
    //delete tmp_pixels
    for (int i=0; i < _h; ++i){
        for (int j=0; j < _w; ++j){
            delete [] tmp_pixels[i][j];
        }
    }
    for (int i=0; i < _h; ++i){
        delete [] tmp_pixels[i];
    }
    delete [] tmp_pixels;

}

void Median_Filter_Gray(Image *image, int kernel) {
    int _h = image->get_height();
    int _w = image->get_width();
    int border = kernel / 2;
    int **_pixels = image->get_pixels();
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

void Median_Filter_RGB(Image *image, int kernel) {
    int _h = image->get_height();
    int _w = image->get_width();
    int border = kernel / 2;
    int ***_pixels = image->get_3D_pixels();
    int ***filtered_pixels = new int**[_h];

    for (int i = 0; i < _h; i++) {
        filtered_pixels[i] = new int*[_w];
        for (int j = 0; j < _w; j++) {
            filtered_pixels[i][j] = new int[3];
        }
    }
    
    // 遍历图像的每一个像素（忽略边缘像素）
    for (int y = border; y < _h - border; y++) {
        for (int x = border; x < _w - border; x++) {
            vector<int> windowR;
            vector<int> windowG;
            vector<int> windowB;

            // 获取3x3窗口的像素值
            for (int ky = -border; ky <= border; ky++) {
                for (int kx = -border; kx <= border; kx++) {
                    windowR.push_back(_pixels[y + ky][x + kx][0]);
                    windowG.push_back(_pixels[y + ky][x + kx][1]);
                    windowB.push_back(_pixels[y + ky][x + kx][2]);
                }
            }

            // 对窗口中的像素值进行排序
            sort(windowR.begin(), windowR.end());
            sort(windowG.begin(), windowG.end());
            sort(windowB.begin(), windowB.end());

            // 获取中位数
            int medianR = windowR[windowR.size() / 2];
            int medianG = windowG[windowG.size() / 2];
            int medianB = windowB[windowB.size() / 2];

            // 将中位数赋值给滤波后的图像
            filtered_pixels[y][x][0] = medianR;
            filtered_pixels[y][x][1] = medianG;
            filtered_pixels[y][x][2] = medianB;
        }
    }

    // 将滤波结果复制回原图像
    for (int y = 1; y < _h - 1; y++) {
        for (int x = 1; x < _w - 1; x++) {
            _pixels[y][x][0] = filtered_pixels[y][x][0];
            _pixels[y][x][1] = filtered_pixels[y][x][1];
            _pixels[y][x][2] = filtered_pixels[y][x][2];
        }
    }

    // 释放分配的内存
    for (int i = 0; i < _h; i++) {
        for (int j = 0; j < _w; j++) {
            delete[] filtered_pixels[i][j];
        }
        delete[] filtered_pixels[i];
    }
    delete[] filtered_pixels;
}

void Sobel_Gradient_Filter_Gray(Image *image) {

    int GX[3][3] = {
    { 1, 0, -1 },
    { 2, 0, -2 },
    { 1, 0, -1 }
    };

    int GY[3][3] = {
    { 1,  2,  1 },
    { 0,  0,  0 },
    { -1, -2, -1 }
    };

    int _h = image->get_height();
    int _w = image->get_width();
    int **_pixels = image->get_pixels();

    int **filtered_pixels = new int*[_h];
    for (int i = 0; i < _h; i++) {
        filtered_pixels[i] = new int[_w];
    }

    for (int y = 1; y < _h - 1; y++) {
        for (int x = 1; x < _w - 1; x++) {
            int sumX = 0;
            int sumY = 0;

            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    sumX += _pixels[y + ky][x + kx] * GX[ky + 1][kx + 1];
                    sumY += _pixels[y + ky][x + kx] * GY[ky + 1][kx + 1];
                }
            }

            int magnitude = static_cast<int>(sqrt(sumX * sumX + sumY * sumY));
            filtered_pixels[y][x] = std::min(255, std::max(0, magnitude));
        }
    }

    for (int y = 1; y < _h - 1; y++) {
        for (int x = 1; x < _w - 1; x++) {
            _pixels[y][x] = filtered_pixels[y][x];
        }
    }

    for (int i = 0; i < _h; i++) {
        delete[] filtered_pixels[i];
    }
    delete[] filtered_pixels;
}

void Linear_Motion_Blur_Gray(Image *image, double angle, int kernel_size) {
    int width = image->get_width();
    int height = image->get_height();
    int **pixels = image->get_pixels();

    // 建立長度為kernel每個數值皆為kernel分之一的模糊矩陣
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