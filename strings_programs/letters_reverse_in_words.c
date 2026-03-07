#include<stdio.h>
int main()
{
    char str[50];
    fgets(str,sizeof(str),stdin);
    int start=0,end;
    for(int i=0;str[i]!='\0';i++)
    {
        if(str[i]==' ' || str[i]== '\n')
        {
            end=i-1;
            while(start<end)
            {
                char temp;
                temp=str[start];
                str[start]=str[end];
                str[end]=temp;
                start++;
                end--;
            }

            start=i+1;
        }
    }
    printf("%s is reversed words\n",str);
    return 0;

}
