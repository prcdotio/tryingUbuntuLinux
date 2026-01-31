/*
Source: HackerRank
Playing with character to get input not only word instead we will get sentence until user hit Enter key.
*/

#include <stdio.h>
int main(void){
    int id;
    char name[50];
    printf("ID:\t");
    scanf("%d", &id);
    getchar();
    printf("Name:\t");
    scanf("%[^\n]", name);
    printf("ID:\t%d\t\tName:\t%s.\n", id, name);

    return 0;
}