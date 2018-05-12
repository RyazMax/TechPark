// Рязанов Максим АПО-13
/*
Дано число N < 106 и последовательность пар целых чисел из [-231..231] длиной N.
Построить декартово дерево из N узлов, характеризующихся парами чисел {Xi, Yi}.
Каждая пара чисел {Xi, Yi} определяет ключ Xi и приоритет Yi в декартовом дереве.
Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции:
При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом.
Затем разбейте найденное поддерево по ключу x так, чтобы в первом поддереве все ключи меньше x,
а во втором больше или равны x. Получившиеся два дерева сделайте дочерними для нового узла (x, y). 
Новый узел вставьте на место узла P.

Построить также наивное дерево поиска по ключам Xi методом из задачи 2.

Вычислить количество узлов в самом широком слое декартового дерева и количество узлов в 
самом широком слое наивного дерева поиска. Вывести их разницу. Разница может быть отрицательна.
*/

#include <iostream>
#include <queue>
#include <stack>

template <class T>
struct CNode {
    T Data;
    CNode* Left;
    CNode* Right;

    CNode () : Left(nullptr), Right(nullptr) {}
    CNode(T data) : Data(data), Left(nullptr), Right(nullptr) {}
};

// Подсчет количества узлов в самом широком слое
template <class T>
int BFS(CNode <T>* vert) {
    std::queue<CNode<T>*> nodes;
    std::queue<int> deeps;
    int nodesCount = 0; // Максимальная ширина
    int currCount = 0; // Ширина текущего слоя
    int currLvl = 0; // Текущая глубина

    nodes.push(vert);
    deeps.push(0);

    while (!nodes.empty()) {
        CNode<T>* curr = nodes.front();
        int deep = deeps.front(); // Глубина текущего узла
        nodes.pop();
        deeps.pop();

        if (deep == currLvl) {
            ++currCount;
        } else {
            currLvl = deep;
            currCount = 1;
        }

        nodesCount = nodesCount > currCount ? nodesCount : currCount;

        if (curr->Left) {
            nodes.push(curr->Left);
            deeps.push(deep+1);
        }
        if (curr->Right) {
            deeps.push(deep+1);
            nodes.push(curr->Right);
        }
    }

    return nodesCount;
}

// Обход сверху
template <class T, class Function>
void PreOrder(CNode<T>* vert, Function func) {
    if (vert == nullptr) {
        return;
    }

    std::stack<CNode<T>*> st;
    st.push(vert);

    while (st.size() && st.top() != nullptr) {
        vert = st.top();
        st.pop();
        func(vert);

        if (vert->Right) {
            st.push(vert->Right);
        }
        if (vert->Left) {
            st.push(vert->Left);
        }
    }
}

// Обход снизу
template <class T, class Function>
void PostOrder(CNode<T>* vert, Function func) {
    if (vert == nullptr) {
        return;
    }

    CNode<T>* first = vert;
    enum  { 
        DOWN,
        LEFT,
        RIGHT
    } state = DOWN;

    std::stack <CNode<T>*> st;
    st.push(vert);

    while (st.size() && vert != nullptr) {
        switch (state)
        {
            case DOWN:
                if (vert->Left) {
                    st.push(vert->Left);
                    break;
                } else if (vert->Right) {
                    st.push(vert->Right);
                    break;
                } else {
                    st.pop();
                    if (vert != first) {
                        if (st.top()->Left == vert) {
                            state = LEFT;
                        } else {
                            state = RIGHT;
                        }
                    }
                    func(vert);
                    break;
                }
            case LEFT:
                if (vert->Right) {
                    st.push(vert->Right);
                    state = DOWN;
                    break;
                } else {
                    st.pop();
                    if (vert != first) {
                        if (st.top()->Left == vert) {
                            state = LEFT;
                        } else {
                            state = RIGHT;
                        }
                    }
                    func(vert);
                    break;
                }
            case RIGHT:
                st.pop();
                if (vert != first) {
                    if (st.top()->Left == vert) {
                    state = LEFT;
                    } else {
                        state = RIGHT;
                    }
                }
                func(vert);
                break;
        }

        if (st.size())
            vert = st.top();
    }
}

// Декартово дерево
template <class T>
class CTreap {
public:
    CTreap();
    CTreap(const CTreap &other);
    CTreap(CTreap&& other);
    ~CTreap();

    CTreap& operator = (const CTreap &other);
    CTreap& operator = (CTreap&& other);

    void Add(T val);
    void Delete(T val);
    int MaxWidth();
private:
    void split(CNode<T>* currNode, T val,  CNode<T>*& left, CNode<T>*& right);
    CNode<T>** findWithKey(T val);
    CNode<T>** findLessPrior(T val);
    CNode<T>* merge(CNode<T>* left, CNode<T>* right);
    CNode<T>* head;
};

