#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int weight;
    int value;
    int original_index;
} item_t;

int main() {
    int num_items, max_capacity;
    if (scanf("%d %d", &num_items, &max_capacity)!=2){
        return 0;
    }
    
    item_t *items = (item_t *)malloc(num_items * sizeof(item_t));
    for (int i = 0; i < num_items; i++) {
        if (scanf("%d %d", &items[i].weight, &items[i].value)!=2){
            return 0;
        }
        items[i].original_index = i;
    }

    //метод динамического программирования
    long long *max_values = (long long *)calloc(max_capacity + 1, sizeof(long long));
    int *selected_items = (int *)calloc((num_items + 1) * (max_capacity + 1), sizeof(int));
    
    for (int i = 0; i < num_items; i++) {
        for (int current_capacity = max_capacity; current_capacity >= items[i].weight; current_capacity--) {
            if (max_values[current_capacity] < max_values[current_capacity - items[i].weight] + items[i].value) {
                max_values[current_capacity] = max_values[current_capacity - items[i].weight] + items[i].value;
                selected_items[i * (max_capacity + 1) + current_capacity] = 1;
            }
        }
    }
    
    int *chosen_items = (int *)calloc(num_items, sizeof(int));
    int chosen_count = 0;
    int remaining_capacity = max_capacity;
    long long total_value = max_values[max_capacity];
    
    for (int i = num_items - 1; i >= 0; i--) {
        if (selected_items[i * (max_capacity + 1) + remaining_capacity]) {
            chosen_items[chosen_count++] = i;
            remaining_capacity -= items[i].weight;
        }
    }
    
    printf("%lld\n", total_value);
    
    for (int i = 0; i < chosen_count - 1; i++) {
        for (int j = i + 1; j < chosen_count; j++) {
            if (items[chosen_items[i]].original_index > items[chosen_items[j]].original_index) {
                int temp = chosen_items[i];
                chosen_items[i] = chosen_items[j];
                chosen_items[j] = temp;
            }
        }
    }
    
    for (int i = 0; i < chosen_count; i++) {
        int idx = chosen_items[i];
        printf("%d %d\n", items[idx].weight, items[idx].value);
    }
    
    free(items);
    free(max_values);
    free(selected_items);
    free(chosen_items);
    return 0;
}
