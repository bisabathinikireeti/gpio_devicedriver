#include<stdio.h>
int  main()
{
    printf("enter the numbers\n");
    int a,b,res;
    scanf("%d %d",&a,&b);
    res=(a&(~b)|b&(~a));
    printf("%d",res);
    
    return 0;
    
}
