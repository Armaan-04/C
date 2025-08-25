#include <stdio.h>

struct ITEM {
    int item_id;
    float profit;
    float weight;
    float ratio;
};

void insertionSort(struct ITEM arr[], int n) {
    for (int i = 1; i < n; i++) {
        struct ITEM key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j].ratio < key.ratio) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int n;
    float capacity;
    printf("Enter the number of items: ");
    scanf("%d", &n);

    struct ITEM items[n];
    for (int i = 0; i < n; i++) {
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%f %f", &items[i].profit, &items[i].weight);
        items[i].item_id = i + 1;
        items[i].ratio = items[i].profit / items[i].weight;
    }

    printf("Enter the capacity of knapsack: ");
    scanf("%f", &capacity);

    insertionSort(items, n);

    float total_profit = 0.0;
    float amount_taken[n];

    for (int i = 0; i < n; i++) {
        if (capacity >= items[i].weight) {
            amount_taken[i] = 1.0;  
            total_profit += items[i].profit;
            capacity -= items[i].weight;
        } else {
            amount_taken[i] = capacity / items[i].weight; 
            total_profit += items[i].profit * amount_taken[i];
            capacity = 0;
        }
    }

    printf("\nItem No\tProfit\t\tWeight\t\tAmount to be taken\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%.6f\t%.6f\t%.6f\n", items[i].item_id, items[i].profit, items[i].weight, amount_taken[i]);
    }

    printf("Maximum profit: %.6f\n", total_profit);

    return 0;
}

