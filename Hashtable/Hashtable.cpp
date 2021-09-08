#include <iostream>
#include <string>

using namespace std;

struct hashStruct //структура элемента хеш-таблицы
{
    string key; //ключ
    hashStruct(string key) //конструктор
    {
        this->key = key;
    }
};

int hashCount(string key, int size, int a) //вычисляем значение ключа по методу Горнера
{
    int res = 0;
    for (int i = 0; i < key.size(); i++)
        res = (res * a + key[i]) % size;
    res = (res * 2 + 1) % size;
    return res;
}

int main()
{
    setlocale(LC_CTYPE, "rus");
    const int hashSize = 100000; //так как номер читательского- пятизначное число, элементов всего 100000
    int h;//переменная для хеш-значения
    bool flag = false;
    hashStruct* hashTable[hashSize]; //сама таблица
    for (int i = 0; i < hashSize; i++)
        hashTable[i] = NULL;//обнуляем хеш-таблицу
    string FIOA;//ФИО и адрес
    cout << "Практическая работа №3, Шахгусейнов.\nВыберите действие:\n1.Вставка элемента\n2.Удаление элемента\n3.Поиск элемента\n4.Вывести все эелемнты\nВведите 0, если закончили работу\n";
    string temp = "1";
    while (temp != "0")
    {
        getline(cin, temp);
        if (temp == "1")
        {
            cout << "Введите ФИО и адрес для добавления в таблицу\n";
            getline(cin, FIOA);
            h = hashCount(FIOA, hashSize, hashSize - 1);
            while (hashTable[h] != NULL && h < hashSize) //если элемент таблицы занят (коллизия)- смещаемся на один элемент до тех пор, пока не найдем пустой элемент. Ну или табоица переполнена
            {
                h++;
            }
            if (h < hashSize)
                hashTable[h] = new hashStruct(FIOA);
            else cout << "Хеш-таблица переполнена\n";
        }
        if (temp == "2")
        {
            cout << "Введите ФИО и адрес, которые хотите удалить\n";
            getline(cin, FIOA);
            h = hashCount(FIOA, hashSize, hashSize - 1);
            while (hashTable[h] != NULL && h < hashSize) //ищем непустой элемент
            {
                if (hashTable[h]->key == FIOA) //если коллизия- ищем нужный с помощью введенных данных элемент и удаляем его
                {
                    hashTable[h] = NULL;
                    flag = true;
                    break;
                }
                else h++;
            }
            if (flag == false) //если мы так и не попали в if, значит элемент не найден, значит, удалять нечего
                cout << "Элемент не найден\n";
            else cout << "Элемент удален\n";
        }
        if (temp == "3")
        {
            "Введите ФИО и адрес для поиска в таблице\n";
            getline(cin, FIOA);
            h = hashCount(FIOA, hashSize, hashSize - 1);
            while (hashTable[h] != NULL && h < hashSize)
            {
                if (hashTable[h]->key == FIOA)
                {
                    flag = true;
                    break;
                }
                else h++;
            }
            if (flag == false)
            {
                cout << "Элемент не найден\n";
            }
            else cout << "Найден " << hashTable[h]->key << " с номером " << h << '\n';
        }
        if (temp == "4")
        {
            cout << "Вывод всех элементов таблицы\n";
            for (int i = 0; i < hashSize; i++)
                if (hashTable[i] != NULL)
                {
                    flag = true;
                    cout << hashTable[i]->key << " с номером " << i << '\n';
                }
            if (flag == false)
                cout << "Элементы не найдены\n";
        }
        flag = false;
    }
}