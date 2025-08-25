#include <stdio.h>

void SelectionSort(int arr[], int n) {
    int i, j, minIndex, temp;

    for(i = 0; i < n-1; i++) {
        minIndex = i;

        for(j = i+1; j < n; j++) {
            if(arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

int main() {
    int arr[100], n, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements: \n", n);
    for(i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    SelectionSort(arr, n);

    printf("Sorted array: ");
    for(i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
