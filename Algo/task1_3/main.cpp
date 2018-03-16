// Автор: Рязанов Максим АПО-13
/*
Условие задачи:
Даны два строго возрастающих массива целых чисел A[0..n) и B[0..m) и число k.
Найти количество таких пар индексов (i, j), что A[i] + B[j] = k. Время работы O(n + m).
n, m ≤ 100000.
*/

#include <iostream>
#include <assert.h>

using namespace std;

// Нахождение количества пар индексов
// first - первый массив
// second - второй массив
// firstSize - размер первого массива
// secondSize - размер второго массив
// number - необходимое значение суммы 2 элементов
int solve(int* first, int* second, int firstSize, int secondSize, int number)
{
    int res = 0; // Счетчик количества индексов

    for (int i = 0, j = secondSize-1; i<firstSize && j>=0;) {
        if (first[i]+second[j] == number) {
            ++res;
            --j;
            ++i;
        } else if (first[i]+second[j] < number) {
            ++i;
        } else {
            --j;
        }
    }

    return res;
}

int main()
{
    int n, m; // Размеры массивов
    int *a, *b; // Массивы
    int k; // Необходимая сумма 2 элементов 

    assert(cin >> n);
    assert(a = new int [n]);
    for (int i=0; i<n; ++i) {
        if (!(cin >> a[i])) {
            delete[] (a);
            assert(false);
        }
    }

    if (!(cin >> m)) {
        delete[] (a);
        assert(false);
    }
    if ((b = new int [m]) == 0){
        delete[] (a);
        assert(false);
    }
    for (int i=0; i<m; ++i) {
        if (!(cin >> b[i])) {
            delete[] (a);
            delete[] (b);
            assert(false);
        }
    }

    if (!(cin >> k)) {
        delete[] (a);
        delete[] (b);
        assert(false);
    }
    
    int ans = solve(a, b, n , m, k); // Ответ
    cout << ans;

    delete[] (a);
    delete[] (b);

    return 0;
}