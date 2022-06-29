#include <iostream>
#include "WorkWithGraphs.h"
#include "InputMethods.h"
#include "Graph.h"


int main() {
  Graph graph;
  int operation = 0;
  // Получаем граф пока не введен правильный
  while (!GetNewGraph(graph)) {}
  // Повтор программы, пока не введена 5 будет предложено выбрать операцию с графом
  while (operation != 5) {
    // Получаем операцию
    operation = GetMatrixOperation();
    switch(operation) {
      // Подсчет степеней вершин
      case 1: CountDegreeOfVertices(graph); break;
      // Подсчет ребер в графе
      case 2: CountEdges(graph); break;
      // Вывод графа консоль / файл
      case 3: OutGraph(graph); break;
      // Ввод другого графа
      case 4: while(!GetNewGraph(graph)){} break;
      // Выход из программы
      case 5: std::cout << "Goodbye.\n";
      default:
        break;
    }
  }
  return 0;
}