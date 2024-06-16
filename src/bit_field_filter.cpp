#include "bit_field_filter.h"

bool loadCase(int8_t option, Image *image){
    //image can only be gray or rgb -> if option in gray and rgb in same time => error
    if (option & (RGB) && (option & GRAY)){
        cout << "Invalid option !" << endl;
        return false;
    }   
    if(option & GRAY_BOX){
        std::cout << endl << endl << "Load Gray Box" << endl << endl;
        Gray_Box_Filter(image, 5);
    }
    if(option & GRAY_Med){
        std::cout << endl << endl << "Load Gray med" << endl << endl;
        Median_Filter_Gray(image, 5);
    }    
    if(option & GRAY_Sobel){
        std::cout << endl << endl << "Load Gray Sobel" << endl << endl;
        Sobel_Gradient_Filter_Gray(image);
    }
    if(option & GRAY_Linear){
        std::cout << endl << endl << "Load Gray Linear" << endl << endl;
        Linear_Motion_Blur_Gray(image, 90.0, 10);
    }
    if(option & RGB_BOX){
        std::cout << endl << endl << "Load RGB Box" << endl << endl;
        RGB_Box_Filter(image, 5);
    }
    if(option & RGB_Med){
        std::cout << endl << endl << "Load RGB Med" << endl << endl;
        Median_Filter_RGB(image, 5);
    }
    if(option & RGB_Sobel){
        std::cout << endl << endl << "Load RGB Sobel" << endl << endl;
        Sobel_Gradient_Filter_RGB(image);
    }
    if(option & RGB_Linear){
        std::cout << endl << endl << "Load RGB Linear" << endl << endl;
        Linear_Motion_Blur_RGB(image, 90.0, 10);
    }
    return true;
}

