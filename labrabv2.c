#include <stdio.h>

#define BASE 6

void clear_input(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void task1(void)
{
    long long n;
    int digits[64];
    int count = 0;
    int i;

    printf("Введите неотрицательное целое число: ");
    if (scanf("%lld", &n) != 1 || n < 0)
    {
        printf("Ошибка: нужно неотрицательное целое число.\n");
        clear_input();
        return;
    }

    if (n == 0)
    {
        printf("Результат: 0\n");
        return;
    }

    while (n > 0)
    {
        digits[count] = n % BASE;
        n = n / BASE;
        count++;
    }

    printf("Результат: ");
    for (i = count - 1; i >= 0; i--)
    {
        printf("%d", digits[i]);
    }
    printf("\n");
}

void task2(void)
{
    long long N;
    long long m = 0;
    int i = 0;

    printf("Введите N: ");
    if (scanf("%lld", &N) != 1)
    {
        printf("Ошибка ввода.\n");
        clear_input();
        return;
    }

    while (m <= N)
    {
        i++;
        m = m + i;
    }

    printf("Первое число больше %lld: m%d = %lld\n", N, i, m);
}

void task3(void)
{
    long long n;
    int up = 1;
    int down = 1;
    int right;
    int left;

    printf("Введите число: ");
    if (scanf("%lld", &n) != 1)
    {
        printf("Ошибка ввода.\n");
        clear_input();
        return;
    }
    if (n < 0) n = -n;

    right = n % 10;
    n = n / 10;
    while (n > 0)
    {
        left = n % 10;
        if (left >= right) up = 0;
        if (left <= right) down = 0;
        right = left;
        n = n / 10;
    }

    if (up && down) printf("В числе одна цифра (порядок не определён).\n");
    else if (up) printf("Цифры расположены по возрастанию.\n");
    else if (down) printf("Цифры расположены по убыванию.\n");
    else printf("Цифры никак не упорядочены.\n");
}

void task4(void)
{
    long long x;
    long long sum = 0;
    int index = 0;

    printf("Вводите натуральные числа, 0 - конец ввода:\n");
    if (scanf("%lld", &x) != 1) { printf("Ошибка ввода.\n"); clear_input(); return; }

    while (x != 0)
    {
        index++;
        if (index % 3 != 0 && x % 3 == 0)
        {
            sum = sum + x;
        }
        if (scanf("%lld", &x) != 1) { printf("Ошибка ввода.\n"); clear_input(); return; }
    }

    printf("Сумма: %lld\n", sum);
}

void task5(void)
{
    int n, a, b, c;
    int count = 0;

    for (n = 100; n <= 999; n++)
    {
        a = n / 100;
        b = n / 10 % 10;
        c = n % 10;
        if (a != b && a != c && b != c)
        {
            printf("%d ", n);
            count++;
            if (count % 15 == 0) printf("\n");
        }
    }
    printf("\nВсего: %d\n", count);
}

void task6(void)
{
    long long x, y;
    long long a, b, t;
    long long gcd, lcm;

    printf("Введите два натуральных числа: ");
    if (scanf("%lld %lld", &x, &y) != 2 || x <= 0 || y <= 0)
    {
        printf("Ошибка: нужны два натуральных числа.\n");
        clear_input();
        return;
    }

    a = x;
    b = y;
    while (b != 0)
    {
        t = a % b;
        a = b;
        b = t;
    }
    gcd = a;
    lcm = x / gcd * y;

    printf("НОД = %lld, НОК = %lld\n", gcd, lcm);
}

void task7(void)
{
    long long n;
    long long first;
    long long term;
    long long sum = 0;
    long long k;

    printf("Введите натуральное число: ");
    if (scanf("%lld", &n) != 1 || n <= 0)
    {
        printf("Ошибка: нужно натуральное число.\n");
        clear_input();
        return;
    }

    first = n * (n - 1) + 1;
    printf("%lld^3 = ", n);
    for (k = 0; k < n; k++)
    {
        term = first + 2 * k;
        sum = sum + term;
        printf("%lld", term);
        if (k < n - 1) printf(" + ");
    }
    printf(" = %lld\n", sum);
}

void task8(void)
{
    long long n;
    long long a, b;
    int found = 0;

    printf("Введите натуральное число: ");
    if (scanf("%lld", &n) != 1 || n <= 0)
    {
        printf("Ошибка: нужно натуральное число.\n");
        clear_input();
        return;
    }

    for (a = 1; a * a <= n; a++)
    {
        for (b = a; a * a + b * b <= n; b++)
        {
            if (a * a + b * b == n)
            {
                printf("%lld = %lld^2 + %lld^2\n", n, a, b);
                found = 1;
            }
        }
    }
    if (!found) printf("Число нельзя представить в виде суммы квадратов.\n");
}

int main(void)
{
    int choice;

    do
    {
        printf("\n=== LabRab2V1 ===\n");
        printf("1-8 - номер задания, 0 - выход\nВаш выбор: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Ошибка ввода!\n");
            return 1;
        }
        switch (choice)
        {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 4: task4(); break;
            case 5: task5(); break;
            case 6: task6(); break;
            case 7: task7(); break;
            case 8: task8(); break;
            case 0: break;
            default: printf("Нет такого пункта!\n");
        }
    } while (choice != 0);

    return 0;
}