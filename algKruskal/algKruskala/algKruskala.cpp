#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    setlocale(LC_CTYPE, "rus");
    int NumberOfVerticals, NumberOfEdges; //количество вершин и ребер графа
    cout << "Введите количество вершин и ребер графа\n";
    cin >> NumberOfVerticals >> NumberOfEdges;
    vector <vector <int> > vertical(NumberOfEdges, vector<int>(3)); //структура предстваления графа- список ребер (вес ребра, начало вершины, конец вершины)

    cout << "Введите граф в виде: начало вершины, конец вершины, вес соединяющего ребра\n";
    for (int i = 0; i < NumberOfEdges; ++i)
    {
        cin >> vertical[i][1] >> vertical[i][2] >> vertical[i][0];
        vertical[i][1]--;
        vertical[i][2]--;
    }

    sort(vertical.begin(), vertical.end()); //сортируем по весу ребер
    vector <int> comp(NumberOfVerticals); //номера компоненты связанности

    for (int i = 0; i < NumberOfVerticals; ++i)
        comp[i] = i;
    cout << "\nПостроенное остовное дерево графа:\n";
    for (auto& edge : vertical) //обходим матрицу графа
    {
        int weight = edge[0]; //получаем значения
        int start = edge[1];
        int end = edge[2];
        if (comp[start] != comp[end]) //если компоненты не равны
        {
            int a = comp[start]; //заопмниаем их
            int b = comp[end];
            for (int i = 0; i < NumberOfVerticals; ++i) //пройдя по всем вершинам
                if (comp[i] == b) //меняем нужные компоненты связанности
                    comp[i] = a;
            start++;
            end++;
            cout << start << " " << end << " " << weight << '\n'; //и выводим "оставленные"
        }
    }
}

/*
5 8
1 2 1
1 3 2
1 5 10
2 5 6
2 4 3
5 4 11
3 5 7
3 4 4
*/