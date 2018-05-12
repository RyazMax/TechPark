// Рязанов Максим АПО-13
/*
Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Рекурсия запрещена.
Вывести снизу вверх
*/

#include <iostream>
#include <stack>

template <class T>
class CBinTree {
public:
    CBinTree();
    CBinTree(CBinTree &other);
    CBinTree(CBinTree&& other);
    ~CBinTree();

    CBinTree& operator = (CBinTree &other);
    CBinTree& operator = (CBinTree&& other);

    struct CNode;

    void AddNew(T value);
    void Delete(T value);

    template <class Function>
    void PostOrder(CNode* vert, Function func);
    template <class Function>
    void PreOrder(CNode* vert, Function func); 
private:
    CNode *head;

};

template <class T>
struct CBinTree<T>::CNode {
    T Data;
    CNode* Left;
    CNode* Right;

    CNode(T data) : Data(data), Left(nullptr), Right(nullptr) {}
};

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
        std::stack<CNode*> st;
        this->head = new CNode(other.head->Data);
        st.push(this->head);
        other.PreOrder(0, [&st](CNode* node) {
            CNode* curr = st.top();
            st.pop();
            curr->Data = node->Data;
            if (node->Right) {
                curr->Right = new CNode(0);
                st.push(curr->Right);
            }
            if (node->Left) {
                curr->Left = new CNode(0);
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
         this->PostOrder(0, [](CNode* node){delete node;});
    }
    if (other.head == nullptr) {
        this->head = nullptr;
    }
    else {
        std::stack<CNode*> st;
        this->head = new CNode(other.head->Data);
        st.push(this->head);
        other.PreOrder(0, [&st](CNode* node) {
            CNode* curr = st.top();
            st.pop();
            curr->Data = node->Data;
            if (node->Right) {
                curr->Right = new CNode(0);
                st.push(curr->Right);
            }
            if (node->Left) {
                curr->Left = new CNode(0);
                st.push(curr->Left);
            }
        });
    }

    return *this;
}


template <class T>
CBinTree<T>& CBinTree<T>::operator=(CBinTree&& other) {
    if (this->head != nullptr) {
        this->PostOrder(0, [](CNode* node){delete node;});
    }

    this->head = other.head;
    other.head = nullptr;

    return *this;
}


template <class T>
CBinTree<T>::~CBinTree() {
    this->PostOrder(0, [](CNode* node){delete node;});
}

template <class T>
void CBinTree<T>::AddNew(T value) {
    
    CNode* curr = this->head;

    if (curr == nullptr) {
        this->head = new CNode(CNode(value));
        return ;
    }

    while (true) {
        if (value > curr->Data) {
            if (curr->Right == nullptr) {
                curr->Right = new CNode(CNode(value));
                break;
            } else {
                curr = curr->Right;
            }
        } else {
            if (curr->Left == nullptr) {
                curr->Left = new CNode(CNode(value));
                break;
            } else {
                curr = curr->Left;
            }
        }
    }
}

template <class T>
void CBinTree<T>::Delete(T val) {
    CNode** toDel = &(this->head);

    while (*toDel != nullptr && (*toDel)->Data != val) {
        if (val > (*toDel)->Data) {
            toDel = &((*toDel)->Right);
        } else {
            toDel = &((*toDel)->Left);
        }
    }
    if (*toDel == nullptr) {
        return;
    }

    CNode* left = (*toDel)->Left, *right = (*toDel)->Right;
    if (left == nullptr) {
        delete *toDel;
        *toDel = right;
    } else if (right == nullptr) {
        delete *toDel;
        *toDel = left;
    } else {
        CNode** sideDel = &((*toDel)->Right);
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
template <class Function>
void CBinTree<T>::PreOrder(CNode* vert, Function func) {
    if (vert == nullptr) {
        vert = this->head;
    }

    std::stack<CNode*> st;
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

template <class T>
template <class Function>
void CBinTree<T>::PostOrder(CNode* vert, Function func) {
    if (vert == nullptr) {
        vert =this->head;
    }

    CNode* first = vert;
    enum  { 
        DOWN,
        LEFT,
        RIGHT
    } state = DOWN;

    std::stack <CNode*> st;
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


int main()
{
    int numCount = 0; // Количество чисел
    int curr = 0; // Текущее число
    
    std::cin >> numCount;

    CBinTree<int> tree;

    for (int i = 0; i < numCount; ++i) {
        std::cin >> curr;
        tree.AddNew(curr);
    }

    tree.PostOrder(0, [](CBinTree<int>::CNode* node){std::cout<<node->Data<<" ";});
    return 0;
}
