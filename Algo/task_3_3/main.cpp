#include <iostream>
#include <list>
#include <vector>
#include <cassert>
#include <set>

const int INF = 2000000000;

struct IGraph {
    virtual ~IGraph() {}
    
    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to, int len) = 0;

    virtual int VerticesCount() const  = 0;

    virtual void GetNextVertices(int vertex, std::vector<std::pair<int, int>>& verticies) const = 0;
    virtual void GetPrevVertices(int vertex, std::vector<std::pair<int, int>>& verticies) const = 0;
};

class CListGraph : public IGraph {
public:
    CListGraph(int n) : adjacencyList(n) {}
    CListGraph(const IGraph& other);
 
    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to, int len) override;
 
    virtual int VerticesCount() const override { return adjacencyList.size(); }
 
    virtual void GetNextVertices(int vertex, std::vector<std::pair<int,int>>& nextVertices) const override;
    virtual void GetPrevVertices(int vertex, std::vector<std::pair<int, int>>& prevVertices) const override;
 
private:
    std::vector<std::list<std::pair<int, int>>> adjacencyList;
 
    bool isValidIndex(int index) const;
};

CListGraph::CListGraph(const IGraph& other)
    : CListGraph(other.VerticesCount())
{
    for (int i = 0; i < adjacencyList.size(); i++ ) {
        std::vector<std::pair<int, int>> nextVertices;
        other.GetNextVertices(i, nextVertices);
        std::copy(nextVertices.begin(), nextVertices.end(), 
                    std::back_inserter(adjacencyList[i]));
    }
}
 
void CListGraph::AddEdge(int from, int to, int len)
{
    assert(isValidIndex(from));
    assert(isValidIndex(to));
 
    adjacencyList[from].push_back(std::pair<int, int>(to, len));
    adjacencyList[to].push_back(std::pair<int, int>(from, len));
}
 
void CListGraph::GetNextVertices(int vertex, std::vector<std::pair<int, int>>& nextVertices) const
{
    assert(isValidIndex(vertex));
 
    std::copy(adjacencyList[vertex].begin(),
        adjacencyList[vertex].end(), std::back_inserter(nextVertices));
}
 
void CListGraph::GetPrevVertices(int vertex, std::vector<std::pair<int, int>>& prevVertices) const
{
    GetNextVertices(vertex, prevVertices);
}
 
bool CListGraph::isValidIndex(int index) const
{
    return 0 <= index && index < adjacencyList.size();
}

int findDist(const IGraph& graph, int start, int end) {
    std::vector<int> dist(graph.VerticesCount(), INF);
    std::set<std::pair<int, int>> q;

    dist[start] = 0;
    q.insert(std::make_pair(dist[start], start));

    while (!q.empty()) {
        int u = q.begin()->second;
        q.erase(q.begin());

        std::vector<std::pair<int, int>> next;
        graph.GetNextVertices(u, next);
        for (std::pair<int, int> v : next) {
            int to = v.first, len = v.second;

            if (dist[u] + len < dist[to]) {
                q.erase(std::make_pair(dist[to], to));
                dist[to] = dist[u] + len;
                q.insert(std::make_pair(dist[to], to));
            }
        }
    }

    return dist[end] != INF ? dist[end] : -1;
}

int main()
{
    int vertCount = 0, edgeCount = 0;
    std::cin>>vertCount>>edgeCount;
    CListGraph graph(vertCount);

    int u, v, len;
    for (int i = 0; i<edgeCount; ++i) {
        std::cin>>u>>v>>len;
        graph.AddEdge(u, v, len);
    }

    std::cin>>u>>v;
    int ans = findDist(graph, u, v);
    std::cout<<ans;
    return 0;
}