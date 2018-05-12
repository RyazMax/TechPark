/*
Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов
в случае, когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества
и проверки принадлежности данной строки множеству.
1_1. Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
*/

#include <iostream>
#include <algorithm>
#include <string>

int hashString(const std::string str, int base) {
    const int p = 131;
    int hash = 0;
    for (const auto it : str) {
        hash = (hash*p+it)%base;
    }
    return hash;
}

template <class KeyType, class ValType>
class CHashTable {
public:
    CHashTable(int initSize, int (*f)(KeyType, int));
    CHashTable(const CHashTable &other);
    CHashTable(CHashTable&& other);
    ~CHashTable();

    CHashTable& operator = (const CHashTable &other);
    CHashTable& operator = (CHashTable&& other);

    bool Has(const KeyType key) const;
    bool Add(const KeyType key, const ValType);
    bool Remove(const KeyType key);
    bool Get(const KeyType key, ValType& res);

private:
    void resize(size_t newSize); // Перехеширование таблицы
    int  (*hashFun)(KeyType, int); // Хеш-функция

    struct CNode;
    CNode* table;
    size_t size; // Размер таблицы
    size_t count; // Число элементов
};

template <class KeyType, class ValType>
struct CHashTable<KeyType, ValType>::CNode {
    KeyType Key;
    ValType Val;
 
    enum state_t {
        EMPTY,
        DELETED,
        HAS
    } State;

    CNode (state_t state = EMPTY) : State(state) {};
    CNode (KeyType key, ValType val) : Key(key), Val(val), State(HAS) {};
};

template <class KeyType, class ValType>
CHashTable<KeyType, ValType>::CHashTable(int initSize, int (*f)(KeyType key, int base)) {
    table = new CNode[initSize];
    size = initSize;
    count = 0;
    hashFun = f;
}

template <class KeyType, class ValType>
CHashTable<KeyType, ValType>::CHashTable(const CHashTable &other) {
    size = other.size;
    count = other.count;
    table = new CNode[size];
    hashFun = other.hashFun;

    for (int i = 0; i<size; ++i) {
        table[i] = other.table[i];
    }
}

template <class KeyType, class ValType>
CHashTable<KeyType, ValType>::CHashTable(CHashTable&& other) {
    size = other.size;
    count = other.count;
    table = other.table;
    hashFun = other.hashFun;

    other.table = nullptr;
    other.size = 0;
    other.count = 0;
}

template <class KeyType, class ValType>
CHashTable<KeyType, ValType>& CHashTable<KeyType, ValType>::operator=(const CHashTable &other) {
    if (table != nullptr) {
        delete[] table;
    }

    size = other.size;
    count = other.count;
    table = new CNode[size];
    hashFun = other.hashFun;

    for (int i = 0; i<size; ++i) {
        table[i] = other.table[i];
    }

    return *this;
}

template <class KeyType, class ValType>
CHashTable<KeyType, ValType>& CHashTable<KeyType, ValType>::operator=(CHashTable&& other) {
    if (table != nullptr) {
        delete[] table;
    }
    
    size = other.size;
    count = other.count;
    table = other.table;
    hashFun = other.hashFun;

    other.table = nullptr;
    other.size = 0;
    other.count = 0;

    return *this;
}

template <class KeyType, class ValType>
CHashTable<KeyType, ValType>::~CHashTable() {
    delete[] table;
}

template <class KeyType, class ValType>
bool CHashTable<KeyType, ValType>::Has(KeyType key) const {
    int hash = hashFun(key, size);

    for (int i = 0; i<size; ++i) {
        hash = (hash + i)%size;
        if (table[hash].State == CNode::EMPTY) {
            return false;
        } else if (table[hash].State == CNode::HAS && table[hash].Key == key) {
            return true;
        }
    }

    return false;
}

template <class KeyType, class ValType>
bool CHashTable<KeyType, ValType>::Add(KeyType key, ValType val) {
    if ((float)count/size > 0.75) {

        resize(size*2);
    }
    int hash = hashFun(key, size);
    for (int i = 0; i<size; ++i) {
        hash = (hash + i)%size;
        if (table[hash].State == CNode::EMPTY) {
            break;
        } else if (table[hash].State == CNode::HAS && table[hash].Key == key) {
            return false;
        }
    }

    hash = hashFun(key, size);
    for (int i = 0; i<size; ++i) {
        hash = (hash + i) % size;
        if (table[hash].State != CNode::HAS) {
            table[hash] = CNode(key, val);
            ++count;
            return true;
        }
    }

    return false;
}

template <class KeyType, class ValType>
bool CHashTable<KeyType, ValType>::Remove(KeyType key) {
    int hash = hashFun(key, size);

    for (int i = 0; i<size; ++i) {
        hash = (hash + i)%size;
        if (table[hash].State == CNode::HAS && table[hash].Key == key) {
            table[hash] = CNode(CNode::DELETED);
            --count;
            return true;
        } else if (table[hash].State == CNode::EMPTY) {
            return false;
        }   
    }

    return false;
}

template <class KeyType, class ValType>
bool CHashTable<KeyType, ValType>::Get(KeyType key, ValType& res) {
    int hash = hashFun(key, size);

    for (int i = 0; i<size; ++i) {
        hash = (hash + i)%size;
        if (table[hash].State == CNode::HAS && table[hash].Key == key) {
            res = table[hash].Val;
            return true;
        } else if (table[hash].State == CNode::EMPTY) {
            return false;
        }
    }

    return false;
}

template <class KeyType, class ValType>
void CHashTable<KeyType, ValType>::resize(size_t newSize) {
    CNode* prevTable = table;
    size_t prevSize = size;
    table = new CNode[newSize];
    size = newSize;
    count = 0;

    for (int i = 0; i<prevSize; ++i) {
        if (prevTable[i].State == CNode::HAS) {
            this->Add(prevTable[i].Key, prevTable[i].Val);
        }
    }

    delete[] prevTable;
}

int main()
{
    CHashTable<std::string, char> hashTable(8, hashString);
    char command = 0;
    std::string key;
    while( std::cin >> command >> key ) {
        switch( command ) {
        case '?':
            std::cout << ( hashTable.Has( key ) ? "OK" : "FAIL" ) << std::endl;
            break;
        case '+':
            std::cout << ( hashTable.Add( key, ' ' ) ? "OK" : "FAIL" ) << std::endl;
            break;
        case '-':
            std::cout << ( hashTable.Remove( key ) ? "OK" : "FAIL" ) << std::endl;
            break;
        }
    }

    return 0;
}