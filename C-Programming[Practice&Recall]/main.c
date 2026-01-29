/*
checking given number is +ve/-ve or 0
no use of if else, switch or ternery
*/
#include <stdio.h>
int main(void){
    int num = 20;
    int check = (num > 0) - (num < 0);
    char *result[] = {"Negative", "Zero", "Positive"};
    printf("%s\n", result [check + 1]);
return 0;
}