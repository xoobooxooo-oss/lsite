#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "arrays.h"

long long ackermann(long long m, long long n)
{
    if (m == 0) return n + 1;
    if (n == 0) return ackermann(m - 1, 1);
    return ackermann(m - 1, ackermann(m, n - 1));
}

int read_long(const char *prompt, long *result)
{
    char line[128];
    char *end;
    size_t len;
    int ch;

    printf("%s", prompt);
    if (fgets(line, sizeof(line), stdin) == NULL) return 0;

    len = strlen(line);
    if (len > 0 && line[len - 1] != '\n' && len == sizeof(line) - 1)
    {
        while ((ch = getchar()) != '\n' && ch != EOF);
        return 0;
    }

    *result = strtol(line, &end, 10);
    if (end == line) return 0;
    while (isspace((unsigned char)*end)) end++;
    if (*end != '\0') return 0;
    return 1;
}

void run_ackermann(void)
{
    long m, n;

    if (!read_long("Введите m (целое >= 0): ", &m) || m < 0)
    {
        printf("Ошибка: m должно быть неотрицательным целым числом.\n");
        return;
    }
    if (!read_long("Введите n (целое >= 0): ", &n) || n < 0)
    {
        printf("Ошибка: n должно быть неотрицательным целым числом.\n");
        return;
    }
    if (m > 3 || n > 10)
    {
        printf("Слишком большие значения (допустимо m <= 3, n <= 10).\n");
        return;
    }
    printf("A(%ld, %ld) = %lld\n", m, n, ackermann(m, n));
}

void run_sort(int which, char trace)
{
    int arr[MAX_SIZE];
    int size;

    if (!read_array(arr, &size)) return;

    if (trace == 't')
    {
        printf("Исходный массив: ");
        print_array(arr, size);
    }

    if (which == 1) bubble_sort(arr, size, trace);
    else if (which == 2) insertion_sort(arr, size, trace);
    else quick_sort(arr, size, trace);

    printf("Результат: ");
    print_array(arr, size);
}

int main(void)
{
    long choice;

    printf("Григорьев Андрей, группа ИТПМ-126\n");

    do
    {
        printf("\n=== ЛР 4 ===\n");
        printf("1 - Функция Аккермана\n");
        printf("2 - Сортировка пузырьком (без вывода шагов)\n");
        printf("3 - Сортировка пузырьком (с выводом шагов)\n");
        printf("4 - Сортировка вставками (без вывода шагов)\n");
        printf("5 - Сортировка вставками (с выводом шагов)\n");
        printf("6 - Быстрая сортировка (без вывода шагов)\n");
        printf("7 - Быстрая сортировка (с выводом шагов)\n");
        printf("0 - Выход\n");
        if (!read_long("Ваш выбор: ", &choice))
        {
            if (feof(stdin)) break;
            printf("Ошибка: введите номер пункта меню.\n");
            choice = -1;
            continue;
        }
        switch (choice)
        {
            case 1: run_ackermann(); break;
            case 2: run_sort(1, 'f'); break;
            case 3: run_sort(1, 't'); break;
            case 4: run_sort(2, 'f'); break;
            case 5: run_sort(2, 't'); break;
            case 6: run_sort(3, 'f'); break;
            case 7: run_sort(3, 't'); break;
            case 0: break;
            default: printf("Нет такого пункта меню!\n");
        }
    } while (choice != 0);

    return 0;
}