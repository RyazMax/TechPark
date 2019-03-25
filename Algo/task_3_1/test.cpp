#include <iostream>
#include <ctime>

#include "matrixgraph.hpp"
#include "listgraph.hpp"
#include "setgraph.hpp"
#include "arcgraph.hpp"

void testMatrixGraph (int count) {
    CMatrixGraph graph(count);
    std::cout<<"Testing Matrix graph\n";

    double sot = clock();
    for (int i = 0; i<count; ++i) {
        for (int j = 0; j<count; ++j) {
            if (i != j) {
                graph.AddEdge(i, j);
            }
        }
    }
    double eot = clock();
    std::cout<<"TIME: "<<(eot-sot)/1000000<<"\n";
}

void testListGraph (int count) {
    CListGraph graph(count);
    std::cout<<"Testing List graph\n";

    double sot = clock();
    for (int i = 0; i<count; ++i) {
        for (int j = 0; j<count; ++j) {
            if (i != j) {
                graph.AddEdge(i, j);
            }
        }
    }
    double eot = clock();
    std::cout<<"TIME: "<<(eot-sot)/1000000<<"\n";
}

void testArcGraph (int count) {
    CArcGraph graph(count);
    std::cout<<"Testing Arc graph\n";

    double sot = clock();
    for (int i = 0; i<count; ++i) {
        for (int j = 0; j<count; ++j) {
            if (i != j) {
                graph.AddEdge(i, j);
            }
        }
    }
    double eot = clock();
    std::cout<<"TIME: "<<(eot-sot)/1000000<<"\n";
}

void testSetGraph (int count) {
    CSetGraph graph(count);
    std::cout<<"Testing Set graph\n";

    double sot = clock();
    for (int i = 0; i<count; ++i) {
        for (int j = 0; j<count; ++j) {
            if (i != j) {
                graph.AddEdge(i, j);
            }
        }
    }
    double eot = clock();
    std::cout<<"TIME: "<<(eot-sot)/1000000<<"\n";
}

int main()
{
    int count = 4000;
    testMatrixGraph(count);
    testListGraph(count);
    testArcGraph(count);
    testSetGraph(count);
    return 0;
}