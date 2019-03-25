#ifndef __MATRIXGRAPH_H__
#define __MATRIXGRAPH_H__

#include "igraph.hpp"

class CMatrixGraph : public IGraph {
public:
    CMatrixGraph(int n) : adjMatrix(n, std::vector<bool>(n, false)) {}
    CMatrixGraph(const IGraph& other);
 
    virtual void AddEdge(int from, int to) override;
 
    virtual int VerticesCount() const override { return adjMatrix.size(); }
 
    virtual void GetNextVertices(int vertex, std::vector<int>& nextVerticse) const override;
    virtual void GetPrevVertices(int vertex, std::vector<int>& prevVertices) const override;
 
private:
    std::vector<std::vector<bool>> adjMatrix;
 
    bool isValidIndex(int index) const;
};

#endif