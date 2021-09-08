#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

const int n = 100; //размер массива

int HashMain(string key, int m) {//высчитывание хеш-значения
    int hash = 0; //само значение
    int a = 53; //простое число для правила Горнера
    for (int i = 0; i < key.size(); i++)
        hash = (hash * a + key[i]) % m; //высчитывание хеш-значения по правилу Горнера
    return hash;
}

int partition(int* a, int low, int high, string* b)//вспомогательная функция разбиения
{
    int pivot = a[high];//опорный элемент
    int i = low - 1;//"начальный" элемент

    for (int j = low; j <= high - 1; j++)
    {
        if (a[j] < pivot)//все элементы меньше опроного сортируются и отправляются в конец массива
        {
            i++;
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
            string s = b[i];//вместе с этим сортируются элементы массива слов
            b[i] = b[j];
            b[j] = s;
        }
    }
    int t = a[i + 1];//аналогично
    a[i + 1] = a[high];
    a[high] = t;
    string s = b[i + 1];
    b[i + 1] = b[high];
    b[high] = s;
    return (i + 1);//возвращаем "граинцу" сортировки
}

void quickSort(int* arr, int low, int high, string* b)//быстрая сортировка
{
    if (low < high)//пока левая и правая граница не "столкнулись"- рекурсивно сортируем массив, разбивая его на части и сортируя их
    {
        int pi = partition(arr, low, high, b);
        quickSort(arr, low, pi - 1, b);
        quickSort(arr, pi + 1, high, b);
    }
}

int bin_search(int* a, int left, int right, int key)//бинарный поиск
{
    while (true)
    {
        int mid = (left + right) / 2;//находим средний элемент

        if (key < a[mid])//если значение ключа меньше среднего- ищем в левой части отсортированного массива
            right = mid - 1;
        else if (key > a[mid])//если больше- ищем в правой
            left = mid + 1;
        else
            return mid;//попали в "точку"- возвращаем индекс среднего эелеемнта

        if (left > right)//если границы "схлопнулись" и ничего до этого не нашлось- элемента нет
            return -1;
    }
}

int main()
{
    string* a = new string[n];//массив слов
    int* arr = new int[n];//массив хеш-значений
    fstream fi("text.txt");//файл, их которого будем брать слова
    for (int i = 0; i < n; i++)
    {
        fi >> a[i];//получаем слово
        arr[i] = HashMain(a[i], n);//и сразу считаем его хеш-значение
    }
    quickSort(arr, 0, n - 1, a);//сортируем массив хеш-значений вместе с массивом слов
    string key;
    cin >> key;//получаем "ключ"
    int hashKey = HashMain(key, n);//считаем его хеш-значение...
    int start = clock();//начало отсчета времени работы программы
    int ans = bin_search(arr, 0, n, hashKey);//...и ищем с помощью бинарного поиска
    if (key == a[ans])
    {
        cout << "Found: " << a[ans];//если строки совпали, то сразу выводим ответ
        int end = clock();//время конца работы программы, если строки совпали. Ниже высчитываются другие случаи
        cout << '\n' << end - start;//выводим время работы программы
    }
    else
    {
        int i = ans;//чтобы "не портить" индекс
        while (arr[i] == hashKey)//если произошла коллизия и ключевое слово оказалось правее- ищем его там
        {
            i++;
            if (key == a[i])
            {
                cout << "Found: " << a[i];
                int end = clock();
                cout << '\n' << end - start;
                return 0;
            }
        }
        i = ans;
        while (arr[i] == hashKey)//если слева- то ищем слева
        {
            i--;
            if (key == a[i])
            {
                cout << "Found: " << a[i];
                int end = clock();
                cout << '\n' << end - start;
                return 0;
            }
        }
        cout << "Word " << key << " not found";//если не нашли нужного слова
        int end = clock();
        cout << '\n' << end - start;
    }
}