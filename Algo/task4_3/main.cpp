// Автор Рязанов Максим АПО-13
/*
Условие задачи:
На вокзале есть некоторое количество тупиков, куда прибывают электрички.
Этот вокзал является их конечной станцией. Дано расписание движения электричек,
в котором для каждой электрички указано время ее прибытия,
а также время отправления в следующий рейс. Электрички в расписании упорядочены
по времени прибытия. Когда электричка прибывает, ее ставят в свободный тупик
с минимальным номером. При этом если электричка из какого-то тупика отправилась в момент
времени X, то электричку, которая прибывает в момент времени X, в этот тупик ставить нельзя,
а электричку, прибывающую в момент X+1 — можно.
В данный момент на вокзале достаточное количество тупиков для работы по расписанию.
Напишите программу, которая по данному расписанию определяет,
 какое минимальное количество тупиков требуется для работы вокзала.
*/

#include <iostream>
#include <assert.h>

using namespace std;

// Очередь с приоритетом на двоичной куче
class CPriorityQueue {
public:
    CPriorityQueue(size_t size = 1);
    CPriorityQueue(int* arr, size_t size);
    CPriorityQueue(const CPriorityQueue &other);
    CPriorityQueue(CPriorityQueue&& other);
    ~CPriorityQueue();

    CPriorityQueue& operator = (const CPriorityQueue &other);
    CPriorityQueue& operator = (CPriorityQueue&& other);

    // Добавление элемента в кучу
    void Add(int data);
    // Извлечение минимального элемента
    int GetMin();
    // Просмотр минимального элемента
    int ReadMin() const;
    // Размер очереди
    size_t GetSize() { return queueSize; }

private:
    // Буффер
    int* buff;
    // Размер очереди и буффера
    size_t queueSize, buffSize;

    // Поднять элемент вверх по индексу
    void siftUp(int index);
    // Спустить элемент вниз по индексу
    void siftDown(int index);
    // Расширение буффера. 0 - если выделение не удалось
    size_t expandBuff(size_t newSize);
};

// Создание пустой кучи
CPriorityQueue::CPriorityQueue(size_t size)
{
    buff = new int [size];
    buffSize = size;
    queueSize = 0;
}

// Построение кучи на массиве
CPriorityQueue::CPriorityQueue(int* arr, size_t size)
{
    assert(arr);
    buff = arr;
    queueSize = size;
    buffSize = size;

    for (int i = size/2;i >= 0;--i) {
        siftDown(i);
    }
}

CPriorityQueue::CPriorityQueue(const CPriorityQueue &other)
{ 
    buffSize = other.buffSize;
    queueSize = other.queueSize;
    buff = new int [buffSize];

    for (int i = 0; i<queueSize; ++i) {
        buff[i] = other.buff[i];
    }
}

CPriorityQueue::CPriorityQueue(CPriorityQueue&& other)
{
    buffSize = other.buffSize;
    queueSize = other.queueSize;
    buff = other.buff;

    other.buff = nullptr;
    other.buffSize = 0;
    other.queueSize = 0;
}

CPriorityQueue::~CPriorityQueue()
{
    delete[] buff;
}

CPriorityQueue& CPriorityQueue::operator=(const CPriorityQueue &other)
{
    if (buff != nullptr) {
        delete[] buff;
    }

    buffSize = other.buffSize;
    queueSize = other.queueSize;
    buff = new int [buffSize];

    for (int i = 0; i<queueSize; ++i) {
        buff[i] = other.buff[i];
    }

    return *this;
}

CPriorityQueue& CPriorityQueue::operator=(CPriorityQueue&& other)
{
    if (buff != nullptr) {
        delete[] buff;
    }

    buffSize = other.buffSize;
    queueSize = other.queueSize;
    buff = other.buff;

    other.buff = nullptr;
    other.buffSize = 0;
    other.queueSize = 0;

    return *this;
}

// Добавление значения data в очередь с приоритетом
void CPriorityQueue::Add(int data)
{
    // Расширить буффер при заполнении
    if (queueSize == buffSize) {
        expandBuff(2*buffSize);
    }

    // Добавить элемент, востановить очередь
    buff[queueSize] = data;
    siftUp(queueSize++);
 }

// Извлечение минимального элемента, если пуста assert
int CPriorityQueue::GetMin()
{
    // Проверка на пустоту
    assert(queueSize);

    // Запоминаем результат
    int result = buff[0];

    // Добавляем последний элемент в начало, востанавливаем кучу
    buff[0] = buff[--queueSize];
    siftDown(0);

    return result;
}

// Возвращает минимальный элемент, не удаляя его, если пуста assert
int CPriorityQueue::ReadMin() const
{
    // Проверка на пустоту
    assert(queueSize);

    return buff[0];
}

// Востановление подкучи относительно узла index
void CPriorityQueue::siftDown(int index)
{
    // Запоминаем текущее значение узла
    int toReplace = buff[index];

    // Пока внутри очереди
    while (index < queueSize) {
        int left = 2*index+1;
        int right = 2*index+2;

        // Поиск меньшего среди сыновей
        int smallest = toReplace;
        int smallestId = -1;
        if (left < queueSize && buff[left] < smallest) {
            smallest = buff[left];
            smallestId = left;
        }
        if (right < queueSize && buff[right] < smallest) {
            smallest = buff[right];
            smallestId = right;
        }

        // Переходим к меньшему сыну, если текущий меньше
        if (smallestId != -1) {
            buff[index] = buff[smallestId];
            index = smallestId;
        } else {   // Куча востановлена, вставляем запомненое значение
            buff[index] = toReplace;
            return;
        }
    }
}

// Востановление кучи вверх от узла index
void CPriorityQueue::siftUp(int index) {
    // Запоминаем текущее значение узла
    int toReplace = buff[index];

    // Пока родитель не меньше или не в корне
    while (index >= 0) {
        int parent = (index-1)/2;
        if (index == 0 || buff[parent] <= toReplace) {
            buff[index] = toReplace;
            return;
        }

        // Переносим родителя на место текущего узла
        buff[index] = buff[parent];
        index = parent;
    }
}

// Расширение буффера, 0 - если расширение не удалось
size_t CPriorityQueue::expandBuff(size_t newSize)
{
    // Выделяем память
    int* newBuff = new int [newSize];

    // Перемещаем данные
    for (int i=0; i < queueSize; ++i) {
        newBuff[i] = buff[i];
    }
    buffSize = newSize;

    // Удаляем старый буффер
    if (buff != 0) {
        delete[] buff;
    }
    buff = newBuff;

    return buffSize;
}

int main()
{
    // Количество электричек
    int trainsCount = 0;
    cin >> trainsCount;

    // Минимальное количество тупиков
    int waysCount = 0;
    CPriorityQueue queue;

    for (int i=0; i<trainsCount; ++i) {
        int arrivalTime = 0, departureTime = 0;

        cin >> arrivalTime >> departureTime;

        // Проверить уехала ли саммая "ранняя" электричка, добавить отбытие новой
        if (queue.GetSize() != 0 && queue.ReadMin() < arrivalTime) {
            queue.GetMin();
        }
        queue.Add(departureTime);

        // Увеличить счетчик, если количество используемых путей выше
        if (queue.GetSize() > waysCount) {
            waysCount = queue.GetSize();
        }
    }

    cout << waysCount;
    return 0;
}