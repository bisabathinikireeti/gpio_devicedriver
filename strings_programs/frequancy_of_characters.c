
#include <stdio.h>
#include<string.h>
int main()
{
char str[50];
scanf("%s",str);
int count[256]={0};
for(int i=0;str[i]!='\0';i++)
{
    count[str[i]]++;
}
 for(int i=0;i<256;i++)
 {
     if(count[i]!=0 && i!='\n')
        printf("%d is frequancy of %c\n",count[i],i);
 }
 return 0;
}
