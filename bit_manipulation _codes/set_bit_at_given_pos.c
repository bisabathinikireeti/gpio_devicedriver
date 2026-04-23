#include<stdio.h>
int main()
{
    printf("enter the numbers\n");
    printf("enter the pos k\n");
    int n,k;
    scanf("%d %d",&n,&k);
    printf("%d",n|(1<<k));
    return 0;
}
