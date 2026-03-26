#include <stdio.h>
int main(void){
    int n;
    printf("Enter a random number to get specific pattern:\t");
    scanf("%d", &n);
    int lower_limit = 0;
    int rows;
    int columns;
    rows = columns = ((2 * n) - 1);
    for (int i = 0; i < rows; ++i)
    {
        int increment = 1;
        int decrement = 0;
        for (int j = 0; j < columns; ++j){
            if(i < n){     //first half
            lower_limit = n - i;
            if (j <= (columns - (i + 1)))
            {
                int result = n - decrement;
                if(result >= lower_limit){
                    printf("%d ", result);
                    decrement += 1;
                }
                else
                {
                    printf("%d ", lower_limit);
                }
            }
            else
            {
                int result_incre;
                result_incre = lower_limit + increment;
                printf("%d ", result_incre);
                increment += 1;
            }
        }else{      //second half
            lower_limit = n - ((rows - 1) - i);
            if(j < (columns - (columns - (i + 1)))){
                int result = n - decrement;
                if(result >= lower_limit){
                    printf("%d ", result);
                    decrement += 1;
                }else{
                    printf("%d ", lower_limit);
                }
            }else{
                int result_incre;
                result_incre = lower_limit + increment;
                printf("%d ", result_incre);
                increment += 1;
            }
        }
        }
        printf("\n");
    }
    return 0;
}