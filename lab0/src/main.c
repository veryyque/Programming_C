#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

void SplitByPoint(const char* numB1, unsigned int size,
    char* beforePointB1,
    char* afterPointB1, unsigned int sizeAfter) {
    size_t i = 0;
    while (i < size && numB1[i] != '\0' && numB1[i] != '.') {
        beforePointB1[i] = numB1[i];
        i++;
    }
    beforePointB1[i] = '\0';
    if (numB1[i] == '.') {
        i++;
        size_t j = 0;
        while (i < size && numB1[i] != '\0' && j < sizeAfter) {
            afterPointB1[j] = numB1[i];
            i++;
            j++;
        }
        afterPointB1[j] = '\0';
    }
    else {
        afterPointB1[0] = '\0';
    }
}

long long int ConvertToInt(const char* beforePointB1, unsigned int size, int b1) {
    long long int intValue = 0;
    for (size_t i = 0; i < size && beforePointB1[i] != '\0'; i++) {
        long long int digit;
        if (isdigit(beforePointB1[i])) {
            digit = beforePointB1[i] - '0';
        }
        else if (islower(beforePointB1[i])) {
            digit = beforePointB1[i] - 'a' + 10;
        }
        else if (isupper(beforePointB1[i])) {
            digit = beforePointB1[i] - 'A' + 10;
        }
        else {
            return -1;
        }
        if (digit >= b1) {
            return -1;
        }
        intValue = intValue * b1 + digit;
    }
    return intValue;
}

long double ConvertToDouble(const char* afterPointB1, unsigned int size, int b1) {
    double doubleValue = 0.0;
    double base = b1;
    for (size_t i = 0; i < size && afterPointB1[i] != '\0'; i++) {
        long int digit;
        if (isdigit(afterPointB1[i])) {
            digit = afterPointB1[i] - '0';
        }
        else if (islower(afterPointB1[i])) {
            digit = afterPointB1[i] - 'a' + 10;
        }
        else if (isupper(afterPointB1[i])) {
            digit = afterPointB1[i] - 'A' + 10;
        }
        else {
            return -1;
        }
        if (digit >= b1) {
            return -1;
        }
        doubleValue += digit / base;
        base *= b1;
    }
    return doubleValue;
}

void ConvertIntToString(size_t intValue, size_t b2, char* beforePointB2, size_t size) {
    size_t index = 0;
    if (intValue == 0) {
        beforePointB2[index++] = '0';
    }
    else {
        while (intValue > 0 && index < size - 1) {
            long long int remainder = intValue % b2;
            beforePointB2[index++] = (remainder < 10) ? (remainder + '0') : (remainder - 10 + 'a');
            intValue /= b2;
        }
    }

    for (size_t i = 0; i < index / 2; i++) {
        char tmp = beforePointB2[i];
        beforePointB2[i] = beforePointB2[index - i - 1];
        beforePointB2[index - i - 1] = tmp;
    }
    beforePointB2[index] = '\0';
}

void ConvertDoubleToString(double doubleValue, size_t b2, char* afterPointB2, size_t size) {
    size_t index = 0;
    afterPointB2[0] = '\0';
    if (doubleValue <= 0) return;

    afterPointB2[index++] = '.';
    for (size_t i = 0; i < 12 && index < size - 1; i++) {
        doubleValue *= b2;
        size_t digit = floor(doubleValue);
        afterPointB2[index++] = (digit < 10) ? (digit + '0') : (digit - 10 + 'a');
        doubleValue -= digit;
    }
    afterPointB2[index] = '\0';
}

int main() {
    int b1, b2;
    if (scanf("%d%d", &b1, &b2) != 2 || b1 < 2 || b1 > 16 || b2 < 2 || b2 > 16) {
        printf("bad input\n");
        return 0;
    }

    char numB1[1000];
    if (scanf("%999s", numB1) != 1) {
        printf("bad input\n");
        return 0;
    }

    size_t DotLocation = 0, DotCount = 0;
    for (size_t i = 0; i < strlen(numB1); i++) {
        if (numB1[i] == '.'){
            if (DotCount != 0) {
                printf("bad input\n");
                return 0;
            }
            DotLocation = i;
            DotCount++;
            if (DotLocation == 0 || (strlen(numB1) - i - 1) == 0){
                printf("bad input\n");
                return 0;
            }
        }
    }
    if (DotCount > 1) {
        printf("bad input\n");
        return 0;
    }
    char beforePointB1[1000];
    char afterPointB1[1000];
    SplitByPoint(numB1, 1000, beforePointB1, afterPointB1, 1000);

    long long int intValue = ConvertToInt(beforePointB1, 1000, b1);
    double doubleValue = ConvertToDouble(afterPointB1, 1000, b1);

    if (intValue < 0  || doubleValue < 0) {
        printf("bad input\n");
        //printf("%llu %lf", intValue, doubleValue); 
        return 0;
    }
   

    char beforePointB2[1000];
    char afterPointB2[1000];

    ConvertIntToString(intValue, b2, beforePointB2, 1000);
    ConvertDoubleToString(doubleValue, b2, afterPointB2, 1000);

    if (strlen(afterPointB1) > 0) {
        printf("%s%s\n", beforePointB2, afterPointB2);
    }
    else {
        printf("%s\n", beforePointB2);
    }

    return 0;
}
