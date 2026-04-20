
#include<stdio.h>
int main()
{
    printf("enter the n and d\n");
    int n,d,res;
    scanf("%d %d",&n,&d);
    res=n&(d-1);
    printf("%d",res);

    return 0;
}
