#include <stdio.h>
int main(void){
    int id;
    char name[50];
    printf("Enter you id:\t");
    scanf("%d", &id);
    printf("Enter your name:\t");
    scanf("\n");
    scanf("%[^\n]", name);
    printf("ID:\t%d\t\tName:\t%s.\n", id, name);

    return 0;
}