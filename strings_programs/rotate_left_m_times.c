#include<stdio.h>
#include<string.h>

int main()
{
    char str[50];
    scanf("%s",str);
    printf("enter how many timwa you want rotate:\n");
    int m;
    scanf("%d",&m);
    int temp=m;
    int start=0;
    while(start<m)
    {
        char temp=str[start];
        str[start]=str[m-1];
        str[m-1]=temp;
        start++;
        m--;
    }
    printf("%s is reverse of the string m times\n",str);
    m=temp;
    int end=strlen(str)-1;
    while(m<end)
    {
        char temp=str[m];
        str[m]=str[end];
        str[end]=temp;
        m++;
        end--;
    }
    printf("%s is full string revesal\n",str);
    start=0;
    end=strlen(str)-1;
    while(start<end)
    {
        char temp=str[start];
        str[start]=str[end];
        str[end]=temp;
        start++;
        end--;
    }
    printf("%s is left rotation of the string m times\n",str);
    return 0;

}
