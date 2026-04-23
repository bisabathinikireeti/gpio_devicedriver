#include<stdio.h>
int main()
{
    printf("enter the numbers\n");
    printf("enter the pos k\n");
    int n,k;
    scanf("%d %d",&n,&k);
    if(n&(1<<k))
    printf("in this pos bit is set\n");
    else
    printf("the bit is not set\n");
    return 0;
}
