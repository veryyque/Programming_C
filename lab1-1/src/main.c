#define _CRT_SECURE_NO_WARNINGS
#define BUFFER_SIZE 8192
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Функция для вычисления хэша
unsigned int hash(const char * text, unsigned long long int text_len, unsigned int added_num) {
    unsigned long long int hash = 0, power = 1;
    for (unsigned long long int j = added_num; j < text_len+added_num; j++) {
        hash += ((unsigned int)text[j] % 3) * power;
        power *= 3;
    }
    return hash;
}

// Функция Рабина-Карпа для режима работы с файлом
unsigned int rabin_karp_count(const char *pattern, unsigned int pattern_hash, const char *text, unsigned int pattern_len, unsigned int text_len) {
    if (text_len < pattern_len) {
        return 0;
    }

    unsigned int match_count = 0;
    unsigned long long int current_hash = hash(text, pattern_len, 0);
    unsigned long long int power = 1;
    for (unsigned int j = 1; j < pattern_len; j++) { //перевычисление для скользящего хэша
        power *= 3;
    }

    for (unsigned int i = 0; i <= text_len - pattern_len; i++) {
        if (current_hash == pattern_hash) {
            int match = 1;
            for (unsigned int j = 0; j < pattern_len; j++) {
                if (text[i + j] != pattern[j]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                match_count++;
            }
        }
        if (i < text_len - pattern_len) {
            //убираю первый символ и добавляю следующий - реализация скользящего хэша
            current_hash = (current_hash - ((unsigned int)text[i] % 3)) / 3 + ((unsigned int)text[i + pattern_len] % 3) * power;
        }
    }
    return match_count;
}

// Функция Рабина-Карпа для терминала
unsigned int global_text_index = 0;

void rabin_karp(const char* pattern, unsigned int pattern_hash, const char * text, unsigned int pattern_len, unsigned int text_len) {
    for (unsigned int i = 0; i <= (text_len - pattern_len); i++) {
        unsigned long long int current_hash = hash(text, pattern_len, i);
        if (current_hash == pattern_hash) {
            for (unsigned int j = 0; j < pattern_len; j++) {
                printf("%u ", i + j + 1 + global_text_index);
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }
        }
    }
    global_text_index+=pattern_len;
}

int main(int argc, char *argv[]) {
    char pattern[BUFFER_SIZE] = {0};
    
    if (argc == 2 && strcmp(argv[1], "-i") == 0) { // режим работы с файлом
        unsigned long long int start_time, end_time;
        double final_time;
        FILE *file = fopen("war_and_peace.txt", "rb");
        if (file == NULL) {
            return 0;
        }

        if (fgets(pattern, sizeof(pattern), file) == NULL) {
            fclose(file);
            return 0;
        }

        unsigned int pattern_len = strlen(pattern);
        if (pattern_len > 0 && pattern[pattern_len - 1] == '\n') {
            pattern[pattern_len - 1] = '\0';
        }
        pattern_len = strlen(pattern);
        if (pattern_len == 0) {
            fclose(file);
            return 1;
        }

        unsigned int pattern_hash = hash(pattern, pattern_len, 0);
        char *text_buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
        if (text_buffer == NULL) {
            fclose(file);
            return 1;
        }

        unsigned int total_read = 0;
        unsigned int bytes_read = 0;
        unsigned int total_matches = 0; 

        start_time = clock();

        bytes_read = fread(text_buffer, 1, BUFFER_SIZE, file);
        total_read = bytes_read;

        while (bytes_read > 0) {
            if (total_read >= pattern_len) {
                total_matches += rabin_karp_count(pattern, pattern_hash, text_buffer, pattern_len, total_read);
            }
            if (total_read >= pattern_len - 1) {
                memmove(text_buffer, text_buffer + total_read - (pattern_len - 1), pattern_len - 1);
                total_read = pattern_len - 1;
            }

            bytes_read = fread(text_buffer + total_read, 1, BUFFER_SIZE - total_read, file);
            total_read += bytes_read;

            if (total_read >= BUFFER_SIZE) {
                char *temp = (char *)realloc(text_buffer, total_read + BUFFER_SIZE);
                if (temp == NULL) {
                    free(text_buffer);
                    fclose(file);
                    return 0;
                }
                text_buffer = temp;
            }
        }

        end_time = clock();
        final_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

        printf("MATCHES: %u\n", total_matches); 
        printf("TIME:%.6f seconds\n", final_time);
        free(text_buffer);
        fclose(file);
        return 0;
    } 
    else { // режим работы с терминалом
        //char pattern[BUFFER_SIZE] = {0};
        if (fgets(pattern, sizeof(pattern), stdin) == NULL) {
            return 1;
        }
        
        unsigned int pattern_len = strlen(pattern);
        if (pattern_len > 0 && pattern[pattern_len - 1] == '\n') {
            pattern[pattern_len - 1] = '\0';
            pattern_len--;
        }
        pattern_len = strlen(pattern);
        unsigned int pattern_hash = hash(pattern, pattern_len, 0);

        printf("%u ", pattern_hash);

        char text[BUFFER_SIZE] = {0};

        while (fgets(text, BUFFER_SIZE, stdin) != NULL) {
            unsigned int text_len = strlen(text);
            rabin_karp(pattern, pattern_hash, text, pattern_len, text_len);
        }
        printf("\n");
        return 0;
    }
}
