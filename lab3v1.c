#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

void task1() {
    double eps, h, pi, sum, f0, fn, x;
    int n, i;
    printf("Введите точность: ");
    scanf("%lf", &eps);
    h = 1.0;
    pi = 0.0;
    do {
        h = h / 2.0;
        n = (int)(1.0 / h);
        sum = 0.0;
        for (i = 1; i < n; i++) {
            x = i * h;
            sum = sum + 1.0 / (1.0 + x * x);
        }
        f0 = 1.0;
        fn = 0.5;
        pi = 4.0 * (h / 2.0) * (f0 + fn + 2.0 * sum);
    } while (fabs(pi - M_PI) > eps);
    printf("Приближённое pi: %.10lf\n", pi);
    printf("M_PI: %.10lf\n", M_PI);
    printf("Шаг h: %.10lf\n", h);
}

void task2() {
    int n, i, found;
    int *a;
    printf("Введите длину массива: ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Неверная длина.\n");
        return;
    }
    a = (int*)malloc(n * sizeof(int));
    if (a == NULL) {
        printf("Ошибка памяти.\n");
        return;
    }
    printf("Введите элементы:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    found = 0;
    printf("Локальные максимумы: ");
    for (i = 1; i < n - 1; i++) {
        if (a[i] > a[i-1] && a[i] > a[i+1]) {
            printf("%d ", a[i]);
            found = 1;
        }
    }
    if (found == 0) {
        printf("не найдены");
    }
    printf("\n");
    free(a);
}

void task3() {
    int n, i, bestStart, bestLen, curStart, curLen;
    int *a;
    printf("Введите длину массива: ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Неверная длина.\n");
        return;
    }
    a = (int*)malloc(n * sizeof(int));
    if (a == NULL) {
        printf("Ошибка памяти.\n");
        return;
    }
    printf("Введите элементы:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    bestStart = 0;
    bestLen = 1;
    curStart = 0;
    curLen = 1;
    for (i = 1; i < n; i++) {
        if (a[i] > a[i-1]) {
            curLen = curLen + 1;
        } else {
            if (curLen > bestLen) {
                bestLen = curLen;
                bestStart = curStart;
            }
            curStart = i;
            curLen = 1;
        }
    }
    if (curLen > bestLen) {
        bestLen = curLen;
        bestStart = curStart;
    }
    printf("Максимальная возрастающая последовательность: ");
    for (i = bestStart; i < bestStart + bestLen; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    free(a);
}

int perevernut(int x) {
    int r = 0;
    while (x > 0) {
        r = r * 10 + x % 10;
        x = x / 10;
    }
    return r;
}

void task4() {
    int a[30], i;
    printf("Исходный массив:\n");
    for (i = 0; i < 30; i++) {
        a[i] = 10 + rand() % 99990;
        printf("%d ", a[i]);
    }
    printf("\n");
    for (i = 0; i < 30; i++) {
        a[i] = perevernut(a[i]);
    }
    printf("Перевёрнутый массив:\n");
    for (i = 0; i < 30; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void task5() {
    char str[1000];
    int key, i;
    char c;
    printf("Введите строку: ");
    scanf(" %[^\n]", str);
    if (str[0] == '\0') {
        printf("Пустая строка.\n");
        return;
    }
    if (str[0] >= '0' && str[0] <= '9') {
        key = str[0] - '0';
        printf("Расшифрованная строка: ");
        for (i = 1; str[i] != '\0'; i++) {
            c = str[i];
            if (c >= 'A' && c <= 'Z') {
                c = (char)((c - 'A' - key + 26) % 26 + 'A');
            } else if (c >= 'a' && c <= 'z') {
                c = (char)((c - 'a' - key + 26) % 26 + 'a');
            }
            printf("%c", c);
        }
        printf("\n");
    } else if ((str[0] >= 'A' && str[0] <= 'Z') || (str[0] >= 'a' && str[0] <= 'z')) {
        key = 1 + rand() % 9;
        printf("Зашифрованная строка: ");
        for (i = 0; str[i] != '\0'; i++) {
            c = str[i];
            if (c >= 'A' && c <= 'Z') {
                c = (char)((c - 'A' + key) % 26 + 'A');
            } else if (c >= 'a' && c <= 'z') {
                c = (char)((c - 'a' + key) % 26 + 'a');
            }
            printf("%c", c);
        }
        printf("\nКлюч: %d\n", key);
    } else {
        printf("Строка не начинается с буквы или цифры.\n");
    }
}

void task6() {
    char str[1000];
    int len, i, j, start, wlen, maxlen;
    printf("Введите строку: ");
    scanf(" %[^\n]", str);
    len = (int)strlen(str);
    maxlen = 0;
    i = 0;
    while (i < len) {
        while (i < len && str[i] == ' ') {
            i++;
        }
        if (i >= len) {
            break;
        }
        start = i;
        while (i < len && str[i] != ' ') {
            i++;
        }
        wlen = i - start;
        if (wlen > maxlen) {
            maxlen = wlen;
        }
    }
    for (wlen = 1; wlen <= maxlen; wlen++) {
        i = 0;
        while (i < len) {
            while (i < len && str[i] == ' ') {
                i++;
            }
            if (i >= len) {
                break;
            }
            start = i;
            while (i < len && str[i] != ' ') {
                i++;
            }
            if (i - start == wlen) {
                for (j = start; j < i; j++) {
                    printf("%c", str[j]);
                }
                printf("\n");
            }
        }
    }
}

int main() {
    int choice;
    srand((unsigned)time(NULL));
    do {
        printf("\nГригорьев Андрей, группа ИТПМ-126\n");
        printf("1. Вычисление pi\n");
        printf("2. Локальные максимумы\n");
        printf("3. Максимальная возрастающая последовательность\n");
        printf("4. Перевёрнутые числа\n");
        printf("5. Шифр Цезаря\n");
        printf("6. Слова по возрастанию длины\n");
        printf("0. Выход\n");
        printf("Выбор: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1;
        }
        switch (choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 4: task4(); break;
            case 5: task5(); break;
            case 6: task6(); break;
            case 0: printf("Выход.\n"); break;
            default: printf("Неверный пункт.\n");
        }
    } while (choice != 0);
    return 0;
}
