#include <iostream>
#include "TransformGraphs.h"

#ifndef PEERGRADEGRAPHS__GRAPH_H_
#define PEERGRADEGRAPHS__GRAPH_H_

class Graph {
  // Данные о графе
  // Представление графа в матрице инцидентности
  // Решил хранить граф только в одном виде и выводить при необходимости в других видах
  std::vector<std::vector<int>> incidenceMatrix;

 public :
  // Конструктор
  Graph() {
   incidenceMatrix = std::vector<std::vector<int>>();
 }

  // Получение графа в виде матрицы смежности
  [[nodiscard]] std::vector<std::vector<int>> GetAdjacencyMatrix() const;

  // Получение графа в виде матрицы инцидентности
  [[nodiscard]] std::vector<std::vector<int>> GetIncidenceMatrix() const;

  // Получение графа в виде списка смежности
  [[nodiscard]] std::map<int, std::list<int>> GetListAdjacency() const;

  // Получение графа в виде списка ребер
  [[nodiscard]] std::list<std::pair<int, int>> GetListEdges() const;

  // Setter для графа
  void SetIncidenceMatrix(const std::vector<std::vector<int>>& matrix);

  // Проверка на пустоту графа
  [[nodiscard]] bool empty() const;

  // Проверка на ориентированность графа
  [[nodiscard]] bool IsOrient() const;

};


#endif //PEERGRADEGRAPHS__GRAPH_H_
