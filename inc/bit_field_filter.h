#ifndef _BIT_FIELD_FILTER_H_ 
#define _BIT_FIELD_FILTER_H_ 

#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <string>

//定義四個濾鏡的值
#define GRAY_BOX    0b00000001
#define GRAY_TWO    0b00000010
#define GRAY_THREE  0b00000100
#define GRAY_FOUR   0b00001000
#define RGB_BOX     0b00010000
#define RGB_TWO     0b00100000
#define RGB_THREE   0b01000000
#define RGB_FOUR    0b10000000

void Gray_Box_Filter(Image image);

//using bitwise and to track whtat is the user's option
void loadCase(int8_t image){
    if(option & GRAY_BOX)
        Gray_Box_Filter(Image image);
    if(option & GRAY_TWO)
        //printf("Case 2 detected\n");
    if(option & GRAY_THREE)
        //printf("Case 3 detected\n");
    if(option & GRAY_FOUR)
        //printf("Case 4 detected\n");
    if(option & RGB_BOX)
        RGB_Box_Filter(Image image);
    if(option & RGB_TWO)
        //printf("Case 2 detected\n");
    if(option & RGB_THREE)
        //printf("Case 3 detected\n");
    if(option & RGB_FOUR)
        //printf("Case 4 detected\n");
    std::cout << endl;
}

#endif