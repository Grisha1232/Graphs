#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <fstream>
#include <sstream>
#include <string>
#include "Graph.h"

#ifndef PEERGRADEGRAPHS__GETINPUTMETHODS_H_
#define PEERGRADEGRAPHS__GETINPUTMETHODS_H_

// Получение вида хранения графа
int GetTheMatrixView();
// Получение способа ввода
std::pair<int, std::string> GetInputMethod();
// Получение операции с графом
int GetMatrixOperation();

// Получение нового графа
bool GetNewGraph(Graph& graph);

// Присвоение матрицы графу
bool SetGraph(Graph& graph, std::istream& in, const std::pair<int, std::string>& inputMethod, const int& view);

// Получение матрицы смежности
std::pair<std::vector<std::vector<int>>, bool> GetAdjacencyMatrix(std::istream& in, bool isViaConsole);

// Получение матрицы инцидентности
std::pair<std::vector<std::vector<int>>, bool> GetIncidenceMatrix(std::istream& in, bool isViaConsole);

// Получение списка смежности
std::pair<std::map<int, std::list<int>>, bool> GetListAdjacency(std::istream& in, bool isViaConsole);

// Получение списка ребер
std::pair<std::list<std::pair<int, int>>, bool> GetListEdges(std::istream& in, bool isViaConsole);

#endif //PEERGRADEGRAPHS__GETINPUTMETHODS_H_
