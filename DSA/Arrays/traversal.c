#include <stdio.h>

int main(){
int arr[50]; 
int n = 0;
printf("Enter size of array: ");
scanf("%d" , &n);

for (int i = 0 ; i<n ; i++){
    printf( "Enter element %d : " , i+1);
    scanf("%d" , &arr[i]);
}

printf("The elements of the array are: ");
for (int i = 0 ; i<n ; i++){
    printf(" %d " , arr[i]);
}
}
