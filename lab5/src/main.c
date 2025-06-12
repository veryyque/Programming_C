#include "code.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *input_file = NULL;
    FILE *output_file = NULL;
    byte operation_mode = 0;
    long file_offset = 0;
    int skip_first_byte = 0;

    if (argc == 1)
    {
        skip_first_byte = 1;
        input_file = fopen("in.txt", "rb");
        if (!input_file)
        {
            printf("Ошибка: не удалось открыть in.txt\n");
            return 1;
        }
        if (fread(&operation_mode, 1, 1, input_file) != 1)
        {
            printf("Ошибка: некорректный ввод\n");
            fclose(input_file);
            return 1;
        }
        if (operation_mode != 'c' && operation_mode != 'd')
        {
            printf("Ошибка: неверный режим (%c)\n", operation_mode);
            fclose(input_file);
            return 1;
        }
        file_offset = ftell(input_file);
        output_file = fopen("out.txt", "wb");
        if (!output_file)
        {
            printf("Ошибка: не удалось открыть out.txt\n");
            fclose(input_file);
            return 1;
        }
    }
    else if (argc == 4)
    {
        if (strcmp(argv[1], "-c") == 0)
        {
            operation_mode = 'c';
        }
        else if (strcmp(argv[1], "-d") == 0)
        {
            operation_mode = 'd';
        }
        else
        {
            printf("Ошибка: неверный режим (%s)\n", argv[1]);
            return 1;
        }
        input_file = fopen(argv[2], "rb");
        if (!input_file)
        {
            printf("Ошибка: не удалось открыть %s\n", argv[2]);
            return 1;
        }
        output_file = fopen(argv[3], "wb");
        if (!output_file)
        {
            printf("Ошибка: не удалось открыть %s\n", argv[3]);
            fclose(input_file);
            return 1;
        }
        file_offset = 0;
    }
    else
    {
        printf("Использование: %s [-c|-d input_file output_file]\n", argv[0]);
        return 1;
    }

    if (operation_mode == 'c')
    {
        encode(input_file, output_file, skip_first_byte, file_offset);
    }
    else if (operation_mode == 'd')
    {
        decode(input_file, output_file, skip_first_byte);
    }
    else
    {
        printf("Ошибка: неверный режим (%c)\n", operation_mode);
    }
    fclose(input_file);
    fclose(output_file);
    return 0;
}
