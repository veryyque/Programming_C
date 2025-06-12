#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int medianOfThree(int* arr, int left, int right) {
    int mid = left + (right - left) / 2;

    if (arr[left] > arr[mid])
        swap(&arr[left], &arr[mid]);
    if (arr[mid] > arr[right])
        swap(&arr[mid], &arr[right]);
    if (arr[left] > arr[mid])
        swap(&arr[left], &arr[mid]);
    
    return mid; 
}

void threeWayPartition(int* arr, int left, int right, 
                      int* first_equal, int* last_equal) {
    int pivotIndex = medianOfThree(arr, left, right);
    swap(&arr[pivotIndex], &arr[right]);
    int pivot = arr[right];
    
    int less = left;      
    int current = left;   
    int greater = right;  

    while (current <= greater) {
        if (arr[current] < pivot) {
            swap(&arr[less], &arr[current]);
            less++;
            current++;
        } 
        else if (arr[current] > pivot) {
            swap(&arr[current], &arr[greater]);
            greater--;
        } 
        else {
            current++;
        }
    }
    
    *first_equal = less;
    *last_equal = greater; 
}

void quickSort3(int* arr, int left, int right) {
    if (left >= right){
        return;
    }
    int* stack = (int*)malloc((right - left + 1) * sizeof(int));
    if (stack == NULL) return;
    
    int top = -1;
    top++;
    stack[top] = left;
    top++;
    stack[top] = right;

    while (top >= 0) {
        right = stack[top];
        top--;
        left = stack[top];
        top--;

        int first_eq, last_eq;
        threeWayPartition(arr, left, right, &first_eq, &last_eq);

        if (first_eq - 1 > left) {
            top++;
            stack[top] = left;
            top++;
            stack[top] = first_eq - 1;
        }

        if (last_eq + 1 < right) {
            top++;
            stack[top] = last_eq + 1;
            top++;
            stack[top] = right;
        }
    }
    
    free(stack);
}

int main() {
    int N;
    if (scanf("%d", &N) != 1) {
        return 0;
    }

    int* arr = (int*)malloc(N * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    for (int i = 0; i < N; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 0;
        }
    }

    quickSort3(arr, 0, N - 1);

    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}
