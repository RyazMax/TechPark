// Автор Рязанов Максим АПО-13
/*
Условие задачи:
Дан массив целых чисел А[0..n-1]. 
Известно, что на интервале [0, m] значения массива строго возрастают,
 а на интервале [m, n-1] строго убывают. Найти m за O(log m).
2 ≤ n ≤ 10000.
*/

#include <iostream>
#include <assert.h>

#define MIN_N 2
#define MAX_N 10000

using namespace std;

// Поиск индекса m, c помощью бинарного поиска
// array - исходный массив
// size - размер массива
int findM(int* array, int size)
{
    int left = 0, right = size-1; // Левая и правая границы диапозона включительно
    while (left<right) {
        int medium = (left+right)/2; // Середина округляется вниз

        if (array[medium]<array[medium+1]) {
            left =  medium+1; 
        } else {
            right = medium;
        }
    }
    return left;
}

int main()
{
    int n; // Размер массива
    int* array; // Массив

    assert(cin >> n);
    assert(n>=MIN_N && n<=MAX_N);

    assert(array = new int [n]);
    for (int i=0; i<n; ++i) {
        if (!(cin >> array[i])) {
            delete[] array;
            assert(false);
        }
    }

    int ans = findM(array, n); // Ответ
    cout << ans;

    delete[] array;

    return 0;
}
