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

int BinarySearch(int arr[] , int n , int data)
{
    int l = 0;
    int r = n-1;
    while(l<r)
    {
       int mid=(l+r)/2;
       if(data==arr[mid])
       {
        return mid;
       }
       else if(data<arr[mid])
       {
           r = mid-1;
       }
       else
       {
        l = mid + 1;
       }
       
    }
    return -1;

}

int main(){
    int arr[100];
    int n;
    int data;
    
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

    printf("\nEnter the element to search: ");
    scanf("%d", &data);

    int result = BinarySearch(arr, n, data);

    if (result != -1) {
        printf("Element found at index %d\n", result);
    } else {
        printf("Element not found\n");
    }
}