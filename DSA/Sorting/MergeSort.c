#include <stdio.h>

void Merge(int A[], int low, int high, int mid) {
    int i = low;
    int j = mid + 1;
    int k = low;
    int B[100];

    while (i <= mid && j <= high) {
        if (A[i] < A[j]) {
            B[k] = A[i];
            i++;
            k++;
        } else {
            B[k] = A[j];
            i++;
            j++;
        }
        k++;
    }

    while (i <= mid) {
        B[k] = A[i];
        k++;
        i++;
    }
    while (j <= high) {
        B[k] = A[j];
        k++;
        j++;
    }
    for (int p = low; p <= high; p++) {
        A[p] = B[p];
    }
}

void MergeSort(int A[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        MergeSort(A, low, mid);
        MergeSort(A, mid + 1, high);
        Merge(A, low, high, mid); 
    }
}

int main() {
    int A[100];
    int n;

    printf("Enter size of the array: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &A[i]);
    }

    printf("Unsorted array is: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }

    MergeSort(A, 0, n - 1);

    printf("\nSorted array using Merge sort is: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
}
