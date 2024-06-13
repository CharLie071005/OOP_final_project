#include <stdio.h>
#include <stdint.h>

/*定義四個濾鏡的值
#define Box_Filter    0b00000001
#define CASE_TWO    0b00000010
#define CASE_THREE  0b00000100
#define CASE_FOUR   0b00001000

//using bitwise and to track whtat is the user's option
void loadCase(int8_t image){
    if(option & CASE_ONE)
        //
    if(option & CASE_TWO)
        //printf("Case 2 detected\n");
    if(option & CASE_THREE)
        //printf("Case 3 detected\n");
    if(option & CASE_FOUR)
        //printf("Case 4 detected\n");
    printf("\n");
    printAndResult(option);
}

int main(){
    //test1:
    uint8_t option = 0b00001001;
    printf("test1:\n");
    loadCase(option);

    //test2:
    printf("test2:\n");
    loadCase(CASE_ONE | CASE_TWO);

    //test3:
    printf("test3:\n");
    loadCase(CASE_ONE | CASE_TWO | CASE_THREE | CASE_FOUR);
    return 0;
}*/