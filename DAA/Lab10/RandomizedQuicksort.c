#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    // Lomuto's Partition: uses arr[high] as pivot
    int pivot = arr[high]; 
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++; 
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

int randomized_partition(int arr[], int low, int high) {
    // Select random index in [low, high]
    int random_pivot_index = low + rand() % (high - low + 1);

    // Swap random pivot with the last element for partition
    swap(&arr[random_pivot_index], &arr[high]);

    return partition(arr, low, high);
}

void randomized_quicksort(int arr[], int low, int high) {
    if (low < high) {
        // Get partition index
        int p = randomized_partition(arr, low, high);

        // Recurse on the two sub-arrays
        randomized_quicksort(arr, low, p - 1);
        randomized_quicksort(arr, p + 1, high);
    }
}

int main() {
    // Initialize random seed once
    srand(time(NULL));

    int n;
    printf("Enter the number of elements in the array: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid array size.\n");
        return 1;
    }

    // Dynamically allocate memory for the array
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input. Exiting.\n");
            free(arr);
            return 1;
        }
    }
    
    printf("\nOriginal array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    randomized_quicksort(arr, 0, n - 1);
    
    printf("Sorted array:   ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    // Free the dynamically allocated memory
    free(arr);

    return 0;
}