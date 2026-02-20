// Online C compiler to run C program online
#include <stdio.h>

int main() {
    int arr[]={1,8,6,9,5,4};
    int n=6;
    printf("ascending order\n");
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(arr[i]>arr[j]){
                int temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
    printf(" \nthis is reversing array and descesnding array\n");
    for(int i=0;i<n/2;i++)
    {
        int temp=arr[i];
        arr[i]=arr[n-i-1];
        arr[n-i-1]=temp;
    }
     for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
    return 0;
}
