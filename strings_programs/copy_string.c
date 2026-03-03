#include<stdio.h>
int main()
{
    printf("enter the string\n");
    char src[100],dst[100];
    scanf("%s",src);
    int i=0;
   while(src[i]!='\0'){
       dst[i]=src[i];
       i++;
   }
   printf("%s :is the copied string",dst);
}
