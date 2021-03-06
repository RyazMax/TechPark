// Рязанов Максим АПО-13
/*
Необходимо написать несколько реализаций интерфейса:
CListGraph, хранящий граф в виде массива списков смежности,
CMatrixGraph, хранящий граф в виде матрицы смежности,
CSetGraph, хранящий граф в виде массива хэш-таблиц,
CArcGraph, хранящий граф в виде одного массива пар {from, to}.
Также необходимо реализовать конструктор, принимающий const IGraph*. 
Такой конструктор должен скопировать переданный граф в создаваемый объект.
Для каждого класса создавайте отдельные h и cpp файлы.
Число вершин графа задается в конструкторе каждой реализации.
*/

#include <iostream>

#include "matrixgraph.hpp"
#include "listgraph.hpp"
#include "setgraph.hpp"
#include "arcgraph.hpp"

int main()
{
    return 0;
}