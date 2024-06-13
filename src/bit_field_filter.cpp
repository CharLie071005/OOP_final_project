#include "bit_field_filter.h"

void loadCase(int8_t option, Image &image){
    if(option & GRAY_BOX)
        Gray_Box_Filter(image, 3);
    if(option & GRAY_TWO)
        //printf("Case 2 detected\n");
    if(option & GRAY_THREE)
        //printf("Case 3 detected\n");
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