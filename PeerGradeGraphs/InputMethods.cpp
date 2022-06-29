#include "InputMethods.h"
#include "TransformGraphs.h"
#include <filesystem>

// Получение способа ввода матриц и/или списков. (Return: <1 или 2, string>)
std::pair<int, std::string> GetInputMethod() {
  std::cout << "Select the matrix input method (Enter the operation number):" << "\n";
  std::cout << "1. Via the console\n"
               "2. Via file" << "\n";
  int inputMethod;
  // Проверка на дурака
  while (std::cin >> inputMethod) {
    if (inputMethod != 1 && inputMethod != 2) {
      std::cout << "There is no such operation. Repeat the input: ";
    } else {
      break;
    }
  }
  // Если выбран файл то ввести его
  if (inputMethod == 2) {
    std::string filePath;
    std::cout << "Enter the path to the file: ";
    while(getline(std::cin >> std::ws, filePath)) {
      // Проверка на дурака
      const std::filesystem::path path(filePath);
      std::error_code ec;
      // Проверка на существование файла
      if (std::filesystem::is_regular_file(path, ec))
      {
        break;
      } else {
        std::cout << "The file path is incorrect. Repeat the input: ";
      }
    }
    return {inputMethod, filePath};
  }
  return {inputMethod, ""};
}

// Получение свединия о вводимой матрице. (Return: 1, 2, 3 или 4)
int GetTheMatrixView() {
  std::cout << "Select the type of matrix to be entered (Enter the number):" << "\n";
  std::cout << "1. Adjacency matrix\n"
               "2. The incidence matrix\n"
               "3. Adjacency list\n"
               "4. List of edges" << "\n";
  int view;
  // Проверка на дурака
  while (std::cin >> view) {
    if (view != 1 && view != 2 &&
        view != 3 && view != 4) {
      std::cout << "There is no such option. Repeat the input: ";
    } else {
      break;
    }
  }
  return view;
}

// Получение номера операции с матрицей. (Return: 1, 2, 3, 4 или 5)
int GetMatrixOperation() {
  std::cout << "1. Counting degrees of vertices for an undirected graph or Indegree/Outdegree of vertices for an oriented graph.\n"
               "2. Counting the number of edges (for an undirected)/arcs (for an oriented) graph.\n"
               "3. Output of the graph in a different representation.\n"
               "4. Enter new graph.\n"
               "5. Exit the program.\n";
  int operation;
  while (std::cin >> operation) {
    if (operation != 1 && operation != 2 && operation != 3 &&
        operation != 4 && operation != 5) {
      std::cout << "There is no such operation. Repeat the input: ";
    } else {
      break;
    }
  }
  return operation;
}

// Получение матрицы смежности через консоль / файл. (Return: <матрица, true / false>)
std::pair<std::vector<std::vector<int>>, bool> GetAdjacencyMatrix(std::istream& in, bool isViaConsole) {
  int vertices;
  // Если производится ввод с консоли выводится подсказка
  if (isViaConsole)
    std::cout << "Enter the number of vertices of the graph: ";
  in >> vertices;
  std::vector<std::vector<int>> adjacencyMatrix(vertices, std::vector<int>(vertices));
  // Если производится ввод с консоли выводится подсказка
  if (isViaConsole)
    std::cout << "Enter the adjacency matrix: " << "\n";
  int adjacency;
  for (int i = 0; i < vertices; ++i) {
    for (int j = 0; j < vertices; ++j) {
      in >> adjacency;
      // Если в матрице присутсвуют элементы не 1 или 0 то сразу возвращаем матрицу с false
      if (adjacency != 1 && adjacency != 0) {
        return {adjacencyMatrix, false};
      }
      adjacencyMatrix.at(i).at(j) = adjacency;
    }
  }
  return {adjacencyMatrix, true};
}


// Получение матрицы инцидентности через консоль / файл (Return: <матрица, true / false>)
std::pair<std::vector<std::vector<int>>, bool> GetIncidenceMatrix(std::istream& in, bool isViaConsole) {
  int vertices, edges;
  // Если производится ввод с консоли выводится подсказка
  if (isViaConsole)
    std::cout << "Enter the number of vertices of the graph: ";
  in >> vertices;
  // Если производится ввод с консоли выводится подсказка
  if (isViaConsole)
    std::cout << "Enter the number of edges of the graph: ";
  in >> edges;
  std::vector<std::vector<int>> incidenceMatrix(vertices, std::vector<int>(edges));
  // Если производится ввод с консоли выводится подсказка
  if (isViaConsole)
    std::cout << "Enter the adjacency matrix:" << "\n";
  int adjacency;
  for (int i = 0; i < vertices; ++i) {
    for (int j = 0; j < edges; ++j) {
      in >> adjacency;
      // Есил присутсвуют элементы кроме -1, 1 или 0, return <матрцица, false>
      if (adjacency != -1 && adjacency != 1 && adjacency != 0) {
        return {incidenceMatrix, false};
      }
      incidenceMatrix.at(i).at(j) = adjacency;
    }
  }
  return {incidenceMatrix, true};
}

