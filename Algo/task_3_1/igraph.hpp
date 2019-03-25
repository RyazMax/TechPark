#ifndef __IGRAPH_H__
#define __IGRAPH_H__

#include <vector>
#include <cassert>

struct IGraph {
    virtual ~IGraph() {}
    
    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual void GetNextVertices(int vertex, std::vector<int>& verticies) const = 0;
    virtual void GetPrevVertices(int vertex, std::vector<int>& verticies) const = 0;
};

#endif