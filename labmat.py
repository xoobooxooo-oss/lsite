def to_number(text):
    value = float(text)
    if value.is_integer():
        return int(value)
    return value


def format_number(x):
    if isinstance(x, float):
        return str(round(x, 6))
    return str(x)


def read_positive_int(invitation):
    while True:
        try:
            value = int(input(invitation))
        except ValueError:
            print("Ошибка: введите целое число")
            continue
        if value <= 0:
            print("Ошибка: число должно быть больше нуля")
            continue
        return value


def read_number(invitation):
    while True:
        try:
            return to_number(input(invitation))
        except ValueError:
            print("Ошибка: введите число")


def input_matrix(rows, cols):
    if rows <= 0 or cols <= 0:
        raise ValueError("Количество строк и столбцов должно быть положительным")
    matrix = []
    for i in range(rows):
        while True:
            parts = input(f"Введите строку {i + 1}: ").split()
            if len(parts) != cols:
                print(f"Ошибка: нужно ровно {cols} элементов")
                continue
            try:
                row = [to_number(p) for p in parts]
            except ValueError:
                print("Ошибка: все элементы должны быть числами")
                continue
            matrix.append(row)
            break
    return matrix


def read_matrix():
    rows = read_positive_int("Количество строк: ")
    cols = read_positive_int("Количество столбцов: ")
    return input_matrix(rows, cols)


def print_matrix(matrix):
    cells = [[format_number(x) for x in row] for row in matrix]
    for row in cells:
        print(" ".join(row))


def same_size(a, b):
    if not a or not b:
        return False
    return len(a) == len(b) and len(a[0]) == len(b[0])


def add_matrices(a, b):
    if not same_size(a, b):
        raise ValueError("Размеры матриц не совпадают")
    result = [ ]
    for i in range(len(a)):
        row = []
        for j in range(len(a[0])):
            row.append(a[i][j] + b[i][j])
        result.append(row)
    return result


def subtract_matrices(a, b):
    if not same_size(a, b):
        raise ValueError("Размеры матриц не совпадают")
    result = []
    for i in range(len(a)):
        row = []
        for j in range(len(a[0])):
            row.append(a[i][j] - b[i][j])
        result.append(row)
    return result


def multiply_by_scalar(matrix, scalar):
    result = []
    for i in range(len(matrix)):
        row = []
        for j in range(len(matrix[0])):
            row.append(scalar * matrix[i][j])
        result.append(row)
    return result


def transpose(matrix):
    rows = len(matrix)
    cols = len(matrix[0])
    result = [[0] * rows for _ in range(cols)]
    for i in range(rows):
        for j in range(cols):
            result[j][i] = matrix[i][j]
    return result


def multiply_matrices(a, b):
    if len(a[0]) != len(b):
        raise ValueError("Число столбцов A должно равняться числу строк B")
    m = len(a)
    n = len(b)
    k = len(b[0])
    result = [[0] * k for _ in range(m)]
    for i in range(m):
        for j in range(k):
            total = 0
            for t in range(n):
                total += a[i][t] * b[t][j]
            result[i][j] = total
    return result


def check_square(matrix):
    if not matrix:
        raise ValueError("Матрица пуста")
    if len(matrix) != len(matrix[0]):
        raise ValueError("Матрица должна быть квадратной")


def main_diagonal(matrix):
    check_square(matrix)
    return [matrix[i][i] for i in range(len(matrix))]


def secondary_diagonal(matrix):
    check_square(matrix)
    n = len(matrix)
    return [matrix[i][n - 1 - i] for i in range(n)]


def trace(matrix):
    return sum(main_diagonal(matrix))


def get_minor(matrix, row, col):
    check_square(matrix)
    n = len(matrix)
    if not (0 <= row < n and 0 <= col < n):
        raise ValueError("Некорректные индексы строки или столбца")
    return [
        [matrix[i][j] for j in range(n) if j != col]
        for i in range(n)
        if i != row
    ]


def cofactor(matrix, row, col):
    minor = get_minor(matrix, row, col)
    if len(minor) == 0:
        return 1
    return (-1) ** (row + col) * determinant(minor)


def determinant(matrix):
    check_square(matrix)
    n = len(matrix)
    if n == 1:
        return matrix[0][0]
    if n == 2:
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]
    total = 0
    for j in range(n):
        total += matrix[0][j] * cofactor(matrix, 0, j)
    return total


def identity_matrix(n):
    return [[1 if i == j else 0 for j in range(n)] for i in range(n)]


def is_identity(matrix, eps=1e-9):
    n = len(matrix)
    for i in range(n):
        if len(matrix[i]) != n:
            return False
        for j in range(n):
            expected = 1 if i == j else 0
            if abs(matrix[i][j] - expected) >= eps:
                return False
    return True


def inverse_matrix(matrix, eps=1e-12):
    check_square(matrix)
    n = len(matrix)
    e = identity_matrix(n)
    aug = [
        [float(x) for x in matrix[i]] + [float(x) for x in e[i]]
        for i in range(n)
    ]
    for col in range(n):
        pivot = -1
        for r in range(col, n):
            if abs(aug[r][col]) > eps:
                pivot = r
                break
        if pivot == -1:
            raise ValueError("Матрица вырождена, обратной не существует")
        aug[col], aug[pivot] = aug[pivot], aug[col]
        lead = aug[col][col]
        aug[col] = [x / lead for x in aug[col]]
        for r in range(n):
            if r != col:
                factor = aug[r][col]
                aug[r] = [aug[r][c] - factor * aug[col][c] for c in range(2 * n)]
    return [row[n:] for row in aug]


