#include<stdio.h>

int main(){
int a[5];
int i;
int *q = a;   //q is a pointer that stores the base address of array a

for (i = 0 ; i<5 ; i++)
{
    printf("Enter array elements: ");
    scanf("%d" , &a[i]);
}
for(i=0 ; i<5 ; i++){        //&q+i for printing address
    printf("%d " , *(q+i));  //address traversing 
}
return 0;
}