#include <iostream>

using namespace std;

struct node // структура для представления узлов дерева
{
	int data; //информационное значение узла
	int height; //высота поддерева
	node* left; //указатель на левый "листок"
	node* right; //указатель на правый "листок"
	node(int d) //конструктор узла
	{ 
		data = d; 
		left = 0; 
		right = 0; 
		height = 1;
	}
};

int getHeight(node* p) // узнаем высоту заданного узла p (вспомогательная функция)
{
	if (p == NULL) //если узла нет- возвращаем ноль
		return 0;
	else 
		return p->height;
}

int getBalanceFactor(node* p) //узнаем "баланс" (разница между высотами правого и левого поддеревьев) заданного узла p (вспомогательная функция) (не делаем проверку на p==NULL, так как в дальнейшем она сама себя подразумевает)
{
	return getHeight(p->right) - getHeight(p->left);
}

void fixHeight(node* p) //востанавливает высоту height при корректных значениях height в правом и левом узлах
{
	int hl = getHeight(p->left);
	int hr = getHeight(p->right);
	if (hl > hr)
		p->height = hl + 1;
	else p->height = hr + 1;
}

node* rotateRight(node* p) // правый поворот вокруг узла p (вспомогательная функция для балансировки дерева в нужном направлении(перестановка указателей на "листья"))
{
	node* q = p->left; //маняем указатели
	p->left = q->right;
	q->right = p;
	fixHeight(p); //и соответственно подправляем высоты
	fixHeight(q);
	return q; // возвращаем указатель на вершину нового поддерева
}

node* rotateLeft(node* p) // аналогично правому повороту
{
	node* q = p->right;
	p->right = q->left;
	q->left = p;
	fixHeight(p);
	fixHeight(q);
	return q;
}

node* balance(node* p) // балансировка узла p
{
	fixHeight(p); //исправляем его высоту
	if (getBalanceFactor(p) == 2) // если дерево "растеклось" слишком вправо, то балансируем влево
	{
		if (getBalanceFactor(p->right) < 0) //если нарушен баланс у правого "листка" влево, то балансируем вправо
			p->right = rotateRight(p->right);
		return rotateLeft(p); //и завершаем работу функции
	}
	if (getBalanceFactor(p) == -2) //аналогично для "слишком левого" дерева и его возможного "слишком правого" листа
	{
		if (getBalanceFactor(p->left) > 0)
			p->left = rotateLeft(p->left);
		return rotateRight(p);
	}
	return p; // если балансировка не нужна
}

node* insert(node* p, int d) // вставка ключа k в дерево с корнем p
{
	if (p == NULL) //если дерева нет
		return new node(d);
	if (d < p->data) //если значение меньше текущего- помещаем узел влево
		p->left = insert(p->left, d);
	else
		p->right = insert(p->right, d); //иначе- вправо
	return balance(p); //и балансируем
}

void preorderPrint(node* root, int h) //прямой обход
{
	if (root == NULL) //если дерева нет- нечего и выводить
		return;
	for (int i = 0; i < h; i++)
		cout << ' ';
	cout << root->data << '\n'; // вывод элемента
	preorderPrint(root->left, h + 1); //рекурсивный вызов левого поддерева
	preorderPrint(root->right, h + 1); //рекурсивный вызов правого поддерева
}

void inorderPrint(node* root, int h) //симметричный обход
{
	if (root == NULL) //если дерева нет- нечего и выводить
		return;
	inorderPrint(root->left, h + 1);   //рекурсивный вызов обхода левого поддерева
	for (int i = 0; i < h; i++)
		cout << ' ';
	cout << root->data << '\n';
	inorderPrint(root->right, h + 1);  //рекурсивный вызов обхода правого поддерева
}

void average(node* root, int& sum, int& num) //ищем среднее арифметическое
{
	if (root == NULL) //если дерева нет- нечего и выводить
		return;
	sum += root->data; //складываем в переменную значение всех узлов
	num++; //и увеличиваем каунтер num числа узлов дерева
	average(root->left, sum, num); //и рекурсивно обходим левое и правое поддеревья
	average(root->right, sum, num);
}

void finder(node* root, int needed, int& dist) //ищем расстояние до нужного элемента
{
	if (root->data == needed || root == NULL) //если дерева нет- нечего и выводить. Ну или если найден нужный элемент и можно выходить из функции
		return;
	dist++; //увеличиваем с каждым ходом переменную
	if (root->data > needed) //если текущий элемент больше ключа- идем влево (из-за логики построения бинарного древа поиска
	{
		if (root->left!=NULL)
		finder(root->left, needed, dist);
		else
		{
			dist = -1;
			return;
		}
	}
	else //аналогично, если наоборот
	{
		if (root->right != NULL)
		finder(root->right, needed, dist);
		else
		{
			dist = -1;
			return;
		}
	}
}


int main()
{
	setlocale(LC_CTYPE, "rus");
	int temp = 1, key, num = 0, sum = 0, data, dist = 0;
	node* tree = NULL;
	cout << "Практическая работа №2, Шахгусейнов.\nВыберите действие:\n1.Вставка элемента\n2.Прямой обход\n3.Симметричниый обход\n4.Найти среднее арифметическое всех узлов\n5.Найти длину пути от корня до заданного значения\nВведите 0, если закчончили работу\n";
	while (temp != 0)
	{
		if (temp != 0 && temp != 1 && temp != 2 && temp != 3 && temp != 4 && temp != 5)
			cout << "Введено непредусмотренное значение- попробуйте снова\n";
		cin >> temp;
		if (temp == 1)
		{
			cout << "Введите значение узла\n";
			cin >> key;
			tree = insert(tree, key);
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
			if (tree == NULL)
				cout << "Древа нет- для начала вставьте эелемент\n";
			else
			{
				cout << "Симметричный обход: \n";
				inorderPrint(tree, 0);
				cout << '\n';
			}
		}
		if (temp == 4)
		{
			if (tree == NULL)
				cout << "Древа нет- для начала вставьте эелемент\n";
			else
			{
				average(tree, sum, num);
				cout << "Среднее арифметическое: " << sum / num << '\n';
			}
		}
		if (temp == 5)
		{
			if (tree == NULL)
				cout << "Древа нет- для начала вставьте эелемент\n";
			else
			{
				cout << "Введите ключевое значение\n";
				cin >> data;
				finder(tree, data, dist);
				if (dist != -1)
					cout << dist - 1 << '\n';
				else cout << "Элемент не найден\n";
			}
		}
	}
}