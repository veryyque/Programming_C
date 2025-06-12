#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int main() {
	int N;
	long long int sum = 0;
	if (scanf("%d\n", &N) != 1 || (N < 1 || N > 10)) {
		printf("bad input");
		return EXIT_SUCCESS;
	}
	long long int arr[10];
	for (int i = 0; i < N; i++) {
		if (scanf("%lli", &arr[i]) != 1){
			printf("bad input");
			return EXIT_SUCCESS;
		}
		if (arr[i] < INT_MIN || arr[i] > INT_MAX) {
			printf("bad input");
			return EXIT_SUCCESS;
		}
	}
	for (int i = 0; i < N; i++) {
		sum += arr[i];
	}
	if (sum < INT_MIN || sum > INT_MAX) {
		printf("overflow");
			return EXIT_SUCCESS;
	}
	printf("%lli", sum);
	return 0;
}
