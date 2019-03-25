#ifndef __SETGRAPH_H__
#define __SETGRAPH_H__

#include <unordered_set>

#include "igraph.hpp"

class CSetGraph : public IGraph {
public:
    CSetGraph(int n) : hashTableList(n), revHashTableList(n) {}
    CSetGraph(const IGraph& other);
 
    virtual void AddEdge(int from, int to) override;
 
    virtual int VerticesCount() const override { return hashTableList.size(); }
 
    virtual void GetNextVertices(int vertex, std::vector<int>& nextVertices) const override;
    virtual void GetPrevVertices(int vertex, std::vector<int>& prevVertices) const override;
 
private:
    std::vector<std::unordered_set<int>> hashTableList;
    std::vector<std::unordered_set<int>> revHashTableList;
 
    bool isValidIndex(int index) const;
};

#endif