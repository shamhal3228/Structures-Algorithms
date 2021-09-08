#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

class node //узел
{
public:
	int frequency; //частота узла
	char letter; //символ
	node* left, * right; //правый и левый "потомок"

	node() //пустой конструктор
	{
		left = NULL;
		right = NULL;
	}

	node(node* L, node* R) //конструктор с указателями на потомков
	{
		left = L;
		right = R;
		frequency = L->frequency + R->frequency;
	}
};


struct myCompare
{
	bool operator()(const node* l, const node* r) const //перегруженный операнд () для сравнения по потомку
	{
		return l->frequency < r->frequency;
	}
};


vector<bool> code; //двочиный код строки
map<char, vector<bool> > table; //"карта" ассоциации символа с его двоичным кодом

void buildTree(node* root) //создание дерева 
{
	if (root->left != NULL)//если существует левый потомок- добавить к коду 0 и реккусривно вызвать функцию для левого
	{
		code.push_back(0);
		buildTree(root->left);
	}

	if (root->right != NULL)//если существует правый потомок- добавить к коду 1 и реккусривно вызвать функцию для правого
	{
		code.push_back(1);
		buildTree(root->right);
	}

	if (root->left == NULL && root->right == NULL) //если потомков нет- добавить код в таблицу
		table[root->letter] = code;

	if (!code.empty()) //если код остался- убираем один символ из кода (идем вверх по дереву)
		code.pop_back();
}


int main()
{
	setlocale(LC_CTYPE, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "Введите строку\n";
	map<char, int> m; //карта ассоциаций символ-количество повторений

	string str; //принимаем строку
	getline(cin, str);

	for (int i = 0; i < str.length(); i++) //и записываем частоту символов
	{
		char letter = str[i];
		m[letter]++;
	}

	//записываем начальные узлы в список list

	list<node*> tempNode;
	for (map<char, int>::iterator itr = m.begin(); itr != m.end(); ++itr) //с помощью итератора идем до конца карты
	{
		node* temp = new node; //и создаем узлы
		temp->letter = itr->first;
		temp->frequency = itr->second;
		tempNode.push_back(temp);
	}


	//создаем дерево		

	while (tempNode.size() != 1) //пока есть узлы
	{
		tempNode.sort(myCompare()); //отсортировав карту по частоте

		node* left = tempNode.front(); //получаем первые два элемента
		tempNode.pop_front();
		node* right = tempNode.front();
		tempNode.pop_front();

		node* parent = new node(left, right); //и создаем новый, суммировав частоты
		tempNode.push_back(parent); //и создав новый "пустой" узел
	}

//создаем пары 'символ-код':			

	buildTree(tempNode.front()); //построим дерево, начав с вершины, выводим ответ

	cout << "Сжатая строка: ";

	int powerOfArchivation = 0; //высчитываем среднюю длину кода
	float avgCodeLength = 0;

	auto it = m.begin();
	for (it; it != m.end(); it++)
	{
		float temp = it->second;
		temp /= str.length();
		temp *= table[it->first].size();
		avgCodeLength += temp;
	}

	float disper = 0; //и дисперсию
	it = m.begin();
	for (it; it != m.end(); it++)
	{
		float temp = it->second;
		temp /= str.length();
		float qtemp = table[it->first].size() - avgCodeLength;
		qtemp *= qtemp;
		temp *= qtemp;
		disper += temp;
	}

	for (int i = 0; i < str.length(); i++) //идем до конца строки
	{
		char letter = str[i];
		vector<bool> temp = table[letter]; //получаем код

		for (int j = 0; j < temp.size(); j++) //и выводим посимвольно
		{
			cout << temp[j];
			powerOfArchivation++; //для вычисления степени сжатия
		}
		cout << " ";
	}

	float res = str.length() * 8;
	res /= powerOfArchivation;
	cout << "\nКоэффициент сжатия: " << res << "\nДисперсия: " << disper;
}

//Шахгусейнов Шамхал Мехти оглы