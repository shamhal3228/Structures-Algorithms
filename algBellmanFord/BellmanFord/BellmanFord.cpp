#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main()
{
	int NumberOfVerticals, NumberOfEdges;
	setlocale(LC_CTYPE, "rus");
	cout << "Введите количество вершин и количество ребер\n";
	cin >> NumberOfVerticals >> NumberOfEdges; //количество вершин и количество ребер
	vector < vector <int> > vertical(NumberOfEdges, vector<int>(3)); //структура предстваления графа- список ребер (вес ребра, начало вершины, конец вершины)
	map <char, int> temporary; //карта для перевода символов в числа
	temporary.insert(pair<char, int>(' ', -1)); //первый элемент как заглушка
	auto it = temporary.begin(); //итератор
	cout << "Введите список ребер графа\n";
	for (int i = 0; i < NumberOfEdges; ++i) //получаем граф
	{
		char a, b; //получаем символы
		bool flag1 = false, flag2 = false;
		cin >> a;
		cin >> b;
		cin >> vertical[i][2]; //и вес
		for (auto it = temporary.begin(); it != temporary.end(); ++it) //проходимся по карте и ищем симолы без кода
		{
			if (it->first == a)
				flag1 = true;
			if (it->first == b)
				flag2 = true;
		}
		if (!flag1) //если такие были- выдаем код символу
			temporary.insert(pair<char, int>(a, temporary.size() - 1));
		if (!flag2)
			temporary.insert(pair<char, int>(b, temporary.size() - 1));

		vertical[i][0] = temporary[a]; //и выдаем эти значения в список ребер
		vertical[i][1] = temporary[b];
	}

	char key; //ключевое значение как символ
	int start; //ключевое значение как число
	cout << "Введите вершину:\n";
	cin >> key;
	for (auto it = temporary.begin(); it != temporary.end(); ++it) //ищем ключевой символ в карте и выдаем start значение
	{
		if (it->first == key)
		{
			start = temporary[key];
			break;
		}
	}
	
	const int INF = 1e9; //переменная для обозначения бесконечности
	vector <int> F(NumberOfVerticals, INF); //значения
	F[start] = 0;
	for (int k = 0; k < NumberOfVerticals; ++k)
		for (auto& edge : vertical)
		{
			int start = edge[0];
			int finish = edge[1];
			int weight = edge[2];
			if (F[start] + weight < F[finish])
				F[finish] = F[start] + weight;
		}

	it = temporary.begin();
	it++;
	cout << "Кратчайщий путь от вашей вершины до всех вершин графа:\n";
	for (int i = 0; i < NumberOfVerticals; i++)
	{

		cout << it->first << " " << F[i] << '\n';
		++it;
	}
}