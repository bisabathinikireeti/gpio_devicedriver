#include<stdio.h>
int main()
{
    printf("enter the string\n");
    char str[100];
    scanf("%s",str);
    int len=0;
    while(str[len]!='\0')
    {
        len++;
    }
    printf("%d is len of string\n",len);
    return 0;
}
