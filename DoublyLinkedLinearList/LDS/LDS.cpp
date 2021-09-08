#include <iostream>

using namespace std;

struct node //структура элемента ЛДС
{
    int data; //значение элемента
    node* next = NULL, * prev = NULL; //указатели на следующий и предыдущий элементы
};

void addHead(node** head, node** tail, int data) //добавление элемента в начало списка
{
    node* temp = new node(); //инициализируем добавляемый элемент
    temp->data = data;

    if ((*head) == NULL) //если списка нет- создаем его
    {
        temp->next = NULL;
        temp->prev = NULL;
        *head = temp;
        *tail = temp;
        return;
    }

    (*head)->prev = temp; //иначе- вставялем перед головным и меняем указатель head
    temp->next = *head;
    temp->prev = NULL;
    *head = temp;
}

void deleteTail(node** tail, node** head) //удаление последнего элемента
{
    node* curr = *tail; //рабочая переменная

    if (curr == NULL) //если списка нет- выходим из функции
    {
        cout << "Нет ЛДС\n";
        return;
    }

    if (curr->prev == NULL) //если элемент один
    {
        (*tail) = NULL;
        tail = NULL;
        (*head) = NULL;
        head = NULL;
        curr = NULL;
        free(curr);
        free(tail);
        free(head);
        cout << "Элемент удален\n";
        return;
    }

    *tail = curr->prev; //иначе- удаляем последний элемент, меняя указатели у предыдущего элемента
    (*tail)->next = NULL;
    curr->prev = NULL;
    free(curr);
    cout << "Элемент удален\n";
}

void searchLR(node** head, int data) //поиск элемента по значению слева-направо
{
    if ((*head) == NULL) //если списка нет- выходим из функции 
    {
        cout << "Нет ЛДС\n";
        return;
    }

    int index = 0; //позиция элемента
    
    node* curr = *head; //проходимся по списку слева-направо и сравниваем информационные части с искомым значением; при совпадении- выходим из цикла
    while (curr != NULL)
    {
        if (curr->data == data)
        {
            cout << "Найден элемент " << data << " под номером " << index << '\n';
            return;
        }
        index++;
        curr = curr->next;
    }
    cout << "Элемент не найден\n"; //иначе- элемента нет
}

void searchRL(node** tail, int data) //поиск элемента по значению справа-налево
{
    if ((*tail) == NULL) //если списка нет- выходим из функции
    {
        cout << "Нет ЛДС\n";
        return;
    }

    int index = 0; //позиция элемента
    node* curr = *tail; //проходимся по списку справа-налево и сравниваем информационные части с искомым значением
     
    while (curr != NULL)
    {
        if (curr->data == data) //при совпадении- выходим из цикла
        {
            cout << "Найден элемент " << data << " под номером " << index << '\n';
            return;
        }
        index++;
        curr = curr->prev;
    }
    cout << "Элемент не найден\n"; //иначе- элемента нет
}

void changeByData(node** head, int oldData, int newData) //изменение элемента по значению
{
    if ((*head) == NULL) //если списка нет- выходим из функции 
    {
        cout << "Нет ЛДС\n";
        return;
    }

    node* curr = *head; //иначе проходимся по списку и ищем искомое значение

    while (curr != NULL)
    {
        if (curr->data == oldData) //при совпадении- меняем значение и выходим из функции
        {
            curr->data = newData;
            cout << "Изменено\n";
            return;
        }
        curr = curr->next;
    }
    cout << "Элемент не найден\n"; //иначе элемента нет
}

void printLR(node** head)
{
    if ((*head) == NULL) //если списка нет- выходим из функции 
    {
        cout << "Нет ЛДС\n";
        return;
    }

    node* curr = *head; //проходимся по списку слева-направо и выводим информационные части элементов
    while (curr != NULL)
    {
        cout << curr->data << ' ';
        curr = curr->next;
    }
    cout << '\n';
}

void printRL(node** tail)
{
    if ((*tail) == NULL) //если списка нет- выходим из функции 
    {
        cout << "Нет ЛДС\n";
        return;
    }

    node* curr = *tail; //проходимся по списку справа-налево и выводим информационные части элементов
    while (curr != NULL)
    {
        cout << curr->data << ' ';
        curr = curr->prev;
    }
    cout << '\n';
}

int main()
{
    setlocale(LC_CTYPE, "rus");

    int data, newData, command = 1, subcommand;

    node* head = new node(), * two = new node(), * three = new node(), * four = new node(), * five = new node(), * six = new node(), * seven = new node(), * eight = new node(), * nine = new node(), * tail = new node();
    
    head->next = two;
    two->next = three;
    three->next = four;
    four->next = five;
    five->next = six;
    six->next = seven;
    seven->next = eight;
    eight->next = nine;
    nine->next = tail;

    tail->prev = nine;
    nine->prev = eight;
    eight->prev = seven;
    seven->prev = six;
    six->prev = five;
    five->prev = four;
    four->prev = three;
    three->prev = two;
    two->prev = head;

    cout << "Практическая работа 4. Линейные двусвязные списки. Шахгусейнов Шамхал ИКБО-02-19\n";

    cout << "Введите 10 целочисленных значений для линейного двусвязного списка\n";

    node* curr = head;
    while (curr != NULL)
    {
        cin >> data;
        curr->data = data;
        curr = curr->next;
    }

    while (command != 0)
    {
        cout << "Выберите команду:\n1.Добавить элемент в начало списка\n2.Удалить последний элемент\n3.Найти элемент(первое вхождение)\n4.Изменить элемент по значению (первое вхождение)\n5.Вывести ЛДС\n0.Закончить работу\n";

        cin >> command;

        switch (command)
        {
        case 1:
        {
            cout << "Введите значение\n";
            cin >> data;
            addHead(&head, &tail, data);
            cout << "Элемент добавлен\n";
            break;
        }
        case 2:
        {
            deleteTail(&tail, &head);
            break;
        }
        case 3:
        {
            cout << "Выберите подкомманду\n1.Проход слева-направо\n2.Проход справа-налево\n";
            cin >> subcommand;
            switch (subcommand)
            {
            case 1:
            {
                cout << "Введите значение\n";
                cin >> data;
                searchLR(&head, data);
                break;
            }
            case 2:
            {
                cout << "Введите значение\n";
                cin >> data;
                searchRL(&tail, data);
                break;
            }
            default:
            {
                cout << "Некорректное значение- попробуйте снова\n";
                break;
            }
            }
            break;
        }
        case 4:
        {
            cout << "Введите старое и новое значения\n";
            cin >> data >> newData;
            changeByData(&head, data, newData);
            break;
        }
        case 5:
        {
            cout << "Выберите подкомманду\n1.Проход слева-направо\n2.Проход справа-налево\n";
            cin >> subcommand;
            switch (subcommand)
            {
            case 1:
            {
                printLR(&head);
                break;
            }
            case 2:
            {
                printRL(&tail);
                break;
            }
            default:
            {
                cout << "Некорректное значение- попробуйте снова\n";
                break;
            }
            }
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
//1 2 3 4 5 6 7 8 9 10