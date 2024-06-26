#ifndef _BIT_FIELD_FILTER_H_ 
#define _BIT_FIELD_FILTER_H_ 

#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include "image.h"
#include <math.h>

//definition of bit to choose filter
#define GRAY_BOX       0b00000001
#define GRAY_Med       0b00000010
#define GRAY_Sobel     0b00000100
#define GRAY_Linear    0b00001000
#define GRAY_Stretch   0b00010000
#define GRAY_Histogram 0b00100000
#define RGB_BOX        0b00000001
#define RGB_Med        0b00000010
#define RGB_Sobel      0b00000100
#define RGB_Linear     0b00001000
#define RGB_Stretch    0b00010000
#define RGB_Histogram  0b00100000
#define GRAY           0b01000000
#define RGB            0b10000000
//search stdint.h

//The Case loading function 
bool loadCase(int8_t option, Image *image);

//funtion of filters
void Gray_Box_Filter(Image *image, int kernelSize);
void RGB_Box_Filter(Image *image, int kernelSize);
void Median_Filter_Gray(Image *image, int kernel);
void Median_Filter_RGB(Image *image, int kernel);
void Sobel_Gradient_Filter_Gray(Image *image);
void Sobel_Gradient_Filter_RGB(Image *image);
void Linear_Motion_Blur_Gray(Image *image, double angle, int kernel_size);
void Linear_Motion_Blur_RGB(Image *image, double angle, int kernel_size);
void Contrast_Stretching_Gray(Image *image);
void Contrast_Stretching_RGB(Image *image);
void Histogram_Equalization_Gray(Image *image);
void Histogram_Equalization_RGB(Image *image);

#endif