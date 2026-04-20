#include<stdio.h>
int  main()
{
    printf("enter the numbers\n");
    int a,b,sum;
    scanf("%d %d",&a,&b);
    sum=a+b;
    if(a>0 && b>0 && sum<0 || a<0 && b<0 && sum>0)
    {
        printf("%d",-1);
        return 0;
    }
    else
    printf("%d",sum);
    return 0;
    
}
