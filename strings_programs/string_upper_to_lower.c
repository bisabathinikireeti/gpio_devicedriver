
#include <stdio.h>
#include<string.h>
int main()
{
    char str[50];
    fgets(str,sizeof(str),stdin);
    printf("%s\n",str);
    int len=0;
    while(str[len] != '\0')
    len++;
    
    for(int i=0;i<len;i++)
    {
        if(str[i]>=65 && str[i]<97)
            str[i]=str[i]+32;
    }
    
    printf("%s is lower alphabets\n",str);
    return 0;
}
