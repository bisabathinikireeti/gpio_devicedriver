// Online C compiler to run C program online
#include <stdio.h>

int main() {
    int arr[]={1,8,6,9,5,4};
    int n=6; int sum=0,i,j;
    int num1,num2;
    printf("largest sum pair\n");
    for( i=0;i<n;i++)
    {
        for( j=i+1;j<n;j++)
        {
            if(sum<arr[i]+arr[j]){
            sum=arr[i]+arr[j];
            num1=arr[i];
            num2=arr[j];}
        }
    }
    printf("\nthe highest sumof pair is %d and %d the sum is=%d ",num1,num2,sum);
    return 0;
}
        
