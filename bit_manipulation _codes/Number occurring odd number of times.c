
//time taking code but it works for singile and multiple odd numbers
#include<stdio.h>
void main()
{
    int arr[]= {1, 2, 3, 2, 3, 1, 3};
    int n=sizeof(arr)/sizeof(arr[0]);
    for(int i=0;i<n;i++)
    {
        int flag=0,count=0;
        for(int k=0;k<i;k++)
        {
            if(arr[i]==arr[k])
            {
                flag=1;
                break;
            }
        }
    if(flag)
    continue;
        for(int j=0;j<n;j++)
        {
            if(arr[j]==arr[i])
            count++;
        }
        if(count%2!=0)
        {
            printf("%d\n",arr[i]);
        }
    }
}



//less time o(1) and it works for only one odd times
#include<stdio.h>
void main()
{
    int arr[]= {1, 2, 3, 2, 3, 1, 3};
    int n=sizeof(arr)/sizeof(arr[0]);
    int res=0;
    for(int i=0;i<n;i++)
    {
        res^=arr[i];
    }
    printf("%d",res);
}


