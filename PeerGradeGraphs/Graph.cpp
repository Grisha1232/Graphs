#include "Graph.h"

// Получение матрицы смежности
[[nodiscard]] std::vector<std::vector<int>> Graph::GetAdjacencyMatrix()  const {
  return ToAdjacency(incidenceMatrix);
}

// Получение матрицы инцидентности
[[nodiscard]] std::vector<std::vector<int>> Graph::GetIncidenceMatrix() const {
  return incidenceMatrix;
}

// Получчение списка смедности
[[nodiscard]] std::map<int, std::list<int>> Graph::GetListAdjacency() const {
  return ToListAdjacency(incidenceMatrix);
}

// Получение списка ребер
[[nodiscard]] std::list<std::pair<int, int>> Graph::GetListEdges() const {
  auto result = ToListEdges(incidenceMatrix);
  result.sort();
  return result;
}

// Присвоение данному графу матрицы инцидентности
void Graph::SetIncidenceMatrix(const std::vector<std::vector<int>>& matrix) {
  incidenceMatrix = matrix;
}

// Проверка графа на пустоту
[[nodiscard]] bool Graph::empty() const {
  return incidenceMatrix.empty();
}

// Проверка графа на ориентированность (является это орграфом или нет)
[[nodiscard]] bool Graph::IsOrient() const {
  auto matrix = GetAdjacencyMatrix();
  for (size_t i = 0; i < matrix.size(); ++i) {
    for (size_t j = 0; j < matrix.size(); ++j) {
      if (matrix.at(i).at(j))
        if (matrix.at(j).at(i) != 1)
          return true;
    }
  }
  return false;
}
