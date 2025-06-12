#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 10

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

int is_valid(const char *str) {
    int len = strlen(str);
    if (len == 0 || len > MAX_LENGTH) {
        return 0;
    }
    
    int digits[10] = {0};
    
    for (int i = 0; i < len; i++) {
        if ((!isdigit(str[i])) || (str[i] == ' ')) {
            return 0;
        }
        int digit = str[i] - '0';
        if (digits[digit] > 0) {
            return 0;
        }
        digits[digit]++;
    }
    return 1;
}

int next_permutation(char *str) { //алгоритм нарайаны
    int len = strlen(str);
    int j = len - 2;
    
    while (j >= 0 && str[j] >= str[j + 1]) { //214
        j--;
    }
    
    if (j < 0) {
        return 0;
    }
    
    int l = len - 1;
    while (str[l] <= str[j]) {
        l--;
    }
    
    swap(&str[j], &str[l]);
    
    int left = j + 1;
    int right = len - 1;
    while (left < right) {
        swap(&str[left], &str[right]);
        left++;
        right--;
    }
    
    return 1;
}

int main() {
    char P[50];
    int N;

    if (fgets(P, sizeof(P), stdin) == NULL) {
        printf("bad input\n");
        return 0;
    }
    
    if (scanf("%d", &N) != 1) {
        printf("bad input\n");
        return 0;
    }

    int len = strlen(P);
    if (len > 0 && P[len-1] == '\n') {
        P[len-1] = '\0';
        len--;
    }

    if (!is_valid(P)) {
        printf("bad input\n");
        return 0;
    }
    
    for (int i = 0; i < N; i++) {
        if (!next_permutation(P)) {
            break;
        }
        printf("%s\n", P);
    }
    
    return 0;
}