template <class T>
int CTreap<T>::MaxWidth() {
    return BFS<T>(this->head);
}

template <class T>
CTreap<T>::CTreap() {
    this->head = nullptr;
}

template <class T>
CTreap<T>::CTreap(const CTreap &other) {
    if (other.head == nullptr) {
        this->head = nullptr;
    }
    else {
        std::stack<CNode<T>*> st;
        this->head = new CNode<T>(other.head->Data);
        st.push(this->head);
        PreOrder(other.head, [&st](const CNode<T>* node) {
            CNode<T>* curr = st.top();
            st.pop();
            curr->Data = node->Data;
            if (node->Right) {
                curr->Right = new CNode<T>();
                st.push(curr->Right);
            }
            if (node->Left) {
                curr->Left = new CNode<T>();
                st.push(curr->Left);
            }
        });
    }
}

template <class T>
CTreap<T>::CTreap(CTreap&& other) {
    this->head = other.head;
    other.head = nullptr;
}

template <class T>
CTreap<T>& CTreap<T>::operator=(const CTreap &other) {
    if (this->head != nullptr) {
         PostOrder(this->head, [](CNode<T>* node){delete node;});
    }
    if (other.head == nullptr) {
        this->head = nullptr;
    } else {
        std::stack<CNode<T>*> st;
        this->head = new CNode<T>(other.head->Data);
        st.push(this->head);
        PreOrder(other.head, [&st](const CNode<T>* node) {
            CNode<T>* curr = st.top();
            st.pop();
            curr->Data = node->Data;
            if (node->Right) {
                curr->Right = new CNode<T>();
                st.push(curr->Right);
            }
            if (node->Left) {
                curr->Left = new CNode<T>();
                st.push(curr->Left);
            }
        });
    }

    return *this;
}

template <class T>
CTreap<T>& CTreap<T>::operator=(CTreap&& other) {
    if (this->head != nullptr) {
        PostOrder(this->head, [](CNode<T>* node){delete node;});
    }

    this->head = other.head;
    other.head = nullptr;

    return *this;
}

template <class T>
CTreap<T>::~CTreap() {
    PostOrder(this->head, [](CNode<T>* node) {delete node;});
}

template <class T>
void CTreap<T>::split(CNode<T>* currNode, T val, CNode<T>*& left, CNode<T>*& right) {
    if (currNode == nullptr) {
        left = nullptr;
        right = nullptr;
    } else if (currNode->Data.first <= val.first) {
        split(currNode->Right, val, currNode->Right, right);
        left = currNode;
    } else {
        split(currNode->Left, val, left, currNode->Left);
        right = currNode;
    }
}

template <class T>
CNode<T>* CTreap<T>::merge(CNode<T>* left, CNode<T>* right) {
    if (left == nullptr || right == nullptr) {
        return left == 0 ? right : left;
    }
    if (left->Data.second > right->Data.second) {
        left->Right = merge(left->Right, right);
        return left;
    } else {
        right->Left =merge(left, right->Left);
        return right;
    }
}

// Нахождение элемента с ключом val.first
template <class T>
CNode<T>** CTreap<T>::findWithKey(T val) {
    CNode<T>** curr = &(this->head);

    while (*curr != nullptr && (*curr)->Data.first != val.first) {
        if (val.first > (*curr)->Data.first) {
            curr = &((*curr)->Right);
        } else {
            curr = &((*curr)->Left);
        }
    }

    return curr;
}

// Нахождение элемента с меньшим приоритетом val.second
template <class T>
CNode<T>** CTreap<T>::findLessPrior(T val) {
    CNode<T>** curr = &(this->head);

    while (*curr != nullptr && (*curr)->Data.second >= val.second) {
        if (val.first > (*curr)->Data.first) {
            curr = &((*curr)->Right);
        } else {
            curr = &((*curr)->Left);
        }
    }

    return curr;
}

template <class T>
void CTreap<T>::Add(T val) {
    CNode<T>** toAdd = findLessPrior(val);
    CNode<T>* left, *right;

    split(*toAdd, val, left, right);
    (*toAdd) = new CNode<T>(val);
    (*toAdd)->Right = right;
    (*toAdd)->Left = left;
}

template <class T>
void CTreap<T>::Delete(T val) {
    CNode<T>** toDel = findWithKey(val);
    CNode<T>* merged = merge((*toDel)->Left, (*toDel)->Right);
    if (*toDel) {
       delete *toDel;
    }

    *toDel = merged;
}

// Бинарное дерево
template <class T>
class CBinTree {
public:
    CBinTree();
    CBinTree(CBinTree &other);
    CBinTree(CBinTree&& other);
    ~CBinTree();

