#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <cassert>

struct IGraph {
    virtual ~IGraph() {}
    
    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual void GetNextVertices(int vertex, std::vector<int>& verticies) const = 0;
    virtual void GetPrevVertices(int vertex, std::vector<int>& verticies) const = 0;
};

class CListGraph : public IGraph {
public:
    CListGraph(int n) : adjacencyList(n) {}
    CListGraph(const IGraph& other);
 
    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) override;
 
    virtual int VerticesCount() const override { return adjacencyList.size(); }
 
    virtual void GetNextVertices(int vertex, std::vector<int>& nextVertices) const override;
    virtual void GetPrevVertices(int vertex, std::vector<int>& prevVertices) const override;
 
private:
    std::vector<std::list<int>> adjacencyList;
 
    bool isValidIndex(int index) const;
};

CListGraph::CListGraph(const IGraph& other)
    : CListGraph(other.VerticesCount())
{
    for (int i = 0; i < adjacencyList.size(); i++ ) {
        std::vector<int> nextVertices;
        other.GetNextVertices(i, nextVertices);
        std::copy(nextVertices.begin(), nextVertices.end(), 
                    std::back_inserter(adjacencyList[i]));
    }
}
 
void CListGraph::AddEdge(int from, int to)
{
    assert(isValidIndex(from));
    assert(isValidIndex(to));
 
    adjacencyList[from].push_back(to);
    adjacencyList[to].push_back(from);
}
 
void CListGraph::GetNextVertices(int vertex, std::vector<int>& nextVertices) const
{
    assert(isValidIndex(vertex));
 
    std::copy(adjacencyList[vertex].begin(),
        adjacencyList[vertex].end(), std::back_inserter(nextVertices));
}
 
void CListGraph::GetPrevVertices(int vertex, std::vector<int>& prevVertices) const
{
    GetNextVertices(vertex, prevVertices);
}
 
bool CListGraph::isValidIndex(int index) const
{
    return 0 <= index && index < adjacencyList.size();
}

int solve(const IGraph& graph, int start, int end) {
    std::queue<int> q;
    std::vector<bool> used(graph.VerticesCount(), false);
    std::vector<int> dist(graph.VerticesCount(), graph.VerticesCount()+1);
    std::vector<int> minCount(graph.VerticesCount(), 0);

    q.push(start);
    used[start] = true;
    dist[start] = 0;
    minCount[start] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        std::vector<int> next;
        graph.GetNextVertices(u, next);
        for (int v : next) {

            if (dist[u] + 1 < dist[v]) {
                    dist[v] = dist[u] + 1;
                    minCount[v] = minCount[u];
                } else if (dist[u] + 1 == dist[v]) {
                    minCount[v] += minCount[u];
                }

            if (!used[v]) {
                q.push(v);
                used[v] = true;
            }
        }
    }

    return minCount[end];
}

int main()
{
    int vertCount = 0, edgeCount = 0;
    std::cin>>vertCount>>edgeCount;
    CListGraph graph(vertCount);

    int u, v;
    for (int i = 0; i<edgeCount; ++i) {
        std::cin>>u>>v;
        graph.AddEdge(u, v);
    }

    std::cin>>u>>v;
    int ans = solve(graph, u, v);
    std::cout<<ans;
    return 0;
}