#include <iostream>
#include <fstream>

using namespace std;

void findUni() //функция нахождения неключевого значения по ключевому
{
	ifstream in("text.txt", ios::app); //открываем файл в режиме чтения, без изменения

	string key, fkey, uni, temp; //раббчоие переменные

	cout << "Введите ключ: ";

	cin >> key; //получаем ключ с клавиатуры

	cout << '\n';

	while (in >> fkey) //пока файл считывается
	{
		if (key == fkey) //если считали ключ, который совпал с искомым- получаем неключевое, выводим его и выходим из функции
		{
			in >> uni;
			cout << uni << '\n';
			return;
		}
		in >> temp;//иначе "пропускаем" неключевое значение неискомого ключа
	}

	cout << "Элемент не найден\n"; //если не вышли раньше- ключа нет
}

void deleteByKey() //функция удаления элемента по неключивому значению
{
	ofstream out("text.txt", ios::in); //открываем файл для ввода в режиме ввода
	ifstream in("text.txt", ios::app); //открываем файл для вывода в режиме без изменения

	string key, fkey, temp = "", intemp; //рабочие переменные
	int index = in.tellg(), tempIndex;

	cout << "Введите ключ: ";
	cin >> key; //получаем ключ
	cout << '\n';

	while (in >> fkey) //пока файл считывается
	{
		if (key == fkey) //при совпадении ключей
		{
			out.seekp(index, ios::beg); //переносим "каретку" на нужную позицию (начало элемента)
			in.seekg(index, ios::beg);
			in >> fkey; //ищем конец элемента- "пропускаем" оба значения
			in >> fkey;
			tempIndex = in.tellg(); //получаем значение позиции в файле
			for (int i = index; i < tempIndex; i++) //создаем пустую строку размера элемента
				temp += " ";
			out.seekp(index, ios::beg); //снова встаем в начало удаляемого элемента
			in.seekg(index, ios::beg);
			out << temp; //и "удаляем" его путем добавления пустой строки
			cout << "Удалено\n";
			return;
		}
		in >> intemp; //если это не произошло- идем дальше
		index = in.tellg(); //и запомниаем позицию
	}
	cout << "Элемент не найден\n"; //если не вышли раньше- элемента нет
}

void inBin() //ввод в бинарный файл
{
	ifstream in("text.txt"); //открываем текстовый файл для чтения
	ofstream out("binary.bin", ios::binary | ios::out); //открываем бинарный файл для записи, очистив раннее содержимое

	char sim; //рабочая переменная

	while (in.get(sim)) //пока считывается файл
		out.write(&sim, sizeof(char)); //переносим символ в бинарный файл
}

void outBin() //вывод содержимого бинарного файла
{
	ifstream in("binary.bin", ios::binary | ios::in); //открываем в режиме для чтения

	char sim; //рабочие переменные
	bool read = false;

	while (in.read(&sim, sizeof(char))) //пока символы считываются
	{
		cout << sim; //выводим их на экран
		read = true;
	}

	if (read == false) //если флаг не изменился- файл пуст
		cout << "Файл пуст\n";
}

int main()
{
	setlocale(LC_CTYPE, "rus");

	int command = 1;
	string key;

	cout << "Практическая работа 8. Шахгусейнов Шамхал\n";

	while (command != 0)
	{
		cout << "Выберите действие:\n1.Запись из текстового файла в бинарный\n2.Чтение бинарного файла\n3.Удалить запись по ключу\n4.Определить неключевой параметр по ключевому\n0.Закончить работу программы\n";

		cin >> command;
		switch (command)
		{
		case 1:
		{
			inBin();
			cout << "Содержимое text.txt записано в binary.bin\n";
			break;
		}
		case 2:
		{
			cout << "Содержимое binary.bin:\n";
			outBin();
			cout << '\n';
			break;
		}
		case 3:
		{
			ofstream out("text.txt", ios::app);
			out << " ";
			out.close();
			deleteByKey();
			break;
		}
		case 4:
		{
			findUni();
			break;
		}
		case 0:
		{
			cout << "Введите ноль снова, если хотите закончить программу\n";
			cin >> command;
			if (command == 0)
			{
				cout << "Спасибо за внимание! Работа программы завершена\n";
				return 0;
			}
			break;
		}
		default:
		{
			cout << "Некорректное значение- попробуйте снова\n";
			break;
		}
		}
		cout << '\n';
	}
}