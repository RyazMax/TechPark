#include "listgraph.hpp"

CListGraph::CListGraph(const IGraph& other)
    : CListGraph(other.VerticesCount())
{
    for (int i = 0; i < adjacencyList.size(); i++ ) {
        std::vector<int> nextVertices;
        other.GetNextVertices(i, nextVertices);
        std::copy(nextVertices.begin(), nextVertices.end(), 
                    std::back_inserter(adjacencyList[i]));
        std::vector<int> prevVertices;
        other.GetPrevVertices(i, prevVertices);
        std::copy(nextVertices.begin(), nextVertices.end(),
                    std::back_inserter(revAdjList[i]));
    }
}
 
void CListGraph::AddEdge(int from, int to)
{
    assert(isValidIndex(from));
    assert(isValidIndex(to));
 
    adjacencyList[from].push_back(to);
    revAdjList[to].push_back(from);
}
 
void CListGraph::GetNextVertices(int vertex, std::vector<int>& nextVertices) const
{
    assert(isValidIndex(vertex));
 
    std::copy(adjacencyList[vertex].begin(),
        adjacencyList[vertex].end(), std::back_inserter(nextVertices));
}
 
void CListGraph::GetPrevVertices(int vertex, std::vector<int>& prevVertices) const
{
    assert(isValidIndex(vertex));
 
    std::copy(revAdjList[vertex].begin(),
        revAdjList[vertex].end(), std::back_inserter(prevVertices));
}
 
bool CListGraph::isValidIndex(int index) const
{
    return 0 <= index && index < adjacencyList.size();
}
