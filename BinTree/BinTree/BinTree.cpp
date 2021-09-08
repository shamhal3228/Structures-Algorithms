#include <iostream>

using namespace std;

bool cmp(string first, string second) //функция сравнения двух слов
{
	if (first.length() > second.length()) return true; //первое слово длиннее
	if (first.length() < second.length()) return false; //второе слово длиннее
	if (first.length() == second.length()) //если длины равны
	{
		for (int i = 0; i < first.length(); ++i) //посимвольно сравниваем слова
		{
			if (first[i] > second[i]) return true;
			if (first[i] < second[i]) return false;
		}
	}
	return true; //если слова одинаковые
}

struct node //структура узла дерева
{
	string name; //информационное значение узла
	node* left; //указатель на левый "листок"
	node* right; //указатель на правый "листок"
	node(string line) //конструктор узла
	{
		name = line;
		left = NULL;
		right = NULL;
	}
};

node* insert(node* root, string line) // вставка ключа k в дерево с корнем p
{
	if (root == NULL) //если дерева нет
		return new node(line);

	if (cmp(line, root->name)) //если значение больше текущего- помещаем узел вправо
		root->right = insert(root->right, line); 
	else 
		root->left = insert(root->left, line); //иначе- влево
	return root; //и возвращаем изначальный корень
}

void preorderPrint(node* root, int h) //прямой обход
{
	if (root == NULL) //если дерева нет- нечего и выводить
		return;
	for (int i = 0; i < h; i++)
		cout << ' ';
	cout << root->name << '\n'; // вывод элемента
	preorderPrint(root->left, h + 1); //рекурсивный вызов левого поддерева
	preorderPrint(root->right, h + 1); //рекурсивный вызов правого поддерева
}
void inorderPrint(node* root, int h) //симметричный обход
{
	if (root == NULL) //если дерева нет- нечего и выводить
		return;
	inorderPrint(root->left, h + 1); //рекурсивный вызов обхода левого поддерева
	for (int i = 0; i < h; i++)
		cout << ' ';
	cout << root->name << '\n';
	inorderPrint(root->right, h + 1); //рекурсивный вызов обхода правого поддерева
}

void average(node* root, double& n, double& sum) //ищем среднее арифметическое (средняя длина слов в данном случае)
{
	if (root == NULL) //если дерева нет- нечего и выводить
		return;
	n++; //иначе количество слов уже равно 1
	for (int i = 0; i < root->name.length(); ++i) 
		sum++; //считаем количество символов
	average(root->left, n, sum); //и рекурсивно обходим левое и правое поддеревья
	average(root->right, n, sum); 
}

void pathLength(node* root, string l, int& dist) //получение длины пути от корня до заданного элемента
{
	if (root->name == l || root == NULL) //если дерева нет- нечего и выводить
		return;

	dist++; //увеличиваем расстояние на 1
	if (cmp(l, root->name)) //сравниваем искомое значение и текущий узел, чтобы выбрать направление
	{
		if (root->right != NULL) 
			pathLength(root->right, l, dist);//если правый потомок не пустой, рекурсивно вызываем функцию
		else
		{
			dist = -1;//иначе искомого элемента нет и расстояние считать бесполезно
			return;
		}
	}
	else
	{
		if (root->left != NULL) 
			pathLength(root->left, l, dist);//если левый потомок не пустой, рекурсивно вызываем функцию
		else
		{
			dist = -1;//иначе искомого элемента нет и расстояние считать бесполезно
			return;
		}
	}
}

int main()
{
	setlocale(LC_CTYPE, "rus");
	int dist = 0, temp = 1;
	double n = 0, sum = 0;
	string line;
	node* tree = NULL;
	cout << "Практическая работа №6, Шахгусейнов.\n";
	
	while (temp != 0)
	{
		cout << "Выберите действие:\n1.Вставка элемента в древо\n2.Выполнить прямой обход\n3.Выполнить симметричниый обход\n4.Найти среднее арифметическое всех узлов(средняя длина слов)\n5.Найти длину пути от корня до заданного значения\nВведите 0, чтобы завершить работу\n";
		
		cin >> temp;

		if (temp < 0 || temp>5)
			cout << "Введено непредусмотренное значение- попробуйте снова\n";

		if (temp == 1)
		{
			cout << "Введите значение узла (название города): ";
			cin >> line;
			tree = insert(tree, line);
		}
		if (temp == 2)
		{
			if (tree == NULL) 
				cout << "Древа нет- для начала вставьте эелемент\n";
			else
			{
				cout << "Прямой обход: \n";
				preorderPrint(tree, 0);
				cout << '\n';
			}
		}
		if (temp == 3)
		{
			if (tree == NULL) cout << "Древа нет- для начала вставьте эелемент\n";
			else
			{
				cout << "Симметричный обход: \n";
				inorderPrint(tree, 0);
				cout << '\n';
			}
		}
		if (temp == 4)
		{
			if (tree == NULL) cout << "Древа нет- для начала вставьте эелемент\n";
			else
			{
				average(tree, n, sum);
				cout << "Среднее арифметическое (средняя длина слов): " << sum / n << '\n';
			}
			n = 0;
			sum = 0;
		}
		if (temp == 5)
		{
			if (tree == NULL) cout << "Древа нет- для начала вставьте эелемент\n";
			else
			{
				cout << "Введите ключевое значение\n";
				cin >> line;
				pathLength(tree, line, dist);
				if (dist != -1) 
					cout << dist << '\n';
				else 
					cout << "Элемент не найден!\n";
			}
			dist = 0;
		}
		if (temp == 0)
		{
			cout << "Введите ноль снова, если хотите закончить программу\n";
			cin >> temp;
			if (temp == 0)
			{
				cout << "Спасибо за внимание! Работа программы завершена\n";
				return 0;
			}
		}
		cout << '\n';
	}
}