#include <iostream>

struct Point {
    int X;
    int Y;
    Point() : X(0), Y(0) {}
};

bool IsLessX(const Point& l, const Point& r) {
    return l.X <r.X;
}

template<class T>
bool IsLessDefault(const T& l, const T& r) {
    return l < r;
}

class IsLessPoint {
public:
    bool operator()(const Point& l, const Point& r) { return l.X < r.X; }
};

template<class T, class Compare>
void mySort(T* arr, int l, int r, Compare cmp)
{
    for (int i = l; i < r; i++) {
        for (int j = l; j < r; j++) {
            if (cmp(arr[j + 1], arr[j])) {
                std::swap(arr[i], arr[j]);
            }
    }
    }
}

int main()
{
    int n = 0;
    std::cin >> n;
    Point* arr = new Point [n];
    for (int i = 0; i<n; ++i) {
        std::cin >> arr[i].X >> arr[i].Y;
    }
    mySort(arr, 0, n, IsLessPoint());
    for (int i = 0; i<n; ++i) {
        std::cout << arr[i].X << arr[i].Y<<std::endl;
    }
    return 0;
}