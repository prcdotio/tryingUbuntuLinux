/*
Testing recursion with prefix increment/decrement and postfix increment/decrement
*/

//testing via recursion
#include <stdio.h>

int factoral(int num);

int main(void){
    int num;
    printf("Enter you number to get it's corresponding factoral:\t");
    scanf("%d", &num);
    int result = factoral(num);
    printf("The corresponding factoral is:\t%d.\n", result);

    return 0;
}
int factorial(int num){
    if(num == 1 || num == 0)
        return 1;
    return num * factoral(--num);
}