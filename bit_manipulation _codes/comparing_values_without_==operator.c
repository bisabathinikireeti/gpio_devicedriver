#include<stdio.h>
int  main()
{
    printf("enter the numbers\n");
    int a,b;
    scanf("%d %d",&a,&b);
    if((a&(~b))==0)
    printf("same\n");
    else
    printf("not same\n");
    return 0;
    
}


//another method using ^
#include<stdio.h>
int  main()
{
    printf("enter the numbers\n");
    int a,b;
    scanf("%d %d",&a,&b);
    if((a^b)== 0)
    printf("same\n");
    else
    printf("not same\n");
    return 0;
    
}

