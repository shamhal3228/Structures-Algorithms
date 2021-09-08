#include <iostream>
#include <string>

using namespace std;

bool isEmpty(int n) //проверка очереди на пустоту
{
    if (n == 1)
        return true;
    else return false;
}

bool isFull(int n, int m) //проверка очереди на полноту
{
    if (n == m + 1)
        return true;
    else return false;
}

void insert(char**& a, int& n, string w) //вставка в конец очереди
{
    for (int i = 0; i < w.size(); i++) //вставляем элемент в очередь
        a[n - 1][i] = w[i];
    n++; //увеличиваем размер очереди
    a = (char**)realloc(a, n * sizeof(char*));//и выделяем место в массиве
    a[n - 1] = (char*)malloc(42 * sizeof(char));
    for (int j = 0; j < 42; j++)
        a[n - 1][j] = ' ';
}

string remove(char**& a, int& n)//удаляем элемент из начала очереди
{
    string temp = "                                          ";//выделяем переменную...
    for (int i = 0; i < 42; i++)
        temp[i] = a[0][i]; // ...для сохрания первого элемента
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < 42; j++)
            a[i][j] = a[i + 1][j];//смещаем массив "вперед"
    n--; //уменьшаем размер очереди
    a = (char**)realloc(a, n * sizeof(char*)); //меняем размер массива (удаляем последний)
    return temp; //возвращаем значение удаленного элемента
}

string get(char**& a, int& n)//получаем первый элемент
{
        string temp = "                                          "; //рабочяя переменная
        for (int i = 0; i < 42; i++)
            temp[i] = a[0][i]; //записываем первый элемент в рабочую переменную...
        return temp; //...и возвращаем ее
}

int main()
{
        setlocale(LC_CTYPE, "rus"); //подключаем кириллицу
        int size = 1, temp = 1, maxsize = 5; //size- размер очереди, temp- для интерфейся, maxsize- максимальный размер очереди
        char** arr = NULL; //выделяем память под двумерный массив символов
        arr = (char**)malloc(size * sizeof(char*));
        for (int i = 0; i < size; i++)
        {
            arr[i] = (char*)malloc(42 * sizeof(char));
            for (int j = 0; j < 42; j++)
                arr[i][j] = ' ';
        }
        string animal; //переменная для получения данных для элемента очереди
        cout << "Практическая работа №1, Шахгусейнов.\nВыберите действие:\n1.Вставка элемента в конец очереди\n2.Удалить элемнт из начала очереди\n3.Получить значение элемента очереди на первом месте\n4.Проверка- не пуста ли очередь\n5.Проверка- не полна ли очередь\nВведите 0, если закчончили работу\n";
        while (temp != 0)
        {
            cin >> temp;
            if (temp!=0 && temp != 1 && temp != 2 && temp != 3 && temp != 4 && temp != 5)
                cout << "Введено непредусмотренное значение- попробуйте снова\n";
            if (temp == 1)
            {
                if (!isFull(size, maxsize))
                {
                    cin >> animal;
                    insert(arr, size, animal);
                }
                else cout << "Очередь переполнена\n";
            }
            if (temp == 2)
            {
                if (isEmpty(size))
                {
                    cout << "Очередь пуста\n";
                }
                else cout << "Удалено слово: " << remove(arr, size) << "\n";
            }
            if (temp == 3)
            {
                if (isEmpty(size))
                    cout << "Очередь пуста\n";
                else cout << get(arr, size) << "\n";
            }
            if (temp == 4)
            {
                if (isEmpty(size))
                    cout << "Очередь пуста\n";
                else cout << "Очередь не пуста\n";
            }
            if (temp == 5)
            {
                if (isFull(size, maxsize))
                    cout << "Очередь переполнена\n";
                else cout << "Очередь не переполнена\n";
            }
        }
}