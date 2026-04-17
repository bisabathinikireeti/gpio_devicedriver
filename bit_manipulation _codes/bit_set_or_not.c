
#include <stdio.h>

int main()
{
    printf("enter the number\n");
    int n,num;
    scanf("%d",&n);
    printf("enter the kth position\n");
    int k;
    scanf("%d",&k);
    if(n&(1<<k))
    printf("the bit is set\n");
    else
        printf("the bit is not set\n");
    return 0;
}
