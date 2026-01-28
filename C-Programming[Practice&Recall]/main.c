#include <stdio.h>
int main(void){
    int ID;
    char name[50];

    printf("Enter your ID:\t");
    scanf("%d", &ID);
    printf("Enter your Name:\t");
    scanf("\n");
    scanf("%[^\n]", name);
    printf("\nID:\t%d\t\tName:\t%s.\n", ID, name);

    return 0;
}