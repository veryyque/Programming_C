#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h> 

#define MAX_STACK_SIZE 10000

// завожу токены для операторов, операндов и ошибок для завершения программы
typedef enum {
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_END,
    TOKEN_ERROR_SYNTAX,
    TOKEN_LAST_RESULT,
} TokenType;

typedef struct {
    TokenType type;
    double value; 
} Token;

Token make_error() {
    Token e = { .type = TOKEN_ERROR_SYNTAX, .value = 0 };
    return e;
}

Token get_token(const char **s, double last_result) {
    while (isspace(**s)) { // не учитываю пробелы
        (*s)++;
    }
    if (**s == '\0') {
        return (Token){TOKEN_END, 0};
    }
    if (isdigit(**s) || **s == '.') { 
        double value = 0.0;
        int decimal_point_found = 0;
        double decimal_multiplier = 0.1;
        
        while (isdigit(**s) || **s == '.') {
            if (**s == '.') {
                if (decimal_point_found) {
                    //printf("syntax error\n");
                    return make_error();
                }
                decimal_point_found = 1;
            } else {
                if (!decimal_point_found) {
                    value = value * 10 + (**s - '0');
                } else {
                    value += (**s - '0') * decimal_multiplier;
                    decimal_multiplier /= 10;
                }
            }
            (*s)++;
        }
        return (Token){TOKEN_NUMBER, value}; // если цифра, то считывается число полностью до знака оператора
    }
    if (**s == '$') {
        (*s)++;
        return (Token){TOKEN_LAST_RESULT, last_result}; // Возвращаем предыущий результат
    }
    Token token;
    switch (**s) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
        case '^':
            token.type = TOKEN_OPERATOR;
            token.value = **s;
            break;
        default:
            //printf("syntax error\n");
            return make_error();
    }
    (*s)++;
    return token;
}

// Структура стека остается без изменений
typedef Token StackElement;
struct Stack {
    StackElement data[MAX_STACK_SIZE];
    int top;
};

// инициализация стэка
void stack_init(struct Stack* s) {
    if (s != NULL) {
        s->top = -1;
    }
}

// кол-во элементов на стэке
size_t stack_size(struct Stack* s) {
    return s->top + 1;
}

// вернуть значение на верхушке стэка без ее изменения
StackElement stack_peek(struct Stack* s) {
    if (s->top == -1) {
        return make_error();
    }
    return s->data[s->top];
}

// поместить значение на верхушку стэка
void stack_push(struct Stack* s, StackElement x) {
    if (s->top >= MAX_STACK_SIZE - 1) {
        return;
    }
    s->data[++s->top] = x;
}

// достать значение с верхушки стэка
StackElement stack_pop(struct Stack* s) {
    if (s->top == -1) {
        return make_error(); 
    }
    return s->data[s->top--];
}

// очистить стэк
int stack_empty(struct Stack* s) {
    return s->top == -1;
}

