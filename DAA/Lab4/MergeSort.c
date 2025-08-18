#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long comparisonCount = 0; 

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        comparisonCount++; 
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}


void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}


int readFile(const char *filename, int arr[]) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error: Cannot open file %s\n", filename);
        return -1;
    }
    int n = 0;
    while (fscanf(fp, "%d", &arr[n]) != EOF) {
        n++;
    }
    fclose(fp);
    return n;
}


void writeFile(const char *filename, int arr[], int n) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Error: Cannot write to file %s\n", filename);
        return;
    }
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d ", arr[i]);
    }
    fclose(fp);
}

int main() {
    int choice;
    int arr[1000];
    int n;
    char inFile[50], outFile[50];

    while (1) {
        printf("1. Sort Ascending Order Data (inAsc.dat)\n");
        printf("2. Sort Descending Order Data (inDesc.dat)\n");
        printf("3. Sort Random Data (inRand.dat)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4) break;

        switch (choice) {
            case 1:
                snprintf(inFile, sizeof(inFile), "inAsc.dat");
                snprintf(outFile, sizeof(outFile), "outAsc.dat");
                break;
            case 2:
                snprintf(inFile, sizeof(inFile), "inDesc.dat");
                snprintf(outFile, sizeof(outFile), "outDesc.dat");
                break;
            case 3:
                snprintf(inFile, sizeof(inFile), "inRand.dat");
                snprintf(outFile, sizeof(outFile), "outRand.dat");
                break;
            default:
                printf("Invalid choice!\n");
                continue;
        }

        n = readFile(inFile, arr);
        if (n <= 0) continue;

        comparisonCount = 0;

        clock_t start = clock();
        mergeSort(arr, 0, n - 1);
        clock_t end = clock();

        double executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;

        writeFile(outFile, arr, n);

        printf("Sorted %d elements.\n", n);
        printf("Number of comparisons: %ld\n", comparisonCount);
        printf("Execution time: %.6f seconds\n", executionTime);
        printf("Output saved to %s\n", outFile);
    }

    return 0;
}