    CBinTree& operator = (CBinTree &other);
    CBinTree& operator = (CBinTree&& other);

    void Add(T value);
    void Delete(T value);
    CNode<T>** findWithKey(T val);
    int MaxWidth();
private:
    CNode<T> *head;

};

template <class T>
int CBinTree<T>::MaxWidth() {
    return BFS<T>(this->head);
}

template <class T>
CBinTree<T>::CBinTree() {
    this->head = nullptr;
}

template <class T>
CBinTree<T>::CBinTree(CBinTree &other) {
    if (other.head == nullptr) {
        this->head = nullptr;
    }
    else {
        std::stack<CNode<T>*> st;
        this->head = new CNode<T>(other.head->Data);
        st.push(this->head);
        PreOrder(other.head, [&st](CNode<T>* node) {
            CNode<T>* curr = st.top();
            st.pop();
            curr->Data = node->Data;
            if (node->Right) {
                curr->Right = new CNode<T>(0);
                st.push(curr->Right);
            }
            if (node->Left) {
                curr->Left = new CNode<T>(0);
                st.push(curr->Left);
            }
        });
    }
}

template <class T>
CBinTree<T>::CBinTree(CBinTree&& other) {
    this->head = other.head;
    other.head = nullptr;
}

template <class T>
CBinTree<T>& CBinTree<T>::operator=(CBinTree &other) {
    if (this->head != nullptr) {
         PostOrder(this->head, [](CNode<T>* node){delete node;});
    }
    if (other.head == nullptr) {
        this->head = nullptr;
    }
    else {
        std::stack<CNode<T>*> st;
        this->head = new CNode<T>(other.head->Data);
        st.push(this->head);
        PreOrder(other.head, [&st](CNode<T>* node) {
            CNode<T>* curr = st.top();
            st.pop();
            curr->Data = node->Data;
            if (node->Right) {
                curr->Right = new CNode<T>(0);
                st.push(curr->Right);
            }
            if (node->Left) {
                curr->Left = new CNode<T>(0);
                st.push(curr->Left);
            }
        });
    }

    return *this;
}


template <class T>
CBinTree<T>& CBinTree<T>::operator=(CBinTree&& other) {
    if (this->head != nullptr) {
        PostOrder(this->head, [](CNode<T>* node){delete node;});
    }

    this->head = other.head;
    other.head = nullptr;

    return *this;
}


template <class T>
CBinTree<T>::~CBinTree() {
    PostOrder(this->head, [](CNode<T>* node){delete node;});
}

template <class T>
CNode<T>** CBinTree<T>::findWithKey(T val) {
    CNode<T>** curr = &(this->head);

    while (*curr != nullptr && (*curr)->Data != val) {
        if (val > (*curr)->Data) {
            curr = &((*curr)->Right);
        } else {
            curr = &((*curr)->Left);
        }
    }

    return curr;
}

template <class T>
void CBinTree<T>::Delete(T val) {
    CNode<T>** toDel = findWithKey(val);
    if (*toDel == nullptr) {
        return;
    }

    CNode<T>* left = (*toDel)->Left, *right = (*toDel)->Right;
    if (left == nullptr) {
        delete *toDel;
        *toDel = right;
    } else if (right == nullptr) {
        delete *toDel;
        *toDel = left;
    } else {
        CNode<T>** sideDel = &((*toDel)->Right);
        while ((*sideDel)->Left != nullptr) {
            sideDel = &((*sideDel)->Left);
        }
        (*toDel)->Data = (*sideDel)->Data;
        right = (*sideDel)->Right;
        delete *sideDel;
        *sideDel = right;
    }
}

template <class T>
void CBinTree<T>::Add(T value) {
    
    CNode<T>* curr = this->head;

    if (curr == nullptr) {
        this->head = new CNode<T>(CNode<T>(value));
        return ;
    }

    while (true) {
        if (value > curr->Data) {
            if (curr->Right == nullptr) {
                curr->Right = new CNode<T>(CNode<T>(value));
                break;
            } else {
                curr = curr->Right;
            }
        } else {
            if (curr->Left == nullptr) {
                curr->Left = new CNode<T>(CNode<T>(value));
                break;
            } else {
                curr = curr->Left;
            }
        }
    }
}


int main()
{
    int cmdCount = 0;
    int key, prior;
    CTreap<std::pair<int,int>> treap;
    CBinTree<int> tree;

    std::cin>>cmdCount;

    for (int i=0; i<cmdCount; ++i) {
        std::cin>>key>>prior;
        treap.Add(std::make_pair(key, prior));
        tree.Add(key);
    }
    
    std::cout<<treap.MaxWidth()-tree.MaxWidth();
    return 0;
}


