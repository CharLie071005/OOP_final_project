#include "bit_field_filter.h"

void loadCase(int8_t option, Image *image){
    if(option & GRAY_BOX){
        std::cout << endl << endl << "Load Gray Box" << endl << endl;
        Gray_Box_Filter(image, 5);
    }
<<<<<<< HEAD
    if(option & GRAY_Med){
        std::cout << endl << endl << "Load Gray Median" << endl << endl;
=======
    if(option & GRAY_TWO){
        std::cout << endl << endl << "Load Gray Two" << endl << endl;
>>>>>>> b0c8f8d17babb752b19383fc91a2e6538f821f4a
        Median_Filter_Gray(image, 3);
    }    
    if(option & GRAY_Sobel){
        std::cout << endl << endl << "Load Gray Sobel" << endl << endl;
        Sobel_Gradient_Filter_Gray(image);
    }
<<<<<<< HEAD
    if(option & GRAY_Linear){
        std::cout << endl << endl << "Load Gray Linear" << endl << endl;
        Linear_Motion_Blur_Gray(image, 90.0, 5);
=======
    if(option & GRAY_FOUR){
        std::cout << endl << endl << "Load Gray Four" << endl << endl;
        Linear_Motion_Blur_Gray(image, 0.0, 5);
>>>>>>> b0c8f8d17babb752b19383fc91a2e6538f821f4a
    }
    if(option & RGB_BOX){
        std::cout << endl << endl << "Load RGB Box" << endl << endl;
        RGB_Box_Filter(image, 5);
    }
<<<<<<< HEAD
    if(option & RGB_Med){
        std::cout << endl << endl << "Load RGB Median" << endl << endl;
=======
    if(option & RGB_TWO){
        std::cout << endl << endl << "Load RGB Two" << endl << endl;
        Median_Filter_RGB(image, 3);
>>>>>>> b0c8f8d17babb752b19383fc91a2e6538f821f4a
    }
    if(option & RGB_Sobel){
        std::cout << endl << endl << "Load RGB Sobel" << endl << endl;
        Sobel_Gradient_Filter_RGB(image);
    }
    if(option & RGB_Linear){
        std::cout << endl << endl << "Load RGB Linear" << endl << endl;
    std::cout << endl;
    }
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

    // 搜尋圖片的每一个像素（忽略邊界）
    for (int y = border; y < _h - border; y++) {
        for (int x = border; x < _w - border; x++) {
            vector<int> window;
            
            // 取得3x3的濾鏡矩陣
            for (int ky = -border; ky <= border; ky++) {
                for (int kx = -border; kx <= border; kx++) {
                    window.push_back(_pixels[y + ky][x + kx]);
                }
            }

            // 對濾鏡矩陣中的像素進行排列
            sort(window.begin(), window.end());

            // 取得中位數
            int median = window[window.size() / 2];

            // 将中位数赋值给滤波后的图像
            filtered_pixels[y][x] = median;
        }
    }

    //將套完濾鏡的pixels複製到_pixels上
    for (int y = 1; y < _h - 1; y++) {
        for (int x = 1; x < _w - 1; x++) {
            _pixels[y][x] = filtered_pixels[y][x];
        }
    }

    //刪除記憶體空間
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
    //確定是否水平的矩陣
    int GX[3][3] = {
    { 1, 0, -1 },
    { 2, 0, -2 },
    { 1, 0, -1 }
    };
    //確定是否垂直的矩陣
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

            for (int ky = -1; ky <= 1; ky++) { //把pixels做卷積
                for (int kx = -1; kx <= 1; kx++) {
                    sumX += _pixels[y + ky][x + kx] * GX[ky + 1][kx + 1];
                    sumY += _pixels[y + ky][x + kx] * GY[ky + 1][kx + 1];
                }
            }
            
            int magnitude = static_cast<int>(sqrt(sumX * sumX + sumY * sumY));
            filtered_pixels[y][x] = std::min(255, std::max(0, magnitude));
        }
    }
    //把更新的liftered_pixels更新到_pixels
    for (int y = 1; y < _h - 1; y++) {
        for (int x = 1; x < _w - 1; x++) {
            _pixels[y][x] = filtered_pixels[y][x];
        }
    }
    //釋放記憶體空間
    for (int i = 0; i < _h; i++) {
        delete[] filtered_pixels[i];
    }
    delete[] filtered_pixels;
}

void Sobel_Gradient_Filter_RGB(Image *image) {
    //確定是否水平的矩陣
    int GX[3][3] = {
    { 1, 0, -1 },
    { 2, 0, -2 },
    { 1, 0, -1 }
    };
    //確定是否垂直的矩陣
    int GY[3][3] = {
    { 1,  2,  1 },
    { 0,  0,  0 },
    { -1, -2, -1 }
    };

    int _h = image->get_height();
    int _w = image->get_width();
    int ***_pixels = image->get_3D_pixels();

    int ***filtered_pixels = new int **[_h];
    for (int i = 0; i < _h; i++) {
        filtered_pixels[i] = new int *[_w];
        for (int j = 0; j < _w; j++){
            filtered_pixels[i][j] = new int [3];
        }
    }

    for (int y = 1; y < _h - 1; y++) {
        for (int x = 1; x < _w - 1; x++) {
            int sumX_R = 0;
            int sumY_R = 0;
            int sumX_G = 0;
            int sumY_G = 0;
            int sumX_B = 0;
            int sumY_B = 0;

            for (int ky = -1; ky <= 1; ky++) { //把pixels做卷積
                for (int kx = -1; kx <= 1; kx++) {
                    sumX_R += _pixels[y + ky][x + kx][0] * GX[ky + 1][kx + 1];
                    sumY_R += _pixels[y + ky][x + kx][0] * GY[ky + 1][kx + 1];
                    sumX_G += _pixels[y + ky][x + kx][1] * GX[ky + 1][kx + 1];
                    sumY_G += _pixels[y + ky][x + kx][1] * GY[ky + 1][kx + 1];
                    sumX_B += _pixels[y + ky][x + kx][2] * GX[ky + 1][kx + 1];
                    sumY_B += _pixels[y + ky][x + kx][2] * GY[ky + 1][kx + 1];
                    
                }
            }
            
            int magnitude_R = static_cast<int>(sqrt(sumX_R * sumX_R + sumY_R * sumY_R));
            int magnitude_G = static_cast<int>(sqrt(sumX_G * sumX_G + sumY_G * sumY_G));
            int magnitude_B = static_cast<int>(sqrt(sumX_B * sumX_B + sumY_B * sumY_B));
            filtered_pixels[y][x][0] = std::min(255, std::max(0, magnitude_R));
            filtered_pixels[y][x][1] = std::min(255, std::max(0, magnitude_G));
            filtered_pixels[y][x][2] = std::min(255, std::max(0, magnitude_B));
            std::cout << "Sobel RGB 演算法正確 "  << endl;
        }
    }
    //把更新的liftered_pixels更新到_pixels
    for (int y = 1; y < _h - 1; y++) {
        for (int x = 1; x < _w - 1; x++) {
            _pixels[y][x][0] = filtered_pixels[y][x][0];
            _pixels[y][x][1] = filtered_pixels[y][x][1];
            _pixels[y][x][2] = filtered_pixels[y][x][2];
        }
    }
    //釋放記憶體空間
    for (int i = 0; i < _h; i++) {
        for (int k = 0; k < _w; k++){
            delete [] filtered_pixels[i][k];
        }
        delete [] filtered_pixels[i];
    }
    delete [] filtered_pixels;
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