// Trying recursion to calculate factoral

#include <stdio.h>
int fact(int num);
int main(void){
    int n;
    printf("Enter any number to get it's corresponding factoral:\t");
    scanf("%d", &n);
    if(n < 0){
        printf("F*ck U, Don't try to be oversmart. It's undefined for negative itegers.\n");
        return -1;
    }else if(n > 12){
        printf("F*c* U, Don't try to be oversmart. It's just 64 bit system and compiler is just built for 32 bit handling. Don't try to calculate larger number otherwise you will get inaccurate value.\n");
        return 13;
    }else{
    int result = fact(n);
    printf("The corresponding factoral is: %d\n", result);
    }

    return 0;
}
int fact(int num){
    if(num == 1 || num == 0)
    return 1;
    return num * fact(num - 1);
}