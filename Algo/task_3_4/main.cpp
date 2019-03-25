#include <iostream>
#include <array>
#include <list>
#include <vector>
#include <cassert>
#include <math.h>
#include <algorithm>

typedef unsigned long long ull_t;

const int INF = 2000000000;
const ull_t mask = 0x000000000000000F;

class State {
public:
    State( const std::array<int, 16>& state );
   
    int operator[](int i) const;
 
    bool CanMoveLeft() const;
    bool CanMoveRight() const;
    bool CanMoveUp() const;
    bool CanMoveDown() const;
 
    State MoveLeft() const;
    State MoveRight() const;
    State MoveUp() const;
    State MoveDown() const;

    int GetH() const;
    bool isGoal() const;
    bool canSolve() const;
 
private:
    ull_t body;
    
    inline int getNullPosition() const;

    void setValue(int pos, int value);
    void swap(int i, int j);
 
    static const int size = 4;
};
 
State::State(const std::array<int, 16>& state)
{
    for (int i = 0; i < state.size(); i++) {
        setValue(i, state[i]);
    }
}

int State::GetH() const
{
    int sum = 0;
    for (int i = 0; i<size*size; ++i)
    {
        int curr = (*this)[i] - 1;
        if (curr == -1) continue;
        sum += abs(curr%size - i%size);
        sum += abs(curr/size - i/size); 
    }
    
    return sum;
}

bool State::isGoal() const
{
    return !GetH();
}
 
int State::getNullPosition() const
{
    for (int i = 0; i<size*size; ++i) {
        if ((*this)[i] == 0) return i;
    }
}
 
int State::operator[](int i) const
{
    ull_t value = body & (mask << i * size);
    value >>= i * size;
 
    return value;
}
 
void State::setValue(int pos, int value)
{
    ull_t v = value;

    body &= ~(mask << pos * size);
    body |= (v << pos * size);
}
 
void State::swap(int i, int j)
{
    const int iValue = (*this)[i];
    setValue(i, (*this)[j]);
    setValue(j, iValue);
}
 
bool State::CanMoveLeft() const
{
    return (getNullPosition() % size) != size - 1;
}
 
bool State::CanMoveRight() const
{
    return (getNullPosition() % size) != 0;
}
 
bool State::CanMoveUp() const
{
    return getNullPosition() < (size - 1) * size;
}
 
bool State::CanMoveDown() const
{
    return getNullPosition() >= size;
}
 
State State::MoveLeft() const
{
    assert(CanMoveLeft());
 
    State newState = *this;
    //newState.setValue(getNullPosition() - 1, 0);
    newState.swap(newState.getNullPosition() + 1, getNullPosition());
 
    return newState;
}
 
State State::MoveRight() const
{
    assert(CanMoveRight());
 
    State newState = *this;
    int nullPos = getNullPosition();
    newState.swap(nullPos - 1, nullPos);
 
    return newState;
}
 
State State::MoveUp() const
{
    assert(CanMoveUp());
 
    State newState = *this;
   // newState.setValue(getNullPosition() - size, 0);
    newState.swap(newState.getNullPosition() + size, getNullPosition());
 
    return newState;
}
 
State State::MoveDown() const
{
    assert(CanMoveDown());
 
    State newState = *this;
    //newState.setValue(getNullPosition() + size, 0);
    newState.swap(newState.getNullPosition() - size, getNullPosition());
 
    return newState;
}

std::ostream& operator << (std::ostream& out, const State& s)
{
    return out << s[0] << s[1] << s[2] << s[3] << s[4]
        << s[5] << s[6] << s[7] << s[8]
        << s[9] << s[10] << s[11] << s[12]
        << s[13] << s[14] << s[15] << std::endl;
}

void printState(const State& s)
{
    for (int i = 0; i<4; ++i) 
    {
        for (int j = 0; j<4; ++j)
        {
            std::cout<<s[i*4+j]<<" ";
        }
        std::cout<<"\n";
    }
}

int cnt = 0;
int search(State state, int dist, int bound, char lastMove, std::vector<char> &path)
{
    //std::cout<<cnt++<<" ";
    std::queue<State> open;
    std::queue<State> close;
    int f = dist + state.GetH();
    if (f > bound) return f;
    if (state.isGoal()) {
        path.push_back(lastMove);
        return -1;
    }
    
    int min = INF;
    int t = 0;
    if (state.CanMoveDown() && lastMove != 'U')
    {
        t = search(state.MoveDown(), dist + 1, bound, 'D', path);
        if (t == -1)
        {
            //std::cout<<lastMove;
            path.push_back(lastMove);
            return -1;
        }
        if (t < min) min = t;
    }
    if (state.CanMoveUp() && lastMove != 'D')
    {
        t = search(state.MoveUp(), dist + 1, bound, 'U', path);
        if (t == -1)
        {
            //std::cout<<lastMove;
            path.push_back(lastMove);
            return -1;
        }
        if (t < min) min = t;
    }
    if (state.CanMoveLeft() && lastMove != 'R')
    {
        t = search(state.MoveLeft(), dist + 1, bound, 'L', path);
        if (t == -1)
        {
            //std::cout<<lastMove;
            path.push_back(lastMove);
            return -1;
        }
        if (t < min) min = t;
    }
    if (state.CanMoveRight() && lastMove != 'L')
    {
        t = search(state.MoveRight(), dist + 1, bound, 'R', path);
        if (t == -1)
        {
            //std::cout<<lastMove;
            path.push_back(lastMove);
            return -1;
        }
        if (t < min) min = t;
    }

    return min;
}

bool State::canSolve() const
{
    int inv = 0;
    for (int i=0; i<16; ++i)
		for (int j=0; j<i; ++j)
			if ((*this)[i]!= 0 && (*this)[j] > (*this)[i])
				++inv;
    return !(inv & 1);
}

int idaStar(State root, std::vector<char> &path)
{
    //std::cout<<"start";
    int bound = root.GetH();
    int t = 0;
    //std::cout<<"Start";
    //if (!root.canSolve())
    //{
        //std::cout<<"OK";
      //  return 0;
    //}
    while (t != -1 && bound < 50 && t != INF)
    {
        //std::cout<<bound<<"\n";
        t = search(root, 0, bound, 'o', path);
        bound = std::max(bound+6, t);
        
    }
    return t;
}

int main()
{
    std::array<int, 16> arr;
    for (int i = 0; i<16; ++i)
    {
        std::cin>>arr[i];
    }
    State state(arr);
    /*state = state.MoveDown();
    state = state.MoveDown();
    state = state.MoveRight();
    state = state.MoveUp();
    state = state.MoveLeft();
    printState(state);*/

    std::vector<char> path;
    int ans = idaStar(state, path);
    //std::cout<<"ANS: "<<ans;
    if (ans == INF) 
    {
        std::cout<<-1;
    }
    else
    {
        std::cout<<path.size() - 1<<"\n";
        for (int i = path.size()-2; i>=0; --i)
        {
            std::cout<<path[i];
        }
    }
    return 0;
}