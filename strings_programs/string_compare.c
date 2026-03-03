#include<stdio.h>
int main()
{
    printf("enter the two strings\n");
    char src[100],dst[100];
    scanf("%s",src);
    scanf("%s",dst);
    int i=0;
    int flag=0;
    while(src[i]!='\0' || dst[i]!='\0')
    {
        if(src[i]!=dst[i])
        {
            flag=1;
            break;
        }
        i++;
    }
    if(!flag)
        printf("the string is equal\n");
    else
        printf("the string is not equal\n");
    return 0;
}
