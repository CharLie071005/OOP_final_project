#ifndef _BIT_FIELD_FILTER_H_ 
#define _BIT_FIELD_FILTER_H_ 

#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include <image.h>

//定義四個濾鏡的值
#define GRAY_BOX    0b00000001
#define GRAY_TWO    0b00000010
#define GRAY_THREE  0b00000100
#define GRAY_FOUR   0b00001000
#define RGB_BOX     0b00010000
#define RGB_TWO     0b00100000
#define RGB_THREE   0b01000000
#define RGB_FOUR    0b10000000

void Gray_Box_Filter(Image &image, int kernelSize);
void RGB_Box_Filter(Image &image, int kernelSize);

//using bitwise and to track whtat is the user's image
void loadCase(int8_t option, Image &image);

#endif