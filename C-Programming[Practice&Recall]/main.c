/*
checking given number is +ve/-ve or 0
no use of if else, switch or ternery
*/
#include <stdio.h>
int main(void){
    int num;
    printf("Enter any number to check whether it is negative, zero or positive:\t");
    scanf("%d", &num);
    int check = (num > 0) - (num < 0);
    char *result[] = {"Negative", "Zero", "Positive"};
    printf("You entered %s number.\n", result [check + 1]);
return 0;
}