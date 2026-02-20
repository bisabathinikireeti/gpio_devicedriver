// Online C compiler to run C program online
#include <stdio.h>

int main() {
    int arr[]={1,8,6,9,5,4};
    int n=6; int min_sum=arr[0]+arr[1],i,j;
    int num1,num2;
    printf("minimum sum pair\n");
    for( i=0;i<n;i++)
    {
        for( j=i+1;j<n;j++)
        {
            if(min_sum>arr[i]+arr[j]){
            min_sum=arr[i]+arr[j];
            num1=arr[i];
            num2=arr[j];}
        }
    }
    printf("\nthe highest sumof pair is %d and %d the sum is=%d ",num1,num2,min_sum);
    return 0;
}
        
