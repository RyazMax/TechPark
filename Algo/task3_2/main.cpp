// Автор Рязанов Максим АПО-13
/*
Условие задачи:
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back
Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
Если дана команда pop*, то число b - ожидаемое значение.
Если команда pop вызвана для пустой структуры данных, то ожидается “-1”. 
Реализовать дек с динамическим зацикленным буфером.
*/

#include <iostream>
#include <assert.h>

using namespace std;

// Дек на зацикленном буффере
class CDeque {
public:
    CDeque(size_t size = 2);
    CDeque(const CDeque &other);
    CDeque(CDeque&& other);
    ~CDeque();

    CDeque& operator=(const CDeque&);
    CDeque& operator=(CDeque&&);

    // Добавление элемента в конец
    void PushBack(int data);
    // Добавление элемента в начало
    void PushFront(int data);
    // Извлечение с конца
    int PopBack();
    // Извлечение с начала
    int PopFront();
    // Пуста ли очередь
    bool isEmpty() const { return head == tail; }

private:
    // Буффер
    int* buff;
    int head, tail; // Индекс первого, и следующего за последним
    size_t buffSize; // Размер буффера

    // Расширение буффера
    size_t expandBuff(size_t newSize);
};

CDeque::CDeque(size_t size)
{
    buff = new int [size];
    buffSize = size;
    head = tail = 0;
}

CDeque::CDeque(const CDeque &other)
{
    buffSize = other.buffSize;
    head = other.head;
    tail = other.tail;
    buff  = new int [buffSize];

    for (int i = 0; i<buffSize;++i) {
        buff[i] = other.buff[i];
    }
}

CDeque::CDeque(CDeque&& other)
{
    buffSize = other.buffSize;
    head = other.head;
    tail = other.tail;
    buff  = other.buff;

    for (int i = 0; i<buffSize;++i) {
        buff[i] = other.buff[i];
    }

    other.buff = nullptr;
    other.buffSize = 0;
    other.head = 0;
    other.tail = 0;
}

CDeque::~CDeque()
{
    delete[] buff;
}

CDeque& CDeque::operator=(const CDeque &other)
{
    if (buff != nullptr) {
        delete[] buff;
    }
    buffSize = other.buffSize;
    head = other.head;
    tail = other.tail;
    buff  = new int [buffSize];

    for (int i = 0; i<buffSize;++i) {
        buff[i] = other.buff[i];
    }

    return *this;
}

CDeque& CDeque::operator=(CDeque &&other)
{
    if (buff != nullptr) {
        delete[] buff;
    }
    buffSize = other.buffSize;
    head = other.head;
    tail = other.tail;
    buff  = other.buff;

    other.buff = nullptr;
    other.buffSize = 0;
    other.head = 0;
    other.tail = 0;

    return *this;
}

// Добавление элемента в конце дека, расширяет буффер при заполнении
void CDeque::PushBack(int data)
{
    // Проверка заполнения буффера
    if ((tail+1)%buffSize == head) {
        expandBuff(2*buffSize);
    }

    // Добавляем значение
    buff[tail] = data;
    // Сдвигаем указатель на хвост вперед
    tail = (tail + 1)%buffSize;
}

// Добавление элемента в начало дека, расширяет буффер при заполнении
void CDeque::PushFront(int data)
{
    // Проверка заполнения буффера
    if ((head - 1 + buffSize)%buffSize == tail) {
        expandBuff(2*buffSize);
    }

    // Сдвигаем указатель на голову назад
    head = (head - 1 + buffSize)%buffSize;
    // Добавляем значение
    buff[head] = data;
}

// Извлечение элемента из конца дека, assert если пуст
int CDeque::PopBack()
{
    // Проверка дека на пустоту
    assert(!isEmpty());

    // Сдвигаем указатель на хвост назад
    tail = (tail - 1 + buffSize)%buffSize;
    return buff[tail];
}

// Извлечение элемента из начала дека, assert если пуст
int CDeque::PopFront()
{
    // Проверка дека на пустоту
    assert(!isEmpty());

    // Запомимаем то, что нужно вернуть
    int data = buff[head];
    // Сдвигаем указатель на голову вперед
    head = (head + 1)%buffSize;
    return data;
}

// Расширение буффера до newSize и перенос значений в него
// Возвращает новый размер буффера
// 0 при неудачном выделении памяти
size_t CDeque::expandBuff(size_t newSize)
{
    // Выделяем память
    int* newBuff = new int [newSize];
    // Если выделение не удалось
    if (newBuff == nullptr){
        return 0;
    }

    // Перемещаем данные
    for (int i=0; i<buffSize; ++i) {
        newBuff[i] = buff[(head + i)%buffSize];
    }
    head = 0;
    tail = buffSize - 1;
    buffSize = newSize;

    // Удаляем старый буффер
    if (buff != nullptr) {
        delete[] buff;
    }
    buff = newBuff;

    return buffSize;
}

int main()
{
    // Число комманд
    int cmdCount = 0;
    cin >> cmdCount;

    CDeque deque;
    for (int i=0; i<cmdCount; ++i) {
        int command = 0;
        int value = 0;

        cin >> command >> value;

        switch(command) {
            case 1:
                deque.PushBack(value);
                break;
            case 2:
                if (deque.isEmpty() && value != -1 || 
                    !deque.isEmpty() && deque.PopBack() != value)
                    {
                        cout<<"NO";
                        return 0;
                    } 
                break;
            case 3:
                deque.PushFront(value);
                break;
            case 4:
                if (deque.isEmpty() && value != -1 || 
                    !deque.isEmpty() && deque.PopFront() != value)
                    {
                        cout<<"NO";
                        return 0;
                    } 
                break;    
        }
    }
    cout << "YES";
    return 0;
}