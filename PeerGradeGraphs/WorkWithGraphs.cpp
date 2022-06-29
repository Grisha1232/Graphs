#include "WorkWithGraphs.h"
#include "InputMethods.h"

// Вывод списка смежности
std::ostream& operator<< (std::ostream& os, const std::map<int, std::list<int>>& matrix) {
  for (const auto& [vertex, neighbors] : matrix) {
    os << vertex << "\t";
    for (const auto& neighbour : neighbors) {
      os << neighbour << " ";
    }
    os << "\n";
  }
  return os;
}

// Вывод матрицы смежности и матрицы инцидентности
std::ostream& operator << (std::ostream& os, const std::vector<std::vector<int>>& matrix) {
  for (const auto& row : matrix) {
    for (const auto& el : row) {
      os << el << "\t";
    }
    os << "\n";
  }
  return os;
}

// Вывод списка ребер
std::ostream& operator << (std::ostream& os, const std::list<std::pair<int, int>>& matrix) {
  for (const auto& [vertex, neighbor] : matrix) {
    os << vertex << " " << neighbor << "\n";
  }
  return os;
}

// Подсчет степеней и полустепеней графа.
void CountDegreeOfVertices(const Graph& graph) {
  // Проверка на ориентированность графа
  if (!graph.IsOrient()) {
    DegreeOfVertices(graph);
  } else {
    InOutDegreeOfVertices(graph);
  }
}

// Вывод подсчета степеней вершин графа
void DegreeOfVertices(const Graph& graph) {
  // обход по матрице инцидентности.
  int vert = 1;
  for (const auto& vertex : graph.GetIncidenceMatrix()) {
    // Переменная для записи степени вершины.
    int degree = 0;
    // элементы строки матрицы инцидентности.
    for (const auto& ad : vertex) {
      degree += ad;
    }
    std::cout << "The degree of the vertex " << vert << " is equal to " << degree << "\n";
    vert++;
  }
}

// Вывод полустепеней вершин графа.
void InOutDegreeOfVertices(const Graph& graph) {
  // Переменная для хранениия текущей вершины.
  int vert = 1;
  // Обход по рядам матрицы инцидентности.
  for (const auto& vertex : graph.GetIncidenceMatrix()) {
    // Переменные для хранения полустепеней.
    int inDegree = 0, outDegree = 0;
    for (const auto& ad : vertex) {
      if (ad == -1)
        inDegree++;
      if (ad == 1)
        outDegree++;
    }
    std::cout << "The In/Out degree of vertex " << vert << " are (indegree) " << inDegree << " and (outdegree) " << outDegree
    << ". And the Degree is " << inDegree + outDegree << "\n";
    vert++;
  }
}

// Подсчет ребер графа
void CountEdges(const Graph& graph) {
  // Проверка на ориентированность графа
  if (!graph.IsOrient()) {
    std::cout << "The number of edges of the graph is " << graph.GetIncidenceMatrix().at(0).size() << "\n";
  } else {
    std::cout << "Number of arcs of the graph is " << graph.GetIncidenceMatrix().at(0).size() << "\n";
  }
}

// Вывод графа в разных предствалениях
void OutGraph(const Graph& graph) {
  int view;
  std::cout << "How exactly do you want to output the graph?\n";
  std::cout << "1. Adjacency matrix\n"
               "2. The incidence matrix\n"
               "3. Adjacency list\n"
               "4. List of edges" << "\n";
  // Проверка на дурака
  while (std::cin >> view) {
    if (view == 1 || view == 2 || view == 3 || view == 4)
      break;
    else
      std::cout << "There is no such option. Repeat the input: ";
  }
  auto inputMethod = GetInputMethod();
  // Вывод если выбран через консоль
  if (inputMethod.second.empty()) {
    switch (view) {
      case 1: std::cout << graph.GetAdjacencyMatrix(); break;
      case 2: std::cout << graph.GetIncidenceMatrix(); break;
      case 3: std::cout << graph.GetListAdjacency(); break;
      case 4: std::cout << graph.GetListEdges(); break;
      default : std::cout << "Ban"; break;
    }
    // Вывод если выбран через файл (Файл должен быть создан до того как выводить в него)
  } else {
    auto file = std::ofstream(inputMethod.second);
    switch (view) {
      case 1: file << graph.GetAdjacencyMatrix().size() << "\n" << graph.GetAdjacencyMatrix(); break;
      case 2: file << graph.GetIncidenceMatrix().size() << " " << graph.GetIncidenceMatrix().at(0).size() << "\n" << graph.GetIncidenceMatrix(); break;
      case 3: file << graph.GetListAdjacency().size() << "\n" << graph.GetListAdjacency(); break;
      case 4: file << graph.GetListEdges().size() << "\n" << graph.GetListEdges(); break;
      default : file << "Ban"; break;
    }
  }
}

