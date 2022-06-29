#include <iostream>
#include <vector>
#include "Graph.h"

#ifndef PEERGRADEGRAPHS__WORKWITHGRAPHS_H_
#define PEERGRADEGRAPHS__WORKWITHGRAPHS_H_

// Подсчет степеней вершин графа
void CountDegreeOfVertices(const Graph& graph);
// Подсчет степеней для неориентрованного графа
void DegreeOfVertices(const Graph& graph);
// Подсчет степеней для ориентированного графа
void InOutDegreeOfVertices(const Graph& graph);
// Подсчет ребер / дуг графа
void CountEdges(const Graph& graph);
// Вывод графа в разных представлениях
void OutGraph(const Graph& graph);

#endif //PEERGRADEGRAPHS__WORKWITHGRAPHS_H_
