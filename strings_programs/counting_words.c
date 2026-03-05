
#include <stdio.h>
#include<string.h>
int main()
{
char str[50];
int count=1;
fgets(str,sizeof(str),stdin);
puts(str);
for(int i=0;str[i]!='\0';i++)
{
    if(str[i]==' ')
        count++;
}
printf("the string has %d words\n",count);
return 0;
}
