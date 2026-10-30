#include <stdio.h>
#include <math.h>

void task1(void)
{
    long long number;
    int digits[8];
    int flag;
    int sum = 0;
    int i;

    printf("Введите 8-значное число: ");
    scanf("%lld", &number);

    for (i = 7; i >= 0; i--)
    {
        digits[i] = number % 10;
        number = number / 10;
    }

    for (i = 0; i < 8; i++)
    {
        printf("Включить цифру %d (позиция %d) в сумму? (0/1): ", digits[i], i + 1);
        scanf("%d", &flag);
        sum = sum + digits[i] * flag;
    }

    printf("Сумма: %d\n", sum);
}

void task2(void)
{
    long long number;
    long long result = 0;
    long long place = 1;
    int digit;
    int i;

    printf("Введите 6-значное число: ");
    scanf("%lld", &number);

    for (i = 0; i < 6; i++)
    {
        digit = number % 10;
        number = number / 10;
        result = result + (digit % 2) * place;
        place = place * 10;
    }

    printf("Результат: %06lld\n", result);
}

void print_line(double x1, double y1, double x2, double y2)
{
    double A = y1 - y2;
    double B = x2 - x1;
    double C = x1 * y2 - x2 * y1;
    printf("(%.2f)x + (%.2f)y + (%.2f) = 0\n", A, B, C);
}

void task3(void)
{
    double x1, y1, x2, y2, x3, y3;

    printf("Введите x и y первой вершины: ");
    scanf("%lf %lf", &x1, &y1);
    printf("Введите x и y второй вершины: ");
    scanf("%lf %lf", &x2, &y2);
    printf("Введите x и y третьей вершины: ");
    scanf("%lf %lf", &x3, &y3);

    printf("Сторона 1-2: ");
    print_line(x1, y1, x2, y2);
    printf("Сторона 2-3: ");
    print_line(x2, y2, x3, y3);
    printf("Сторона 3-1: ");
    print_line(x3, y3, x1, y1);
}

void task4(void)
{
    int a, b, c;
    int t1, t2, t3, result;

    printf("A\tB\tC\tA|B\t!(A|B)\t!(A|B)&C\t(!(A|B)&C)~A\n");

    for (a = 0; a <= 1; a++)
    {
        for (b = 0; b <= 1; b++)
        {
            for (c = 0; c <= 1; c++)
            {
                t1 = a | b;
                t2 = !t1;
                t3 = t2 & c;
                result = (t3 == a);
                printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", a, b, c, t1, t2, t3, result);
            }
        }
    }
}

void task5(void)
{
    int n1, n2;
    int a, b, c, x, y, z;

    printf("Введите два трёхзначных числа: ");
    scanf("%d %d", &n1, &n2);

    a = n1 / 100;
    b = n1 / 10 % 10;
    c = n1 % 10;
    x = n2 / 100;
    y = n2 / 10 % 10;
    z = n2 % 10;

    printf("a + z = %d\n", a + z);
    printf("b + x = %d\n", b + x);
    printf("c + y = %d\n", c + y);
}

void task6(void)
{
    int n;

    printf("Введите четырёхзначное число: ");
    scanf("%d", &n);

    printf("ab + cd = %d\n", n / 100 + n % 100);
}

void task7(void)
{
    double x, y;

    printf("Введите два числа: ");
    scanf("%lf %lf", &x, &y);

    printf("max = %g\n", (x + y + fabs(x - y)) / 2);
}

int main(void)
{
    int choice;

    do
    {
        printf("\n=== LabRab1V1 ===\n");
        printf("1-7 - номер задания, 0 - выход\n");
        printf("Ваш выбор: ");
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
            case 0: break;
            default: printf("Нет такого пункта!\n");
        }
    } while (choice != 0);

    return 0;
}