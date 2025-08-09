#include <stdio.h>

void InsertionSort(int arr[] , int n){
    int i , j , temp;
    for(i = 1 ; i<n ; i++){
        temp = arr[i];
        j=i-1;

        while(j >= 0 && arr[j]>temp){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1]=temp;
    }
}

int main(){
    int arr[100];
    int n;
    
    printf("Enter size of the array: ");
    scanf("%d" , &n);

    for(int i = 0 ; i<n ; i++){
        printf("Enter element %d : " , i+1);
        scanf("%d" , &arr[i]);
    }


    printf("Unsorted array is: ");
    for(int i = 0 ; i<n ; i++){
        printf("%d " , arr[i]);
    } 

    InsertionSort(arr , n );

    printf("\nSorted array is: ");
    for(int i = 0 ; i < n ; i++){
        printf("%d " , arr[i]);
    }
}


