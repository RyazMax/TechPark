#ifndef __LISTGRAPH_H__
#define __LISTGRAPH_H__

#include <list>

#include "igraph.hpp"

class CListGraph : public IGraph {
public:
    CListGraph(int n) : adjacencyList(n), revAdjList(n) {}
    CListGraph(const IGraph& other);
 
    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) override;
 
    virtual int VerticesCount() const override { return adjacencyList.size(); }
 
    virtual void GetNextVertices(int vertex, std::vector<int>& nextVertices) const override;
    virtual void GetPrevVertices(int vertex, std::vector<int>& prevVertices) const override;
 
private:
    std::vector<std::list<int>> adjacencyList;
    std::vector<std::list<int>> revAdjList;
 
    bool isValidIndex(int index) const;
};

#endif