#include<stdio.h>
int main()
{
    printf("enter the numbers\n");
    int n,count=0;
    scanf("%d",&n);
    while(n)
    {
        if(n&1)
        {
            count++;
        }
        n=n>>1;
    }
    printf("%d",count);
    return 0;
}
