#ifndef __ARCGRAPH_H__
#define __ARCGRAPH_H__

#include "igraph.hpp"

class CArcGraph : public IGraph {
public:
    CArcGraph(int n) : vertCount(n) {}
    CArcGraph(const IGraph& other);
 
    virtual void AddEdge(int from, int to) override;
 
    virtual int VerticesCount() const override { return vertCount; }
 
    virtual void GetNextVertices(int vertex, std::vector<int>& nextVertices) const override;
    virtual void GetPrevVertices(int vertex, std::vector<int>& prevVertices) const override;
 
private:
    std::vector<std::pair<int, int>> arcList;
    
    int vertCount;
    bool isValidIndex(int index) const;
};

#endif