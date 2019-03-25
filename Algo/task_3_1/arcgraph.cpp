#include "arcgraph.hpp"

CArcGraph::CArcGraph(const IGraph &other) :
            CArcGraph(other.VerticesCount()) {
    
    for (int i = 0; i<vertCount; ++i) {
        std::vector<int> nextVertices;
        other.GetNextVertices(i, nextVertices);
        for (int j : nextVertices) {
            arcList.push_back(std::pair<int, int>(i, j));
        }
    }
}

void CArcGraph::AddEdge(int from, int to) {
    assert(isValidIndex(from));
    assert(isValidIndex(to));

    arcList.push_back(std::pair<int, int>(from, to));
}

void CArcGraph::GetNextVertices(int vertex, std::vector<int>& nextVertices) const {
    assert(isValidIndex(vertex));

    for (std::pair<int, int> p : arcList) {
        if (p.first == vertex) {
            nextVertices.push_back(p.second);
        }
    }
}

void CArcGraph::GetPrevVertices(int vertex, std::vector<int>& prevVertices) const {
    assert(isValidIndex(vertex));

    for (std::pair<int, int> p : arcList) {
        if (p.second == vertex) {
            prevVertices.push_back(p.first);
        }
    }
}

bool CArcGraph::isValidIndex(int index) const {
    return index >= 0 && index < vertCount;
}