def matrix_stats(matrix):
    if not matrix or not matrix[0]:
        raise ValueError("Матрица пуста")
    cols = len(matrix[0])
    for row in matrix:
        if len(row) != cols:
            raise ValueError("Строки матрицы имеют разную длину")
    flat = [x for row in matrix for x in row]
    return {
        "rows": len(matrix),
        "cols": cols,
        "min": min(flat),
        "max": max(flat),
        "sum": sum(flat),
        "mean": sum(flat) / len(flat),
        "row_sums": [sum(row) for row in matrix],
        "col_sums": [
            sum(matrix[i][j] for i in range(len(matrix))) for j in range(cols)
        ],
    }


def print_stats(stats):
    print(f"Размер: {stats['rows']} × {stats['cols']}")
    print("Минимальный элемент:", format_number(stats["min"]))
    print("Максимальный элемент:", format_number(stats["max"]))
    print("Сумма элементов:", format_number(stats["sum"]))
    print("Среднее значение:", format_number(stats["mean"]))
    print("Суммы строк:", ", ".join(format_number(x) for x in stats["row_sums"]))
    print("Суммы столбцов:", ", ".join(format_number(x) for x in stats["col_sums"]))


MENU = [
    "1. Ввести матрицу",
    "2. Вывести матрицу",
    "3. Сложить две матрицы",
    "4. Вычесть две матрицы",
    "5. Умножить матрицу на число",
    "6. Транспонировать матрицу",
    "7. Умножить две матрицы",
    "8. Найти определитель",
    "9. Найти обратную матрицу",
    "10. Вывести характеристики матрицы",
    "11. Диагонали и след матрицы",
    "12. Минор и алгебраическое дополнение",
    "0. Завершить программу",
]


def print_menu():
    print()
    print("МАТРИЧНЫЙ КАЛЬКУЛЯТОР")
    for line in MENU:
        print(line)


def ask_name(invitation):
    while True:
        name = input(invitation).strip().upper()
        if name in ["A", "B"]:
            return name
        print("Ошибка: введите A или B")


def ask_matrix(store, action):
    name = ask_name(f"Какую матрицу {action} (A/B): ")
    if store[name] is None:
        raise ValueError(f"Матрица {name} ещё не введена")
    return store[name]


def action_input(store):
    name = ask_name("В какую ячейку сохранить матрицу (A/B): ")
    store[name] = read_matrix()


def action_print(store):
    print_matrix(ask_matrix(store, "вывести"))


def action_binary(store, operation):
    for name in ("A", "B"):
        if store[name] is None:
            raise ValueError(f"Матрица {name} ещё не введена")
    print("Результат:")
    print_matrix(operation(store["A"], store["B"]))


def action_scalar(store):
    matrix = ask_matrix(store, "умножить")
    k = read_number("Введите число k: ")
    print("Результат:")
    print_matrix(multiply_by_scalar(matrix, k))


def action_transpose(store):
    print("Результат:")
    print_matrix(transpose(ask_matrix(store, "транспонировать")))


def action_determinant(store):
    value = determinant(ask_matrix(store, "взять"))
    print("Определитель:", format_number(value))


def action_inverse(store):
    matrix = ask_matrix(store, "обратить")
    inv = inverse_matrix(matrix)
    print("Обратная матрица:")
    print_matrix(inv)
    if is_identity(multiply_matrices(matrix, inv)):
        print("Проверка A * A^(-1) = E пройдена")
    else:
        print("Проверка A * A^(-1) = E не пройдена")


def action_stats(store):
    print_stats(matrix_stats(ask_matrix(store, "описать")))


def action_diagonals(store):
    matrix = ask_matrix(store, "разобрать")
    main_d = main_diagonal(matrix)
    sec_d = secondary_diagonal(matrix)
    print("Главная диагональ:", ", ".join(format_number(x) for x in main_d))
    print("Побочная диагональ:", ", ".join(format_number(x) for x in sec_d))
    print("Сумма главной:", format_number(sum(main_d)))
    print("Сумма побочной:", format_number(sum(sec_d)))
    print("След:", format_number(trace(matrix)))


def action_minor(store):
    matrix = ask_matrix(store, "разобрать")
    check_square(matrix)
    n = len(matrix)
    row = read_number("Строка (индекс с 0): ")
    col = read_number("Столбец (индекс с 0): ")
    if not (0 <= row < n and 0 <= col < n):
        raise ValueError("Некорректные индексы строки или столбца")
    if int(row) != row or int(col) != col:
        raise ValueError("Индексы должны быть целыми")
    row = int(row)
    col = int(col)
    print("Минор:")
    print_matrix(get_minor(matrix, row, col))
    print("Алгебраическое дополнение:", format_number(cofactor(matrix, row, col)))


def main():
    store = {"A": None, "B": None}
    while True:
        print_menu()
        choice = input("Выберите пункт: ").strip()
        if choice == "0":
            print("Программа завершена")
            break
        if choice == "1":
            action_input(store)
        elif choice == "2":
            action_print(store)
        elif choice == "3":
            action_binary(store, add_matrices)
        elif choice == "4":
            action_binary(store, subtract_matrices)
        elif choice == "5":
            action_scalar(store)
        elif choice == "6":
            action_transpose(store)
        elif choice == "7":
            action_binary(store, multiply_matrices)
        elif choice == "8":
            action_determinant(store)
        elif choice == "9":
            action_inverse(store)
        elif choice == "10":
            action_stats(store)
        elif choice == "11":
            action_diagonals(store)
        elif choice == "12":
            action_minor(store)
        else:
            print("Ошибка: нет такого пункта меню")
            continue


if __name__ == "__main__":
    main()