#ifndef _BIT_FIELD_FILTER_H_ 
#define _BIT_FIELD_FILTER_H_ 

#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include "image.h"
#include <math.h>

//定義四個濾鏡的值
#define GRAY_BOX    0b00000001
#define GRAY_Med    0b00000010
#define GRAY_Sobel  0b00000100
#define GRAY_Linear 0b00001000
#define RGB_BOX     0b00010000
#define RGB_Med     0b00100000
#define RGB_Sobel   0b01000000
#define RGB_Linear  0b10000000

void Gray_Box_Filter(Image *image, int kernelSize);
void RGB_Box_Filter(Image *image, int kernelSize);
void Median_Filter_Gray(Image *image, int kernel);
void Sobel_Gradient_Filter_Gray(Image *image);
void Sobel_Gradient_Filter_RGB(Image *image);
void Linear_Motion_Blur_Gray(Image *image, double angle, int kernel_size);
//using bitwise and to track whtat is the user's image
void loadCase(int8_t option, Image *image);

#endif