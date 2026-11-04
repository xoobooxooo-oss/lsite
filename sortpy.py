T1 = [64, 34, 25, 12, 22, 11, 90]


def bubble_sort(arr):
    n = len(arr)
    for i in range(n - 1):
        swapped = False
        for j in range(n - 1 - i):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                swapped = True
        if i < 2:
            print("После прохода", i + 1, ":", arr)
        if not swapped:
            break


def insertion_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j = j - 1
        arr[j + 1] = key
        if i <= 3:
            print("После вставки", i, ":", arr)


def selection_sort(arr):
    n = len(arr)
    for i in range(n - 1):
        min_index = i
        for j in range(i + 1, n):
            if arr[j] < arr[min_index]:
                min_index = j
        arr[i], arr[min_index] = arr[min_index], arr[i]
        if i < 3:
            print("Шаг", i + 1, ": минимум на индексе", min_index, ", список", arr)


def heapify(arr, n, i):
    largest = i
    left = 2 * i + 1
    right = 2 * i + 2
    if left < n and arr[left] > arr[largest]:
        largest = left
    if right < n and arr[right] > arr[largest]:
        largest = right
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)


def heap_sort(arr):
    n = len(arr)
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)
    print("Max-куча:", arr)
    for i in range(n - 1, 0, -1):
        arr[0], arr[i] = arr[i], arr[0]
        heapify(arr, i, 0)
        if n - i <= 2:
            print("После извлечения", n - i, ":", arr)


def partition(arr, low, high):
    pivot = arr[high]
    i = low - 1
    for j in range(low, high):
        if arr[j] <= pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1


def quick_sort(arr, low, high):
    if low < high:
        p = partition(arr, low, high)
        quick_sort(arr, low, p - 1)
        quick_sort(arr, p + 1, high)


def main():
    print("T1:", T1)

    print("\nСортировка пузырьком")
    a = T1[:]
    bubble_sort(a)
    print("Результат:", a)

    print("\nСортировка вставками")
    a = T1[:]
    insertion_sort(a)
    print("Результат:", a)

    print("\nСортировка выбором")
    a = T1[:]
    selection_sort(a)
    print("Результат:", a)

    print("\nПирамидальная сортировка")
    a = T1[:]
    heap_sort(a)
    print("Результат:", a)

    print("\nБыстрая сортировка")
    a = T1[:]
    quick_sort(a, 0, len(a) - 1)
    print("Результат:", a)


if __name__ == "__main__":
    main()
