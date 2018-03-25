// Автор Рязанов Максим АПО-13
/* Условие задачи :
В супермаркете решили оптимизировать показ рекламы.
Известно расписание прихода и ухода покупателей (два целых числа).
Каждому покупателю необходимо показать минимум 2 рекламы.
Рекламу можно транслировать только в целочисленные моменты времени.
Покупатель может видеть рекламу от момента прихода до момента ухода из магазина.
В каждый момент времени может показываться только одна реклама.
Считается, что реклама показывается мгновенно.
Если реклама показывается в момент ухода или прихода, то считается,
что посетитель успел её посмотреть. Требуется определить минимальное
число показов рекламы.
*/

#include <iostream>

// Структура покупатель, содержит время входа и выхода покупателья
struct CConsumer
{
    int InTime;
    int OutTime;

    CConsumer() = default;
    CConsumer(int in, int out) : InTime(in), OutTime(out) {}
    bool operator<(const CConsumer& other) const;
};

// Переопределенный оператор <.
// Условие истинности: время выхода меньше или если равны то время входа больше.
bool CConsumer::operator<(const CConsumer& other) const
{
    if (OutTime < other.OutTime) {
        return true;
    }
    else if (OutTime == other.OutTime) {
        return InTime > other.InTime;
    }
    else {
        return false;
    }
}

// Функтор "меньше" по умолчанию
template<class T>
bool isLessDefault(const T& left, const T& right)
{
    return left<right;
}

// Сортировка слиянием
template <class T, class Compare>
void merge_sort(T* first, T*  last, const Compare& functor)
{
    int size = last-first; // Размер массива
    T* buff = new T [size]; // Буффер для произведения слияния

    for (int blockSize = 1; blockSize < size; blockSize *= 2) {
        int blockBegin = 0; // Начало текущего блока

        while (blockBegin + blockSize < size) {
            // Левая граница текущего блока
            int left = blockBegin; 
            // Правая граница текущего блока, и левая следующего
            int middle = blockBegin + blockSize; 
            // Правая граница следующего блока
            int right = std::min(blockBegin + 2*blockSize, size); 

            int currentLeft = left; // Индекс первого из левого блока
            int currentRight = middle; // Индекс первого из правого блока
            int currentCommon = left; // Индекс последнего из слитого блока

            while (currentLeft < middle || currentRight < right) {
                if (currentRight == right || (currentLeft < middle && 
                    functor(first[currentLeft], first[currentRight])))
                {
                    buff[currentCommon++] = first[currentLeft++];
                }
                else {
                    buff[currentCommon++] = first[currentRight++];
                }
            }

            // Перенос обратно в основной массив
            for (int i = blockBegin; i < right; ++i) {
                first[i] = buff[i];
            }

            blockBegin = right;
        }
    }
    delete[] buff;
}

// Вычисление минимального количетства показов рекламы
int solve(CConsumer* arr, int size)
{
    // Времена 2 последних показов
    int time1 = arr[0].OutTime-1, time2 =arr[0].OutTime;
    int count = 2;

    for (int i=1; i<size; ++i) {
        if (arr[i].InTime > time1) {
            if (arr[i].InTime > time2) {
                time2 = arr[i].OutTime;
                time1 = arr[i].OutTime-1;
                count += 2;
            } else {
                time1 = time2;
                time2 = arr[i].OutTime;
                ++count;
            }
        }
    }

    return count;
}

int main()
{    
    int consumerCount = 0;
    std::cin >> consumerCount;

    CConsumer *arr = new CConsumer[consumerCount];

    for (int i = 0; i<consumerCount; ++i) {
        std::cin>>arr[i].InTime>>arr[i].OutTime;
    }

    merge_sort(arr, arr+consumerCount, isLessDefault<CConsumer>);
    int ans = solve(arr, consumerCount);

    std::cout << ans;
    
    delete[] arr;
    return 0;
}
