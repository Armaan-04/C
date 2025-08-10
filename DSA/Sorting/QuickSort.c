#include <stdio.h>

void swap (int *a , int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Partition(int arr[] , int low , int high){
   int pivot = arr[low];
   int start = low;
   int end = high;

   while(start<end){
        while(arr[start] <= pivot){
            start++;
        }
        while(arr[end]>pivot){
            end--;
        }
        if(start<end){
            swap(&arr[start] , &arr[end]);
        }
   }
   swap(&arr[low] , &arr[end]);
   return end;
}

void QuickSort(int arr[] , int low , int high ){
    if(low < high){
        int loc = Partition( arr , low , high );
        QuickSort(arr , low , loc );
        QuickSort(arr , loc + 1 , high);
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

    QuickSort( arr , 0 , n-1);

    printf("\nSorted array using quick sort is: ");
    for(int i = 0 ; i<n ; i++){
        printf("%d " , arr[i]);
    }
}