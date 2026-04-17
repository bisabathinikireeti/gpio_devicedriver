
#include <stdio.h>

int main()
{
    printf("enter the number\n");
    int n,num;
    scanf("%d",&n);
    int count=1;
    for(int i=0;i<=8;i++)
    {
        if(n&(1<<i) && count==2){
            num=n^(1<<i);
            break;
        }
        
        else if(n&(1<<i)){
           count++;
        }
        
    }
    printf("count=%d",count);
    if(count<3)
        printf("\nthe given number has less than 2 binary ones\n");
    else
    printf("%d",num);
    return 0;
}
