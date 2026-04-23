Position of rightmost set bit
Last Updated : 5 Feb, 2026
Given an integer n, Return the position of the first set bit from right to left in the binary representation n. If no set bits present , then return 0.
Note: Position of rightmost bit is 1.

Examples:

Input: n = 18
Output: 2
Explanation: Binary representation of 18 is 10010, hence position of first set bit from right is 2.

Input:  n = 19
Output: 1
Explanation: Binary representation of 19 is 10011, hence position of first set bit from right is 1.


#include<stdio.h>
int main()
{
    printf("enter the numbers\n");
    int n,res;
    scanf("%d",&n);
    
    res=n&(-n);
    printf("res=%d",res);
    return 0;
}