// расставление приоритета операторов
int operator_priority(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

// Алгоритм сортировочной станции
int sorting_station(const char *s, struct Stack *output, struct Stack *operators, double last_result) {
    Token token;
    int paren_count = 0;
    Token last_token = {TOKEN_END, 0}; //сохр последний токен
    while ((token = get_token(&s, last_result)).type != TOKEN_END) {
        if (token.type == TOKEN_NUMBER) {
            if (last_token.type == TOKEN_NUMBER || (last_token.type == TOKEN_OPERATOR && last_token.value == ')')) {
                printf("syntax error\n"); // число после числа или закр скобки
                return TOKEN_ERROR_SYNTAX;
            }
            stack_push(output, token);
        } else if (token.type == TOKEN_LAST_RESULT) {
            stack_push(output, token); // добавляю пред результат в текущий стэк
        } else if (token.type == TOKEN_OPERATOR) {
            char operator = token.value;
            if (operator == '(' && last_token.type == TOKEN_NUMBER) {
                printf("syntax error\n");// ( скобка после числа
                return TOKEN_ERROR_SYNTAX;
            }
            if (operator == ')' && last_token.type == TOKEN_OPERATOR && last_token.value == '(') {
            printf("syntax error\n"); // пустые скобки
            return TOKEN_ERROR_SYNTAX;
            }
            switch (operator) {
                case '+':
                case '-':
                case '*':
                case '/':
                    while (!stack_empty(operators) &&
                           operator_priority(stack_peek(operators).value) >= operator_priority(operator)) {
                        stack_push(output, stack_pop(operators));
                    }
                    stack_push(operators, token);
                    break;
                case '^': //для правоассоциативных операторов отдельно
                    while (!stack_empty(operators) &&
                           operator_priority(stack_peek(operators).value) > operator_priority(operator)) {
                        stack_push(output, stack_pop(operators));
                    }
                    stack_push(operators, token);
                    break;
                case '(':
                    stack_push(operators, token);
                    paren_count++;
                    break;
                case ')':
                    while (!stack_empty(operators) && stack_peek(operators).value != '(') {
                        stack_push(output, stack_pop(operators));
                    }
                    paren_count--;
                    if (stack_empty(operators) || stack_pop(operators).value != '(') {
                        printf("syntax error\n"); // непарные скобки
                        return TOKEN_ERROR_SYNTAX;
                    }
                    break;
                default:
                    printf("syntax error\n");
                    return TOKEN_ERROR_SYNTAX;
            }
        } else {
            printf("syntax error\n"); //неизвестный токен
            return TOKEN_ERROR_SYNTAX;
        }
        last_token = token;
    }
    if (paren_count != 0) {
        printf("syntax error\n");
        return TOKEN_ERROR_SYNTAX;
    }
    while (!stack_empty(operators)) {
        stack_push(output, stack_pop(operators));
    }
    return 0;
}

// Вычисление RPN
double evaluate_rpn(struct Stack *output) {
    struct Stack eval_stack;
    stack_init(&eval_stack);
    struct Stack reverse_output;
    stack_init(&reverse_output);
    while (!stack_empty(output)) {
        stack_push(&reverse_output, stack_pop(output)); // перевод стэка в обратном порядке
    }
    while (!stack_empty(&reverse_output)) {
        Token token = stack_pop(&reverse_output);
        if (token.type == TOKEN_NUMBER || token.type == TOKEN_LAST_RESULT) {
            stack_push(&eval_stack, token);
        } else if (token.type == TOKEN_OPERATOR) {
            if (stack_size(&eval_stack) < 2) {
                printf("syntax error\n"); //если введено меньше 2 чисел || скобок, нет смысла вычислять
                return NAN;
            }
            double b = stack_pop(&eval_stack).value;
            double a = stack_pop(&eval_stack).value;
            double result = 0.0;
            switch ((int)token.value) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/':
                    if (b == 0) {
                        printf("division by zero\n");
                        return NAN;
                    }
                    result = a / b;
                    break;
                case '^':
                    result = pow(a, b);
                    break;
                default:
                    printf("syntax error\n");
                    return NAN;
            }
            stack_push(&eval_stack, (Token){TOKEN_NUMBER, result}); // дабвляю на стэк результат вычисления
        }
    }
    if (stack_size(&eval_stack) != 1) {
        printf("syntax error\n");
        return NAN;
    }
    return stack_pop(&eval_stack).value;
}

double last_result = 0.0; // Изменено: double вместо int
int main(int argc, char *argv[]) {
    char s[10000] = {0};
    if (argc == 2){
        if (strcmp(argv[1], "-i") == 0){
            while (fgets(s, 10000, stdin) != NULL && strncmp(s, "exit", 4) != 0) {
                s[strcspn(s, "\n")] = '\0';
                struct Stack numbers, operators;
                stack_init(&numbers);
                stack_init(&operators);
                int srt = sorting_station(s, &numbers, &operators, last_result);
                if (srt == 0) {
                    double result = evaluate_rpn(&numbers); // Результат в double
                    if (!isnan(result)) {  
                        // Проверяем, является ли результат целым числом
                        if (floor(result) == result) {
                            printf(" < %d >\n", (int)result); // Выводим как int
                        } else {
                            printf(" < %.15g >\n", result); // Выводим как double
                        }
                        last_result = result; //сохранение последнего результата
                    }
                }
                fputs(" > ", stdout);
            }
        }
    }
    else {
        if (fgets(s, 10000, stdin) == NULL) {
            return 0;
        } 
        s[strcspn(s, "\n")] = '\0';
        int len_str = strlen(s);
        if (len_str == 0) {
            printf("syntax error");
            return 0;
        }
        for (unsigned int i = 0; i < strlen(s) - 1;i++){
            if (s[i] == '.' && s[i + 1] == '0'){
                printf("syntax error\n");
                return 0;
            }
        }
        struct Stack numbers, operators;
        stack_init(&numbers);
        stack_init(&operators);
        int srt = sorting_station(s, &numbers, &operators, last_result);
        if (srt == 0){
            double result = evaluate_rpn(&numbers); // Результат в double
            if (!isnan(result)) {
                if (floor(result) == result) {
                    printf("%d\n", (int)result); // Выводим как int
                } else {
                    printf("%.15g\n", result); // Выводим как double
                }
            }
        }
        return 0;
    }
}