void Gray_Box_Filter(Image *image, int kernelSize){
    int _h = image->get_height();
    int _w = image->get_width();
    int **_pixels = image->get_pixels();  
    int **tmp_pixels = new int*[_h];
    for (int i=0 ; i < _h; i++){
        tmp_pixels[i] = new int [_w];
    }
    
    int bound = kernelSize / 2;  //bound represent the range wdth of matrix to get average 
                                 //ex:kernel =3， than the range is a 3x3 matrix with width of 1
    for (int y = 0; y < _h; ++y) {
        for (int x = 0; x < _w; ++x) {
            int sum =0, count =0;
            for (int K_y = -bound; K_y <= bound; ++K_y) {  //K_x, K_y indicate process of the average matrix
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
    //copy value
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
    
    int bound = kernelSize / 2;  
    for (int y = 0; y < _h; ++y) {
        for (int x = 0; x < _w; ++x) {
            int sumR =0,sumG =0,sumB =0, count =0;
            for (int K_y = -bound; K_y <= bound; ++K_y) {  
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
    //copy value
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

    //search every pixels in photo(ignore the bound)
    for (int y = border; y < _h - border; y++) {
        for (int x = border; x < _w - border; x++) {           
            //get kernel*kernel filter matrix, use vector to store it
            vector<int> window;
            for (int ky = -border; ky <= border; ky++) {
                for (int kx = -border; kx <= border; kx++) {
                    window.push_back(_pixels[y + ky][x + kx]);
                }
            }

            //sort the vector
            sort(window.begin(), window.end());

            //get median value of pixles
            int median = window[window.size() / 2];

            //copy median
            filtered_pixels[y][x] = median;
        }
    }

    //make every value in _pixels equals to median
    for (int y = 1; y < _h - 1; y++) {
        for (int x = 1; x < _w - 1; x++) {
            _pixels[y][x] = filtered_pixels[y][x];
        }
    }

    //release memory space
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
    
    //search every pixels in photo(ignore the bound)
    for (int y = border; y < _h - border; y++) {
        for (int x = border; x < _w - border; x++) {
            //get kernel*kernel filter matrix, use vector to store it
            vector<int> windowR;
            vector<int> windowG;
            vector<int> windowB;
            for (int ky = -border; ky <= border; ky++) {
                for (int kx = -border; kx <= border; kx++) {
                    windowR.push_back(_pixels[y + ky][x + kx][0]);
                    windowG.push_back(_pixels[y + ky][x + kx][1]);
                    windowB.push_back(_pixels[y + ky][x + kx][2]);
                }
            }

            //sort the vector
            sort(windowR.begin(), windowR.end());
            sort(windowG.begin(), windowG.end());
            sort(windowB.begin(), windowB.end());

            //get median value of pixles
            int medianR = windowR[windowR.size() / 2];
            int medianG = windowG[windowG.size() / 2];
            int medianB = windowB[windowB.size() / 2];

            //copy median
            filtered_pixels[y][x][0] = medianR;
            filtered_pixels[y][x][1] = medianG;
            filtered_pixels[y][x][2] = medianB;
        }
    }

    //make every value in _pixels equals to median
    for (int y = 1; y < _h - 1; y++) {
        for (int x = 1; x < _w - 1; x++) {
            _pixels[y][x][0] = filtered_pixels[y][x][0];
            _pixels[y][x][1] = filtered_pixels[y][x][1];
            _pixels[y][x][2] = filtered_pixels[y][x][2];
        }
    }

    //release memory space
    for (int i = 0; i < _h; i++) {
        for (int j = 0; j < _w; j++) {
            delete[] filtered_pixels[i][j];
        }
        delete[] filtered_pixels[i];
    }
    delete[] filtered_pixels;
}

void Sobel_Gradient_Filter_Gray(Image *image) {
    //matrix to check if parallel
    int GX[3][3] = {
    { 1, 0, -1 },
    { 2, 0, -2 },
    { 1, 0, -1 }
    };
    //matrix to check if orthogonal
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

            for (int ky = -1; ky <= 1; ky++) { //integrals the pixels
                for (int kx = -1; kx <= 1; kx++) {
                    sumX += _pixels[y + ky][x + kx] * GX[ky + 1][kx + 1];
                    sumY += _pixels[y + ky][x + kx] * GY[ky + 1][kx + 1];
                }
            }
            
            int magnitude = static_cast<int>(sqrt(sumX * sumX + sumY * sumY));
            filtered_pixels[y][x] = std::min(255, std::max(0, magnitude));
        }
    }
    //copy filtered_pixels to pixels
    for (int y = 1; y < _h - 1; y++) {
        for (int x = 1; x < _w - 1; x++) {
            _pixels[y][x] = filtered_pixels[y][x];
        }
    }
    //release memory space
    for (int i = 0; i < _h; i++) {
        delete[] filtered_pixels[i];
    }
    delete [] filtered_pixels;
    filtered_pixels = nullptr;
}

void Sobel_Gradient_Filter_RGB(Image *image) {
    //matrix to check if parallel
    int GX[3][3] = {
    { 1, 0, -1 },
    { 2, 0, -2 },
    { 1, 0, -1 }
    };
    //matrix to check if orthogonal
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

            for (int ky = -1; ky <= 1; ky++) { //integral the _pixels
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
        }
    }
    //copy filtered_pixels to _pixels
    for (int y = 1; y < _h - 1; y++) {
        for (int x = 1; x < _w - 1; x++) {
            _pixels[y][x][0] = filtered_pixels[y][x][0];
            _pixels[y][x][1] = filtered_pixels[y][x][1];
            _pixels[y][x][2] = filtered_pixels[y][x][2];
        }
    }
    //release memory space
    for (int i = 0; i < _h; i++) {
        for (int k = 0; k < _w; k++){
            delete [] filtered_pixels[i][k];
        }
        delete [] filtered_pixels[i];
    }
    delete [] filtered_pixels;
    filtered_pixels = nullptr;
}

void Linear_Motion_Blur_Gray(Image *image, double angle, int kernel_size) {
    int width = image->get_width();
    int height = image->get_height();
    int **pixels = image->get_pixels();

    // construct blurmatrix whose length equal to kernel and value is 1/kernel
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

void Linear_Motion_Blur_RGB(Image *image, double angle, int kernel_size) {
    int width = image->get_width();
    int height = image->get_height();
    int ***pixels = image->get_3D_pixels();

    // construct blurmatrix whose length equal to kernel and value is 1/kernel
    std::vector<double> kernel(kernel_size, 1.0 / kernel_size); // Simple averaging kernel

    // Compute motion direction components
    double angle_rad = angle * M_PI / 180.0;
    double dx = cos(angle_rad);
    double dy = sin(angle_rad);

    // Apply the kernel in the direction specified
    int half_size = kernel_size / 2;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double sumR = 0.0;
            double sumG = 0.0;
            double sumB = 0.0;
            for (int k = -half_size; k <= half_size; k++) {
                int new_x = x + round(k * dx);
                int new_y = y + round(k * dy);
                if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height) {
                    sumR += kernel[k + half_size] * pixels[new_y][new_x][0];
                    sumG += kernel[k + half_size] * pixels[new_y][new_x][1];
                    sumB += kernel[k + half_size] * pixels[new_y][new_x][2];
                }
            }
            pixels[y][x][0] = round(sumR);
            pixels[y][x][1] = round(sumG);
            pixels[y][x][2] = round(sumB);
        }
    }
}

int map_pixel_value(int pixel) {
    if (pixel >= 0 && pixel <= 25)
        return static_cast<int>(12.0 * pixel / 25.0);
    else if (pixel > 25 && pixel <= 76)
        return static_cast<int>(26.0 * (pixel - 25) / 51.0 + 12);
    else if (pixel > 76 && pixel <= 178)
        return static_cast<int>(178.0 * (pixel - 76) / 102.0 + 38);
    else if (pixel > 178 && pixel <= 229)
        return static_cast<int>(26.0 * (pixel - 178) / 51.0 + 216);
    else if (pixel > 229 && pixel <= 255)
        return static_cast<int>(13.0 * (pixel - 229) / 26.0 + 242);
    return pixel; // 处理异常值
}

void Contrast_Stretching_Gray(Image *image) {
    int width = image->get_width();
    int height = image->get_height();
    int **pixels = image->get_pixels();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixels[y][x] = map_pixel_value(pixels[y][x]);
        }
    }
}

