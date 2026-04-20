#include<stdio.h>
void main()
{
    printf("enter the number\n");
    int n;
    scanf("%d",&n);
    if((n&(n-1))==0)
    {
        printf("the given number %d is  power of 2\n",n);
        
    }
    else
    printf("the given number %d is not power of 2\n",n);
}
