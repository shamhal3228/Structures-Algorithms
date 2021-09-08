#include <iostream>
#include <string>

using namespace std;

struct node //структура элемента очереди
{
    string data; //значение элемента
    node* next; //указатель на следующий элемент
    node(string n) //конструктор элемента очереди
    {
        data = n; //выдаем значение элементу
        next = NULL; //указатель на следущий элемент- NULL
    }
};

struct queue //структруа очереди
{
    node* front, * end; //указатели на первый и последние элементы очереди
    queue() //конструктор
    {
        front = NULL;
        end = NULL;
    }

    bool qIsEmpty()//проверка на пустоту- нет первого элемента- нет очереди
    {
        if (front == NULL)
            return true;
        else return false;
    }

    bool qIsFull(int max)//проверка на полноту
    {
        int i = 0;
        for (node* q = front; q != NULL; q = q->next)//проходим по очереди, увеличивая счетчик i
            i++;
        if (i == max) //и возвращаем соответствующее значение
            return true;
        else return false;
    }

    string qGet() //получаем значение первого элемента очереди
    {
        return front->data;
    }

    void qInsert(string n) //вставка в конец очереди
    {
        node* temp = new node(n);//создаем рабочую переменную
        if (end == NULL)//если нет очереди- создаем ее и завершаем работу
        {
            front = temp;
            end = temp;
            return;
        }

        end->next = temp;//если она есть- меняем end
        end = temp;
    }

    string qRemove() //удаление из начала очереди
    {
        node* temp = front; //прравниваем рабочую переменную к front, а указатель front передаем следующей
        front = front->next;

        if (front == NULL)//если новый front NULL- элемент в очереди был один 
        {
            end = NULL;
        }

        string tempWord = temp->data;//получаем значение
        delete temp; //удаляем элемент
        return tempWord; //и возвращаем значение удаленного
    }
};

int main()
{
    queue* q = new queue; //рабочий элемент очереди
    string animal; //переменная для получения данных для элемента очереди
    setlocale(LC_CTYPE, "rus");//подключаем кириллицу
    int temp = 1, maxsize = 3; //temp- для интерфейся, maxsize- максимальный размер очереди
    cout << "Практическая работа №1, Шахгусейнов.\nВыберите действие:\n1.Вставка элемента в конец очереди\n2.Удалить элемнт из начала очереди\n3.Получить значение элемента очереди на первом месте\n4.Проверка- не пуста ли очередь\n5.Проверка- не полна ли очередь\nВведите 0, если закчончили работу\n";
    while (temp != 0)
    {
        cin >> temp;
        if (temp != 0 && temp != 1 && temp != 2 && temp != 3 && temp != 4 && temp != 5)
            cout << "Введено непредусмотренное значение- попробуйте снова\n";
        if (temp == 1)
        {
            if (q->qIsFull(maxsize) == false)
            {
                cin >> animal;
                q->qInsert(animal);
            }
            else cout << "Очередь переполнена\n";
        }
        if (temp == 2)
        {
            if (!q->qIsEmpty())
            {
                cout << "Удалено слово: " << q->qRemove() << "\n";
            }
            else cout << "Очередь пуста\n";
        }
        if (temp == 3)
        {
            if (q->qIsEmpty())
                cout << "Очередь пуста\n";
            else cout << q->qGet() << "\n";
        }
        if (temp == 4)
        {
            if (q->qIsEmpty())
                cout << "Очередь пуста\n";
            else cout << "Очередь не пуста\n";
        }
        if (temp == 5)
        {
            if (q->qIsFull(maxsize))
                cout << "Очередь переполнена\n";
            else cout << "Очередь не переполнена\n";
        }
    }
}