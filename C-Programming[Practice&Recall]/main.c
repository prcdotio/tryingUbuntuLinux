// Trying recursion to calculate factoral

#include <stdio.h>
int fact(int num);
int main(void){
    int n;
    printf("Enter any number to get it's corresponding factoral:\t");
    scanf("%d", &n);
    int result = fact(n);
    printf("The corresponding factoral is: %d\n", result);

    return 0;
}
int fact(int num){
    if(num == 1 || num == 0)
    return 1;
    return num * fact(num - 1);
}