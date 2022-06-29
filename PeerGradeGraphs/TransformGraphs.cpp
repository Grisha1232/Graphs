#include "TransformGraphs.h"
#include <iostream>

// Преобразование из матрицы смежности в матрицу инцидентности
std::vector<std::vector<int>> FromAdjacency(const std::vector<std::vector<int>>& matrix) {
  std::vector<std::vector<int>> result;
  size_t edges = 0;
  // Подсчет кол-во ребер
  for (size_t i = 0; i < matrix.size(); ++i)
    for (size_t j = i; j < matrix.size(); ++j)
      if (matrix.at(i).at(j) || matrix.at(j).at(i))
        edges++;
  result = std::vector(matrix.size(), std::vector<int>(edges, 0));
  size_t edge = 0;
  for (size_t i = 0; i < matrix.size(); ++i) {
    for (size_t j = i; j < matrix.size(); ++j) {
      // Создание правильной матрицы инцидентности (Порядок ребер может отличаться от вашего)
      if (matrix.at(i).at(j) || matrix.at(j).at(i)) {
        if (matrix.at(i).at(j) == matrix.at(j).at(i)) {
          result.at(i).at(edge) = 1;
          result.at(j).at(edge++) = 1;
        } else if (matrix.at(i).at(j)) {
          result.at(i).at(edge) = 1;
          result.at(j).at(edge++) = -1;
        } else {
          result.at(i).at(edge) = -1;
          result.at(j).at(edge++) = 1;
        }
      }
    }
  }
  return result;
}

// Преобразование из списка смежности в матрицу инцидентности
std::vector<std::vector<int>> FromListAdjacency(const std::map<int, std::list<int>>& matrix) {
  int max = -1;
  // Находим максимальную вершину (число).
  for (const auto& [f, s] : matrix) {
    if (max < f)
      max = f;
    for (const auto& r : s) {
      if (max < r)
        max = r;
    }
  }
  std::vector<std::vector<int>> result = std::vector<std::vector<int>>(max, std::vector<int>(max, 0));
  // Преобразование сначала в матрицу смежности
  for (const auto& [vertex, neighbors] : matrix) {
    for (const auto& neighbour : neighbors) {
      result.at(vertex - 1).at(neighbour - 1) = 1;
    }
  }
  // Преобразование в матрицу инцидентности
  return FromAdjacency(result);
}

// Преобразование из списка ребер в матрицу инцидентности
std::vector<std::vector<int>> FromListEdges(const std::list<std::pair<int, int>>& matrix) {
  std::map<int, std::list<int>> result;
  // Преобразование сначала в список смежности
  for (const auto& [f, s] : matrix) {
    result[f].push_back(s);
    if (result[s].empty())
      result[s] = {};
  }
  // Преобразование в матрицу инцидентности через список смежности
  return FromListAdjacency(result);
}

// Преобразование из матрицы инцидентности в матрицу смежности
std::vector<std::vector<int>> ToAdjacency(const std::vector<std::vector<int>>& matrix) {
  std::vector<std::vector<int>> result = std::vector<std::vector<int>>(matrix.size(), std::vector<int>(matrix.size(), 0));
  for (size_t i = 0; i < matrix.at(0).size(); ++i) {
    // Для запоминания вершины
    size_t vertex = matrix.size();
    for (size_t j = 0; j < matrix.size(); ++j) {
      if ((matrix.at(j).at(i) == 1 && vertex == matrix.size()) || (matrix.at(j).at(i) == -1 && vertex == matrix.size())) {
        vertex = j;
      } else if (matrix.at(j).at(i) == 1) {
        // Если встретились две единицы, то ставим в матрицу смежности семмитрично единицы
        if (matrix.at(vertex).at(i) == 1) {
          result.at(j).at(vertex) = 1;
          result.at(vertex).at(j) = 1;
        }
        // Если встретились единица и минус единица то ставим только во одно место
        if (matrix.at(vertex).at(i) == -1) {
          result.at(j).at(vertex) = 1;
        }
        // Если встретилась сначала минус единица после единица
      } else if (matrix.at(j).at(i) == -1 && matrix.at(vertex).at(i) == 1) {
        result.at(vertex).at(j) = 1;
      }
    }
  }
  return result;
}

// Преобразование из матрицы инцидентности в список смежности
std::map<int, std::list<int>> ToListAdjacency(const std::vector<std::vector<int>>& matrix) {
  std::map<int, std::list<int>> result;
  for (size_t i = 0; i < matrix.at(0).size(); ++i) {
    // Для запоминание вершины
    size_t vertex = matrix.size();
    for (size_t j = 0; j < matrix.size(); ++j) {
      if ((matrix.at(j).at(i) == 1 && vertex == matrix.size()) || (matrix.at(j).at(i) == -1 && vertex == matrix.size())) {
        vertex = j;
      } else if (matrix.at(j).at(i) == 1) {
        // Если встретились две единицы, то добавить к этим вершинам противоположную вершину
        if (matrix.at(vertex).at(i) == 1) {
          // Т.к. в списке смежности отсчет начинается с 1 то добавляю 1
          result[static_cast<int>(vertex) + 1].push_back(static_cast<int>(j) + 1);
          result[static_cast<int>(j) + 1].push_back(static_cast<int>(vertex) + 1);
        }
        // Если встретились единица и минус единица, то добавить только одной вершине другую вершину
        if (matrix.at(vertex).at(i) == -1) {
          result[static_cast<int>(j) + 1].push_back(static_cast<int>(vertex) + 1);
        }
        // Если встретилась сначала минус единица после единица, то добавить одной вершине другую (В другом порядке)
      } else if (matrix.at(j).at(i) == -1 && matrix.at(vertex).at(i) == 1) {
        result[static_cast<int>(vertex) + 1].push_back(static_cast<int>(j) + 1);
      }
    }
  }
  return result;
}

// Преобразование из матрицы инцидентности к списку ребер
std::list<std::pair<int, int>> ToListEdges(const std::vector<std::vector<int>>& matrix) {
  std::list<std::pair<int, int>> result;
  for (size_t i = 0; i < matrix.at(0).size(); ++i) {
    // Для запоминания вершины
    size_t vertex = matrix.size();
    for (size_t j = 0; j < matrix.size(); ++j) {
      if ((matrix.at(j).at(i) == 1 && vertex == matrix.size()) || (matrix.at(j).at(i) == -1 && vertex == matrix.size())) {
        vertex = j;
      } else if (matrix.at(j).at(i) == 1) {
        // Если встретились две единицы, добавлем друг другу вершины
        if (matrix.at(vertex).at(i) == 1) {
          result.emplace_back(vertex + 1, j + 1);
          result.emplace_back(j + 1, vertex + 1);
        }
        // Если встретились единица и минус единица, то добавляем только одной
        if (matrix.at(vertex).at(i) == -1) {
          result.emplace_back(j + 1, vertex + 1);
        }
        // Если встретилась минус единица и единица, то добавляем только одной (в другом порядке)
      } else if (matrix.at(j).at(i) == -1 && matrix.at(vertex).at(i) == 1) {
        result.emplace_back(vertex + 1, j + 1);
      }
    }
  }
  return result;
}
