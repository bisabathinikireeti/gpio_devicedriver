
#include <stdio.h>
#include<string.h>
int main()
{
char str[50];
scanf("%s",str);
int count[256]={};
for(int i=0;str[i]!='\0';i++)
{
  for(int j=i+1;str[j]!='\0';j++)
  {
      if(str[i]==str[j])
        count[str[i]]++;
  }
}
int flag=0;
for(int i=0;i<256;i++)
{
    if(count[i]>0)
    {
        printf("%c is repeated element\n",i);
        flag=1;
    }
}
if(!flag)
    printf("nothing is repeated\n");
return 0;
}
