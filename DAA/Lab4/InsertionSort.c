#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 500

int comparisons = 0;

int partition(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low + 1;
    int j = high;
    
    while (1) {
        while (i <= high && arr[i] <= pivot) {
            comparisons++;
            i++;
        }
        while (arr[j] > pivot) {
            comparisons++;
            j--;
        }
        if (i < j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        } else {
            break;
        }
    }
    
    int temp = arr[low];
    arr[low] = arr[j];
    arr[j] = temp;
    
    return j;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pos = partition(arr, low, high);
        
        int leftSize = pos - low;
        int rightSize = high - pos;
        
        if (leftSize == 0 || rightSize == 0) {
            printf("Partitioning: Worst-case (One side empty)\n");
        } 
        else if (abs(leftSize - rightSize) <= 1) {
            printf("Partitioning: Best-case (Even split)\n");
        }
        
        quickSort(arr, low, pos - 1);
        quickSort(arr, pos + 1, high);
    }
}

int readFile(const char *filename, int arr[]) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error: Cannot open file %s\n", filename);
        return 0;
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
        printf("Error: Cannot open file %s\n", filename);
        return;
    }
    
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d ", arr[i]);
    }
    
    fclose(fp);
}

void displayFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error: Cannot open file %s\n", filename);
        return;
    }
    
    int x;
    while (fscanf(fp, "%d", &x) != EOF) {
        printf("%d ", x);
    }
    printf("\n");
    
    fclose(fp);
}

int main() {
    int choice;
    int arr[MAX], n;
    char inputFile[30], outputFile[30];
    
    do {
        
        printf("1. Sort Ascending Order File\n");
        printf("2. Sort Descending Order File\n");
        printf("3. Sort Random Order File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        comparisons = 0;
        
        switch (choice) {
            case 1:
                sprintf(inputFile, "inAsc.dat");
                sprintf(outputFile, "outQuickAsce.dat");
                break;
            case 2:
                sprintf(inputFile, "inDesc.dat");
                sprintf(outputFile, "outQuickDesc.dat");
                break;
            case 3:
                sprintf(inputFile, "inRand.dat");
                sprintf(outputFile, "outQuickRand.dat");
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
                continue;
        }
        
        n = readFile(inputFile, arr);
        if (n == 0) continue;
        
        clock_t start = clock();
        quickSort(arr, 0, n - 1);
        clock_t end = clock();
        
        writeFile(outputFile, arr, n);
        
        printf("\nSorted Data in %s:\n", outputFile);
        displayFile(outputFile);
        
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Number of Comparisons: %d\n", comparisons);
        printf("Execution Time: %.6f seconds\n", time_taken);
        
    } while (choice != 4);
    
    return 0;
}

