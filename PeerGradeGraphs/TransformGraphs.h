#include <vector>
#include <map>
#include <list>

#ifndef PEERGRADEGRAPHS__TRANSFORMGRAPHS_H_
#define PEERGRADEGRAPHS__TRANSFORMGRAPHS_H_
// Преобразование в матрицу инцидентности и обатно

// Преобразование из матрицы смежности
std::vector<std::vector<int>> FromAdjacency(const std::vector<std::vector<int>>& matrix);
// Преобразование из списка смежности
std::vector<std::vector<int>> FromListAdjacency(const std::map<int, std::list<int>>& matrix);
// Преобразование из списка ребер
std::vector<std::vector<int>> FromListEdges(const std::list<std::pair<int, int>>& matrix);

// Преобразование в матрицу смежности
std::vector<std::vector<int>> ToAdjacency(const std::vector<std::vector<int>>& matrix);
// Преобразование в список смежности
std::map<int, std::list<int>> ToListAdjacency(const std::vector<std::vector<int>>& matrix);
// Преобразование в список ребер
std::list<std::pair<int, int>> ToListEdges(const std::vector<std::vector<int>>& matrix);

#endif //PEERGRADEGRAPHS__TRANSFORMGRAPHS_H_
