#include<stdio.h>
int  main()
{
    printf("enter the numbers\n");
    int a,b;
    scanf("%d %d",&a,&b);
    if(a>0 && b<0 || a<0 && b>0)
    printf("true signs are different\n");
    else
    printf("false signs are not different");
    return 0;
    
}

//another method
#include<stdio.h>
int  main()
{
    printf("enter the numbers\n");
    int a,b;
    scanf("%d %d",&a,&b);
    if((a^b)>>31)
    printf("true these are the different types");
    else
    printf("false these are the not different types");
    return 0;
    
}

