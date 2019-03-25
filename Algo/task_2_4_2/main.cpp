// Рязанов Максим АПО-13
/*
Дано число N и N строк. Каждая строка содержит команду добавления или удаления натуральных чисел, 
а также запрос на получение k-ой порядковой статистики. 
Команда добавления числа A задается положительным числом A, 
команда удаления числа A задается отрицательным числом “-A”. 
Запрос на получение k-ой порядковой статистики задается числом k. 
Требуемая скорость выполнения запроса - O(log n).
*/

#include <iostream>

template <class T>
struct CNode {
    T Data;
    char Height;
    int Count;

    CNode* Left, *Right;

    CNode(T data) : Data(data), Left(nullptr), Right(nullptr), Height(1), Count(1) {}
};

template <class T>
class CAVLtree {
public:
    CAVLtree();
    ~CAVLtree();

    void Add(T val);
    void Delete(T val);
    CNode<T>* findByPos(int pos);
    void show(CNode<T>* node, int lvl);
private:
    CNode<T>* head;

    char getHeight(CNode<T>* node);
    int getCount(CNode<T>* node);
    int bfactor(CNode<T>* node);
    void fixHeight(CNode<T>* node);
    void destroy(CNode<T>* node);
    
    CNode<T>* remove(CNode<T>* node, T val);
    CNode<T>* removeMax(CNode<T>* node);
    CNode<T>* popMax(CNode<T>* node, CNode<T>*& max);
    CNode<T>* insert(CNode<T>* node, T val);
    CNode<T>* rotateRight(CNode<T>* node);
    CNode<T>* rotateLeft(CNode<T>* node);
    CNode<T>* balance(CNode<T>* node);
};

template <class T>
CAVLtree<T>::CAVLtree() {
    head = nullptr;
}

template <class T>
CAVLtree<T>::~CAVLtree() {
    destroy(this->head);
}

template <class T>
void CAVLtree<T>::destroy(CNode<T>* node) {
    if (node != nullptr) {
        destroy(node->Left);
        destroy(node->Right);
        delete node;
    }
}

template <class T>
char CAVLtree<T>::getHeight(CNode<T>* node) {
    return node ? node->Height : 0;
}

template <class T>
int CAVLtree<T>::getCount(CNode<T>* node) {
    return node ? node->Count : 0;
}

template <class T>
int CAVLtree<T>::bfactor (CNode<T>* node) {
    return getHeight(node->Right)-getHeight(node->Left);
}

template <class T>
void CAVLtree<T>::fixHeight(CNode<T>* node) {
    char leftH = getHeight(node->Left);
    char rightH = getHeight(node->Right);
    node->Height = (leftH > rightH ? leftH : rightH) + 1;
    node->Count = getCount(node->Left) + getCount(node->Right) + 1;
}

template <class T>
CNode<T>* CAVLtree<T>::rotateRight(CNode<T>* node) {
    CNode<T>* tmp = node->Left;
    node->Left = tmp->Right;
    tmp->Right = node;
    fixHeight(node);
    fixHeight(tmp);

    return tmp;
}

template <class T>
CNode<T>* CAVLtree<T>::rotateLeft(CNode<T>* node) {
    CNode<T>* tmp = node->Right;
    node->Right = tmp->Left;
    tmp->Left = node;
    fixHeight(node);
    fixHeight(tmp);
}

template <class T>
CNode<T>* CAVLtree<T>::balance(CNode<T>* node) {
    fixHeight(node);

    if (bfactor(node) == 2) {
        if (bfactor(node->Right) < 0) {
            node->Right = rotateRight(node->Right);
        }

        return rotateLeft(node);
    }
    if (bfactor(node) == -2) {
        if (bfactor(node->Left) > 0) {
            node->Left = rotateLeft(node->Left);
        }
        
        return rotateRight(node);
    }

    return node;
}

template <class T>
CNode<T>* CAVLtree<T>::insert(CNode<T>* node, T val) {
    if (node == nullptr) {
        return new CNode<T>(val);
    }

    if (node->Data <= val) {
        node->Right = insert(node->Right, val);
    } else {
        node->Left = insert(node->Left, val);
    }

    return balance(node);
}

template <class T>
void CAVLtree<T>::Add(T val) {
    this->head = insert(this->head, val);
}

template <class T>
CNode<T>* CAVLtree<T>::popMax(CNode<T>* node, CNode<T>*& max) {
    if (node->Right == nullptr) {
        max = node;
        return node->Left;
    }
    node->Right = popMax(node->Right, max);

    return balance(node);
}

template <class T>
CNode<T>* CAVLtree<T>::remove(CNode<T>* node, T val) {
    if (node == nullptr) return nullptr;

    if (val > node->Data) {
        node->Right = remove(node->Right, val);
    } else if (val < node->Data) {
        node->Left = remove(node->Left, val);
    } else {
        CNode<T>* right = node->Right;
        CNode<T>* left = node->Left;
        if (right == nullptr) {
            node->Left = nullptr;
            if (left != nullptr) {
                node->Data = left->Data;
                delete left;
                return node;
            } else {
                delete node;
                return nullptr;
            }
        } else if (left == nullptr) {
            node->Right = nullptr;
            node->Data = right->Data;
            delete right;
            return node;
        } else {
            CNode<T>*  max;
            node->Left = popMax(node->Left, max);
            node->Data = max->Data;
            delete max;
            return balance(node);
        }
    }

    return balance(node);
}

template <class T>
void CAVLtree<T>::Delete(T val) {
    this->head = remove(this->head, val);
}

template <class T>
void CAVLtree<T>::show(CNode<T>* node, int lvl) {
    if (node == nullptr) node = this->head;
    //std::cout<<lvl<<" "<<node->Data<<" "<<getCount(node)<<std::endl;
    if (node->Left)
    show(node->Left, lvl+1);
    if (node->Right)
    show(node->Right, lvl+1);
}

template <class T>
CNode<T>* CAVLtree<T>::findByPos(int pos) {
    CNode<T>* curr = this->head;
    while (curr != nullptr) {
        if (pos == getCount(curr->Left)) {
            break;
        } else if (pos < getCount(curr->Left)) {
            curr = curr->Left;
        } else {
            pos -= getCount(curr->Left)+1;
            curr = curr->Right;
        }
    }

    return curr;
}

int main()
{
    int cmdCount;
    CAVLtree<int> tree;

    std::cin>>cmdCount;
    int key, k;

    for (int i = 0; i<cmdCount; ++i) {
        std::cin>>key>>k;
        if (key>0) {
            tree.Add(key);
        } else {
            tree.Delete(-key);
        }
        //tree.show(0, 0);
        std::cout<<tree.findByPos(k)->Data<<std::endl;
    }
    return 0;
}