void Contrast_Stretching_RGB(Image *image) {
    int width = image->get_width();
    int height = image->get_height();
    int ***pixels = image->get_3D_pixels();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pixels[y][x][0] = map_pixel_value(pixels[y][x][0]);
            pixels[y][x][1] = map_pixel_value(pixels[y][x][1]);
            pixels[y][x][2] = map_pixel_value(pixels[y][x][2]);
        }
    }
}

void Histogram_Equalization_Gray(Image *image) {
    int height = image->get_height();
    int width = image->get_width();
    int **pixels = image->get_pixels();
    vector<int> histogram(256, 0);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            histogram[pixels[y][x]]++;
        }
    }

    vector<int> cdf(256, 0);
    cdf[0] = histogram[0];
    for (int i = 1; i < 256; i++) {
        cdf[i] = cdf[i - 1] + histogram[i];
    }

    int cdf_min = min_element(cdf.begin(), cdf.end());
    int total_pixels = height * width;
    vector<int> filtered(256, 0);
    for (int i = 0; i < 256; i++) {
        filtered[i] = round((float)(cdf[i] - cdf_min) / (total_pixels - cdf_min) * 255);
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            pixels[y][x] = filtered[pixels[y][x]];
        }
    }
}

void Histogram_Equalization_RGB(Image *image) {
    int height = image->get_height();
    int width = image->get_width();
    int ***pixels = image->get_3D_pixels();
    vector<int> histogramR(256, 0);
    vector<int> histogramG(256, 0);
    vector<int> histogramB(256, 0);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            histogramR[pixels[y][x][0]]++;
            histogramG[pixels[y][x][1]]++;
            histogramB[pixels[y][x][2]]++;
        }
    }

    vector<int> cdfR(256, 0);
    vector<int> cdfG(256, 0);
    vector<int> cdfB(256, 0);

    cdfR[0] = histogramR[0];
    cdfG[0] = histogramG[0];
    cdfB[0] = histogramB[0];

    for (int i = 1; i < 256; i++) {
        cdfR[i] = cdfR[i - 1] + histogramR[i];
        cdfG[i] = cdfG[i - 1] + histogramG[i];
        cdfB[i] = cdfB[i - 1] + histogramB[i];
    }

    int cdfR_min = min_element(cdfR.begin(), cdfR.end());
    int cdfG_min = min_element(cdfG.begin(), cdfG.end());
    int cdfB_min = min_element(cdfB.begin(), cdfB.end());

    int total_pixels = height * width;
    vector<int> filtered(256, 0);
    for (int i = 0; i < 256; i++) {
        filteredR[i] = round((float)(cdfR[i] - cdf_min) / (total_pixels - cdf_min) * 255);
        filteredG[i] = round((float)(cdfG[i] - cdf_min) / (total_pixels - cdf_min) * 255);
        filteredB[i] = round((float)(cdfB[i] - cdf_min) / (total_pixels - cdf_min) * 255);
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            pixels[y][x][0] = filteredR[pixels[y][x]];
            pixels[y][x][1] = filteredG[pixels[y][x]];
            pixels[y][x][2] = filteredB[pixels[y][x]];
        }
    }
}