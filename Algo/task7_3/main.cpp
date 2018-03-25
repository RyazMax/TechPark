// Автор Рязанов Максим
/* 
Условие:
Дан массив неотрицательных целых 64-разрядных чисел.
Количество чисел не больше 106. Отсортировать массив 
методом MSD по битам (бинарный QuickSort).
*/

#include <iostream>

typedef unsigned long long ull_t;

// Определение позиции опорного элемента
int partion(ull_t* arr, int first , int last, ull_t mask)
{
    int left = first; // Текущая левая граница
    int right = last; // Текущая правая граница

    while (left <= right) {
        while (left<=last && (arr[left] & mask) == 0) {
            ++left;
        }
        while (right>=first && (arr[right] & mask)) {
            --right;
            
        }

        if (left < right) {
            std::swap(arr[left++], arr[right--]);
        }   
    }

    return left;
}

// Побитовая сортировка
void binnaryMSD(ull_t* arr, int first, int last, ull_t mask)
{
    int pivot = 0; // Опорный элемент

    if (mask && first<last) {
        pivot = partion(arr, first, last, mask);

        binnaryMSD(arr, first, pivot-1, mask>>1);
        binnaryMSD(arr, pivot, last, mask>>1);
    }
}

int main()
{
    int size = 0;
    std::cin>>size;

    ull_t *arr = new ull_t[size];

    for (int i = 0; i<size; ++i) {
        std::cin>>arr[i];
    }

    binnaryMSD(arr, 0, size-1, (ull_t)1<<63);

    for (int i = 0; i<size; ++i) {
        std::cout<<arr[i]<<" ";
    }

    delete[] arr;

    return 0;
}