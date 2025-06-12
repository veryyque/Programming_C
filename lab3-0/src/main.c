#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
void print_list(int *array,long long int N){
    for (unsigned int i=0;i < N; i++){
        printf("%d ",array[i]);
    }
}
void swap(int *a,int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
void heap(int *array, int N, int i){
    int biggest_el_index = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < N && array[left] > array[biggest_el_index]) {
        biggest_el_index = left;
    }
    if (right < N && array[right] > array[biggest_el_index]) {
        biggest_el_index = right;
    }
    if (biggest_el_index != i) {
        swap(&array[i],&array[biggest_el_index]);
        heap(array, N, biggest_el_index);
    }
}
void heap_sort(int *array,int N){
    for (int i = (N / 2 - 1); i >= 0; i--) {
        heap(array, N, i);
    }
    for (int i = N - 1; i > 0; i--) {
        swap(&array[0],&array[i]);
        heap(array, i, 0);
    }
}
int main(){
    long long int N;
    if (scanf("%lld",&N)!=1 || N < 0 || N > 2000000){
        printf("BAD INPUT");
        return 0;
    }
    int *array = (int *)malloc(N * sizeof(int)); 
    if (array == NULL){
        printf("BAD INPUT");
        return 0;
    }
    for (unsigned int i=0;i < N;i++){
        if (scanf("%d",&array[i])!=1){
            printf("BAD INPUT");
            free(array);
            return 0;
        }
        if (array[i] < INT_MIN || array[i] > INT_MAX){
            printf("BAD INPUT");
            free(array);
            return 0;
        }
    }
    heap_sort(array,N);
    print_list(array,N);
    free(array);
    return 0;
}
