#include<stdio.h>
int main()
{
    printf("enter the two strings\n");
    char str[100];
    scanf("%s",str);
    int len=0;
    while(str[len]!='\0')
    len++;
    for(int i=0;i<len/2;i++)
    {
        char temp=str[i];
        str[i]=str[len-i-1];
        str[len-i-1]=temp;
    }
    printf("the reverseal string is: %s",str);
}
