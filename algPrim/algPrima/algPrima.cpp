#include <iostream>
#include <cstring>
using namespace std;
 
#define INF 9999999
 
int main () {

    setlocale(LC_CTYPE, "rus");

    int V;//количество вершин
    cout << "Введите количество вершин\n";
    cin >> V;
 
  int no_edge;//номер ребра

  int** G = new int* [V]; //матрица смежности графа

  for (int i = 0; i < V; i++)
      G[i] = new int[V];

  cout << "Ввести граф в виде матрице смежности\n";

  for (int i=0; i<V; i++)
      for (int j = 0; j < V; j++)
      {
          cin >> G[i][j];
      }
 
  //массив для отслеживания вершин
  bool* selected = new bool[V];

  for (int i = 0; i < V; i++)
      selected[i] = false;
 
 //заполняем false

 
 //номер ребра- 0
  no_edge = 0;
 
 //начнем с первого
  selected[0] = true;
 
  int x;            //номер строчки
  int y;            //номер столбца
 
  
  cout << "Edge" << " : " << "Weight";
  cout << endl;
  while (no_edge < V - 1) {
 
  //находим все ребра, которые соединяют дерево с новыми вершинами, находим минимум и добавляем его в дерево.
 
      int min = INF;
      x = 0;
      y = 0;
 
      for (int i = 0; i < V; i++) {
        if (selected[i]) {
            for (int j = 0; j < V; j++) {
              if (!selected[j] && G[i][j]) { 
                  if (min > G[i][j]) {
                      min = G[i][j];
                      x = i;
                      y = j;
                  }
 
              }
          }
        }
      }
      cout << x + 1 << " - " << y + 1 << " :  " << G[x][y];
      cout << endl;
      selected[y] = true;
      no_edge++;
    }
 
  return 0;
}