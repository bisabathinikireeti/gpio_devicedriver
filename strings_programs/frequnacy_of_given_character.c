
#include <stdio.h>
#include<string.h>
int main()
{
char str[50];
scanf("%s",str);
printf("enter the character you want know frquancy\n");
char c;
getchar();
scanf(" %c",&c);
int count[256]={0};
for(int i=0;str[i]!='\0';i++)
{
  if(str[i]==c)
    count[str[i]]++;
}
for(int i=0;i<256;i++)
{
    if(count[i]!=0)
    {
        printf("%c occured %d times\n",i,count[i]);
    }
    
}
return 0;
}
