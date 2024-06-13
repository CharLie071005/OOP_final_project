#ifndef _BIT_FIELD_FILTER_H_ 
#define _BIT_FIELD_FILTER_H_ 

#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include "image.h"

//定義四個濾鏡的值
#define GRAY_BOX    0b00000001
#define GRAY_TWO    0b00000010
#define GRAY_THREE  0b00000100
#define GRAY_FOUR   0b00001000
#define RGB_BOX     0b00010000
#define RGB_TWO     0b00100000
#define RGB_THREE   0b01000000
#define RGB_FOUR    0b10000000

void Gray_Box_Filter(Image &image);
void RGB_Box_Filter(Image &image);
void Median_Filter_Gray(Image &image);
void Sobel_gradient_Filter(Image &image);

//using bitwise and to track whtat is the user's option
void loadCase(int8_t Opt, Image &image){
    if(Opt & GRAY_BOX)
        Gray_Box_Filter(image);
    if(Opt & GRAY_TWO)
        Median_Filter_Gray(image);
    if(Opt & GRAY_THREE)
        Sobel_gradient_Filter_Gray(image);
    if(Opt & GRAY_FOUR)
        //printf("Case 4 detected\n");
    if(Opt & RGB_BOX)
        RGB_Box_Filter(image);
    if(Opt & RGB_TWO)
        //printf("Case 2 detected\n");
    if(Opt & RGB_THREE)
        //printf("Case 3 detected\n");
    if(Opt & RGB_FOUR)
        //printf("Case 4 detected\n");
    std::cout << endl;
}

#endif