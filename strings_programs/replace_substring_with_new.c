#include<stdio.h>
#include<string.h>
int main()
{
    char str[100],sub[50],rep[50],res[50];
    puts("enter the string\n");
    fgets(str,sizeof(str),stdin);
    int len=strlen(str);
    str[len-1]=str[len];
    puts("enter the sub string\n");
    fgets(sub,sizeof(sub),stdin);
    len=strlen(sub);
    sub[len-1]=sub[len];
    puts("enter the new string\n");
    fgets(rep,sizeof(rep),stdin);
    len=strlen(rep);
    rep[len-1]=rep[len];
    char *pos=strstr(str,sub);
    if(pos!=NULL)
    {
        int index=pos-str;
        strncpy(res,str,index);
        res[index]='\0';
        strcat(res,rep);
        strcat(res,pos+strlen(sub));
        puts(res);
    }
    else{
        printf("substring not found\n");
    }
    return 0;
}
