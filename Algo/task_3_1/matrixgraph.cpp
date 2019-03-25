#include "matrixgraph.hpp"

CMatrixGraph::CMatrixGraph(const IGraph &other)
    : CMatrixGraph(other.VerticesCount()) {
    
    for (int i = 0; i < adjMatrix.size(); ++i) {
        std::vector<int> nextVertices;
        other.GetNextVertices(i, nextVertices);
        for (int j : nextVertices) {
            adjMatrix[i][j] = true;
        }
        std::vector<int> prevVertices;
        other.GetPrevVertices(i, prevVertices);
        for (int j : nextVertices) {
            adjMatrix[j][i] = true;
        }
    }
}

void CMatrixGraph::AddEdge(int from, int to) {
    assert(isValidIndex(from));
    assert(isValidIndex(to));

    adjMatrix[from][to] = true;
}

void CMatrixGraph::GetNextVertices(int vertex, std::vector<int>& nextVertices) const {
    assert(isValidIndex(vertex));

    for (int i = 0; i < adjMatrix.size(); ++i) {
        if (adjMatrix[vertex][i]) {
            nextVertices.push_back(i);
        }
    }
}

void CMatrixGraph::GetPrevVertices(int vertex, std::vector<int>& prevVertices) const {
    assert(isValidIndex(vertex));

    for (int i = 0; i < adjMatrix.size(); ++i) {
        if (adjMatrix[i][vertex]) {
            prevVertices.push_back(i);
        }
    }

}

bool CMatrixGraph::isValidIndex(int index) const {
    return index >= 0 && index < adjMatrix.size();
}