// Получение списка смежности (Return: <список, true / false>)
std::pair<std::map<int, std::list<int>>, bool> GetListAdjacency(std::istream& in, bool isViaConsole) {
  int vertices;
  // Если производится ввод с консоли выводится подсказка
  if (isViaConsole)
    std::cout << "Enter the number of lines in the list: ";
  in >> vertices;
  std::string str;
  int vertex;
  std::map<int, std::list<int>> listAdjacency;
  for (int i = 0; i < vertices; ++i) {
    in >> vertex;
    getline(in, str);
    std::stringstream stream(str);
    int neighbour;
    while (stream >> neighbour) {
      // Проверка на вводимые значения
      if (neighbour == vertex) {
        return {listAdjacency, false};
      }
      listAdjacency[vertex].push_back(neighbour);
    }
  }
  return {listAdjacency, true};
}

// Получение списка ребер (Return: <список, true / false>)
std::pair<std::list<std::pair<int, int>>, bool> GetListEdges(std::istream& in, bool isViaConsole) {
  int edges;
  // Если производится ввод с консоли выводится подсказка
  if (isViaConsole)
    std::cout << "Enter the number of lines in the edge list: ";
  in >> edges;
  std::list<std::pair<int, int>> listEdges;
  for (int i = 0; i < edges; ++i) {
    int first, second;
    in >> first >> second;
    // Проверка на вводимые значения
    if (first == second) {
      return {{}, false};
    }
    listEdges.emplace_back(first, second);
  }
  return {listEdges, true};
}

// Получение нового графа (Return: true(если получилось)) / false(если не получилось))
bool GetNewGraph(Graph& graph) {
  std::pair<int, std::string> inputMethod;
  // Получение вида матрицы (1 из 4-х)
  int viewMatrix = GetTheMatrixView();
  // Получение способа ввода
  inputMethod = GetInputMethod();
  if (!inputMethod.second.empty()) {
    std::ifstream file = std::ifstream(inputMethod.second);
    return SetGraph(graph, file, inputMethod, viewMatrix);
  } else {
    return SetGraph(graph, std::cin, inputMethod, viewMatrix);
  }
}

// Присвоение графу матрицы (Return: true(Если получилось) / false(Если не получилось))
bool SetGraph(Graph& graph, std::istream& in, const std::pair<int, std::string>& inputMethod, const int& view) {
  switch (view) {
    case 1: {
      auto inputResult = GetAdjacencyMatrix(in, inputMethod.second.empty());
      if (inputResult.second) {
        graph.SetIncidenceMatrix(FromAdjacency(inputResult.first));
        return inputResult.second;
      }
      std::cout <<  "\nYou entered incorrect data (each element must be either 0 or 1). Repeat the input.\n";
      return inputResult.second;
    }
    case 2: {
      auto inputResult = GetIncidenceMatrix(in, inputMethod.second.empty());
      if (inputResult.second) {
        graph.SetIncidenceMatrix(inputResult.first);
        return inputResult.second;
      }
      std::cout << "\nYou entered incorrect data (each element must be either -1, 0 or 1). Repeat the input.\n";
      return inputResult.second;
    }
    case 3: {
      auto inputResult = GetListAdjacency(in, inputMethod.second.empty());

      if (inputResult.second) {
        graph.SetIncidenceMatrix(FromListAdjacency(inputResult.first));
        return inputResult.second;
      }
      std::cout << "\nYou entered incorrect data (each element must be less than amount of edges). Repeat the input.\n";
      return inputResult.second;
    }
    case 4: {
      auto inputResult = GetListEdges(in, inputMethod.second.empty());
      if (inputResult.second) {
        graph.SetIncidenceMatrix(FromListEdges(inputResult.first));
        return inputResult.second;
      }
      std::cout << "\nYou entered incorrect data. Repeat the input.\n";
      return inputResult.second;
    }
    default : {
      return false;
    }
  }
}



