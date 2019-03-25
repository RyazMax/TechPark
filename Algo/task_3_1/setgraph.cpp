#include "setgraph.hpp"


CSetGraph::CSetGraph(const IGraph& other) :
    CSetGraph(other.VerticesCount()) {
    
    for (int i = 0; i < hashTableList.size(); ++i) {
        std::vector<int> nextVertices;
        other.GetNextVertices(i, nextVertices);
        for(int j : nextVertices) {
            hashTableList[i].insert(j);
        }

        std::vector<int> prevVertices;
        other.GetPrevVertices(i, prevVertices);
        for(int j : prevVertices) {
            revHashTableList[i].insert(j);
        }
    }
}

void CSetGraph::AddEdge(int from, int to) {
    assert(isValidIndex(from));
    assert(isValidIndex(to));

    hashTableList[from].insert(to);
    revHashTableList[to].insert(from);
}

void CSetGraph::GetNextVertices(int vertex, std::vector<int>& nextVertices) const {
    assert(isValidIndex(vertex));

    std::copy(hashTableList[vertex].begin(), hashTableList[vertex].end(),
                std::back_inserter(nextVertices));
}

void CSetGraph::GetPrevVertices(int vertex, std::vector<int>& prevVertices) const {
    assert(isValidIndex(vertex));

    std::copy(revHashTableList[vertex].begin(), revHashTableList[vertex].end(),
                std::back_inserter(prevVertices));
}

bool CSetGraph::isValidIndex(int index) const {
    return index >= 0 && index < hashTableList.size();
}