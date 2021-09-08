#include <iostream>

using namespace std;

struct node //структура элемента ЛОС
{
    int data; //значение элемента
    node* next; //указатель на следующий элемент
};
    
    void addHead(node** head, int data) //функция, которая вставляет элемент в начало списка; **head- адрес головного элемента, data- значение
    {
        node* temp = new node(); //создаем элемент ЛОС-а
        temp->data = data; //присваиваем ему значение

        if (*head == NULL) //если список еще не создан- инициализируем его
        {
            temp->next = NULL;
            *head = temp;
            return;
        }

        temp->next = *head; //иначе "передвигаем" головной элемент
        *head = temp;
    }

    void addTail(node** head, int data)//функция, которая вставляет элемент в конец списка; **head- адрес головного элемента, data- значение
    {
        node* temp = new node(); //создаем элемент ЛОС-а
        temp->data = data; //присваиваем ему значение
        temp->next = NULL; //и указатель на следующий элемент присваиваем NULL

        if (*head == NULL) //если список еще не создан- инициализируем его
        {
            *head = temp;
            return;
        }

        node* last = *head; //иначе- ищем последний элемент проходом по всему списку
        while (last->next != NULL)
        {
            last = last->next;
        }

        last->next = temp; //и меняем указатель последнего элемента на следуюущий на новосозданный
    }

    void addAfter(node** head, int data, int i)//функция, которая вставляет элемент в середину списка после заданного элемента; **head- адрес головного элемента, data- значение, i- значение элемента, после которого вставляем новый элемент
    {
        node* curr = *head; //создаем рабочую переменную, с помощью которой ищем элемент, значение которого нам известно

        if (*head == NULL) //если список еще не создан- инициализируем его
        {
            curr->data = data;
            curr->next = NULL;
            *head = curr;
            return;
        }

        while (curr != NULL) //пробегаемся по списку
        {
            if (curr->data == i) //если элемент найдем- выходим из цикла
                break;

            curr = curr->next; //иначе- ищем дальше
        }
        
        if (curr == NULL) //если мы дошли до конца, но элемент не был найден- выходим с соответствующим сообщением из функции
        {
            cout << "Элемент не найден";
            return;
        }

        node* temp = new node(); //иначе- создаем элемент ЛОС-а
        temp->data = data; //присваиваем ему значение
        temp->next = curr->next; //и меняем соответствующие указатели
        curr->next = temp;
    }

    void addBefore(node** head, int data, int i) //функция, которая вставляет элемент в середину списка перед заданным элементом; **head- адрес головного элемента, data- значение, i- значение элемента, перед которым вставляем новый элемент
    {
        node* curr = *head; //создаем рабочую переменную, с помощью которой ищем элемент, значение которого нам известно

        if (*head == NULL) //если список еще не создан- инициализируем его
        {
            curr->data = data;
            curr->next = NULL;
            *head = curr;
            return;
        }

        while (curr != NULL) //пробегаемся по списку
        {
            if (curr->data == i) //если элемент найдем- выходим из цикла
                break;

            curr = curr->next; //иначе- ищем дальше
        }

        if (curr == NULL) //если мы дошли до конца, но элемент не был найден- выходим с соответствующим сообщением из функции
        {
            cout << "Элемент не найден";
            return;
        }

        node* temp = new node(); //создаем элемент ЛОС-а
        temp->data = data; //присваиваем ему значение
        temp->next = curr->next;//и меняем соответствующие указатели
        curr->next = temp;

        int sklad = temp->data; //и применяем трюк Вирта
        temp->data = curr->data;
        curr->data = sklad;
    }

    void deleteByPosition(node** head, int i) //функция, которая удаляет элемент по номеру в спике; **head- адрес головного элемента, i- номер удаляемого элемента
    {
        if (*head == NULL) //если списка нет- выходми из функции с соответствующим значением
        {
            cout << "Нет ЛОС\n";
            return;
        }

        node* curr = *head; //рабочая переменная

        if (i == 1) //если удаляется первый элемент- меняем head и удаляем curr
        {
            *head = curr->next;
            free(curr);
            cout << "Удалено\n";
            return;
        }

        for (i; curr != NULL && i > 2; i--) //иначе- доходим за один до нужного элемента
        {
            curr = curr->next;
        }

        if (curr == NULL || curr->next==NULL) //если значение позиции удаляемого элемента больше размера списка- выходим из функции с сооответствующим сообщением
        {
            cout << "Выход за пределы ЛОС\n";
            return;
        }

        node* temp = curr->next->next; //иначе- сохраняя ссылку на следующий за удаляемым элементом элемент, удаляем нужный и и предыдущего за ним элементу выдаем новый указатель на следующий элемент
        free(curr->next);
        curr->next = temp;
        cout << "Удалено\n";
    }

    void deleteByData(node** head, int data) //функция, которая удаляет элемент по значению в спике(первое вхождение); **head- адрес головного элемента, data- значение удаляемого элемента
    {
        if (*head == NULL) //если списка нет- выходми из функции с соответствующим значением
        {
            cout << "Нет ЛОС\n";
            return;
        }

        node* curr = *head, * prev = new node(); //рабочие переменные; curr для прохода, prev- предыдущая удаляемому элементу

        while (curr != NULL && curr->data != data) //проходимся по списку и ищем элемент с нужным значением, запоминая предыдущий
        {
            prev = curr;
            curr = curr->next;
        }

        if (curr == NULL) //если элемент не был найдем- выходим из функции с соответствующим значением
        {
            cout << "Не найден элемент\n";
            return;
        }

        prev->next = curr->next; //иначе- меняем указатель предыдущего на следующий относительно удаляемого

        free(curr); //удаляем

        cout << "Удалено\n";
    }

    void deleteAllByData(node** head, int data) //функция, которая удаляет элемент по значению в спике(все вхождения); **head- адрес головного элемента, data- значение удаляемого элемента
    {
        if (*head == NULL) //если списка нет- выходми из функции с соответствующим значением
        {
            cout << "Нет ЛОС\n";
            return;
        }

        node* curr = *head, * prev = new node(); //рабочие переменные; curr для прохода, prev- предыдущая удаляемому элементу

        while (curr != NULL && curr->data == data) //случай, при котором удаляемые элементы- головные
        {
            *head = curr->next;
            free(curr);
            curr = *head;
        }

        while (curr != NULL) //проходимся по списку и ищем элементы с нужным значением, запоминая предыдущий
        {
            while (curr != NULL && curr->data != data)
            {
                prev = curr;
                curr = curr->next;
            }

            if (curr == NULL) //если элемент не был найдем- выходим из функции с соответствующим значением
            {
                cout << "Функция выполнила свою работу\n";
                return;
            }

            prev->next = curr->next; //иначе- меняем указатель предыдущего на следующий относительно удаляемого

            free(curr); //удаляем

            curr = prev->next; //и идем дальше по циклу
        }
    }

    void search(node** head, int data) //поиск элемента по значению(первое вхождение); **head- адрес головного элемента, data- значение искомого элемента
    {
        if (*head == NULL) //если списка нет- выходми из функции с соответствующим значением
        {
            cout << "Нет ЛОС\n";
            return;
        }

        node* curr = *head; //рабочая переменная для прохода

        while (curr != NULL) //проходимся по списку
        {
            if (curr->data == data) //при совпадении значений- выводим сообщение и выходим из функции
            {
                cout << curr->data << " найден\n";
                return;
            }
            curr = curr->next; //иначе- идем дальше
        }

        cout << data << " не найден\n"; //если не вышли из функции ранее- элемент не найден, о чем и сообщаем
    }

    void searchAll(node** head, int data) //поиск элемента по значению(все вхождения); **head- адрес головного элемента, data- значение искомых элементов
    {
        if (*head == NULL) //если списка нет- выходми из функции с соответствующим значением
        {
            cout << "Нет ЛОС\n";
            return;
        }

        node* curr = *head; //рабочая переменная для прохода
        int  counter = 0; //счетчик элементов

        while (curr != NULL) //проходимся по списку
        {
            if (curr->data == data) //при совпадении значений- прибавляем к счетчику 1 и идем дальше
                counter++;
            curr = curr->next; //иначе- идем дальше
        }
        if (counter == 0) // если счетчик не изменил свое значение- элементы не найдены, о чем и сообщаем
            cout << data << " не найден\n";
        else 
            cout << "Всего значений " << data << " в ЛОС " << counter << '\n'; //иначе- выводим количество найденных элементов
    }

    void changeByData(node** head, int data, int num) //замена элемента по значению(первое вхождение); **head- адрес головного элемента, data- значение искомого элемента, num- значение, на которое меняем
    {
        if (*head == NULL) //если списка нет- выходми из функции с соответствующим значением
        {
            cout << "Нет ЛОС\n";
            return;
        }

        node* curr = *head; //рабочая переменная для прохода

        while (curr != NULL) //проходимся по списку
        {
            if (curr->data == data) //если элемент с нужным значением найден- меняем его и выходим из функции
            {
                curr->data = num;
                cout << "Изменено\n";
                return;
            }
            curr = curr->next; //иначе- идем дальше
        }

        cout << data << " не найден\n"; //если не вышли из функции ранее- элемент не найден, о чем и сообщаем
    }

    void changeByDataAll(node** head, int data, int num) //замена элемента по значению(все вхождения); **head- адрес головного элемента, data- значение искомых элементов, num- значение, на которое меняем
    {
        if (*head == NULL) //если списка нет- выходми из функции с соответствующим значением
        {
            cout << "Нет ЛОС\n";
            return;
        }

        node* curr = *head; //рабочая переменная для прохода
        bool flag = false; //флаг, который поменяется при нахождении элемента

        while (curr != NULL) //проходимся по списку
        {
            if (curr->data == data) //если элемент с нужным значением найден- меняем его и флаг
            {
                curr->data = num;
                flag = true;
            }
            curr = curr->next; //и идем дальше
        }

        if (flag == false) //если флаг не поменялся- элемент не найден, о чем и сообщаем
            cout << data << " не найден\n";
        else
            cout << "Изменены все\n";
    }

    void changeByPosition(node** head, int i, int num) //изменить элемент по значению; **head- адрес головного элемента, i-позиция изменяемого элемента, num- значение, на которое меняем
    {
        if (*head == NULL) //если списка нет- выходми из функции с соответствующим значением
        {
            cout << "Нет ЛОС\n";
            return;
        }

        node* curr = *head; //рабочая переменная для прохода
        int counter = 1; //счетчик элементов
       
        while (curr != NULL) //проходимся по списку
        {
            if (counter == i) //если совпали счетчик и позиция изменяемого элемента- меняем значение элемента
            {
                curr->data = num;
                cout << "Изменено\n";
                return;
            }
            counter++; //инкрементируем счетчик
            curr = curr->next; //иначе- идем дальше
        }

        cout << "Некорректный индекс\n"; //если не вышли из функции раньше- введен некорректный индекс, о чем и сообщаем
    }

    void swapNode(node** head, int a, int b) //поменять два элемента местами; **head- адрес головного элемента, a-значение первого элемента, b- второго
    {
        if (*head == NULL) //если списка нет- выходми из функции с соответствующим значением
        {
            cout << "Нет ЛОС\n";
            return;
        }

        if (a == b) //если введены два одинаковых значения- выходим из функции
        {
            cout << "Значения поменялись местами\n";
            return;
        }

        node* prevA = NULL, * currA = *head; //рабочие переменные для первого значения (предыдущий и сам элементы)
        node* prevB = NULL, * currB = *head; //рабочие переменные для второго значения (предыдущий и сам элементы)

        while (currA != NULL && currA->data != a) //ищем первый элемент в списке
        {
            prevA = currA;
            currA = currA->next;
        }

        while (currB != NULL && currB->data != b) //ищем второй элемент в списке
        {
            prevB = currB;
            currB = currB->next;
        }

        if (currA == NULL || currB == NULL) //если хотя бы один из них не был найден- выходим из функции
        {
            cout << "Не найдено\n";
            return;
        }

        if (prevA != NULL) //если предыдущий элемент для первого ненулевой- меняем его указатель на следующий элемента на второй
            prevA->next = currB;
        else 
            *head = currB; //иначе- меняем головной элемент на второй

        if (prevB != NULL) //если предыдущий элемент для второго ненулевой- меняем его указатель на следующий элемента на первый
            prevB->next = currA;
        else
            *head = currA; //иначе- меняем головной элемент на первый

        node* temp = currB->next; //и меняем указатели первого и второго элемента на следующие на следующие второго и первого соответственно
        currB->next = currA->next;
        currA->next = temp;
        cout << "Значения поменялись местами\n";
    }

    int getLength(node** head) //получаем размер списка; **head- адрес головного элемента
    {
        if (*head == NULL) //если списка нет- выходми из функции с соответствующим значением
        {
            return 0;
        }

        node* temp = *head; //рабочяя переменная
        int counter = 0; //счетчик размера списка

        while (temp != NULL) //проходимся по списку
        {
            counter++; //и инкрементируем счетчик
            temp = temp->next;
        }

        return counter; //и возвращаем размер списка
    }

    void printAll(node** head) //вывод списка; **head- адрес головного элемента
    {
        if (*head == NULL) //если списка нет- выходми из функции с соответствующим значением
        {
            cout << "Нет ЛОС\n";
            return;
        }

        node* temp = *head; //рабочая переменная

        while (temp != NULL) //проходимся по списку
        {
            cout << temp->data << " "; //и выводим их информационную часть
            temp = temp->next;
        }
        cout << '\n';
    }

    void deleteAll(node** head) //удаление списка; **head- адрес головного элемента
    {
        if (*head == NULL) //если списка нет- выходми из функции с соответствующим значением
        {
            cout << "Нет ЛОС\n";
            return;
        }

        node* temp = *head, * next; //рабочие переменные

        while (temp != NULL) //проходимся по списку
        {
            next = temp->next; //одной переменной переходим сразу к следующему
            free(temp); //текущую удаляем
            temp = next; //и переходим второй переменной к следующей
        }

        *head=NULL; //обнуляем головной элемент
        cout << "Список удален\n";
    }

int main()
{
    setlocale(LC_CTYPE, "rus");

    cout << "Практическая работа 1. Линейные односвязные списки. Шахгусейнов Шамхал ИКБО-02-19\n";

    node* head = new node(), * two = new node(), * three = new node(), * four = new node(), * five = new node(), * six = new node(), * seven = new node(), * eight = new node(), * nine = new node(), * ten = new node();
    head->next = two;
    two->next = three;
    three->next = four;
    four->next = five;
    five->next = six;
    six->next = seven;
    seven->next = eight;
    eight->next = nine;
    nine->next = ten;
    ten->next = NULL;

    node* temp = head;
    cout << "Введите 10 целочисленных значений для линейного односвязного списка\n";

    while (temp != NULL)
    {
        cin >> temp->data;
        temp = temp->next;
    }

    cout << "Выберите команду:\n1.Добавить элемент\n2.Удалить элемент\n3.Найти элемент\n4.Изменить элемент\n5.Поменять два элемента местами\n6.Вычислить длину ЛОС\n7.Вывести (распечатать) ЛОС на экран\n8.Удалить ЛОС\n0.Выход из программы\n";
    
    int command = 1, subcommand = 0, data, num;
    while (command != 0)
    {
        cin >> command;
        switch (command)
        {
        case 1:
        {
            cout << "Выберите подкоманду:\n1.Добавить элемент в начало списка\n2.Добавить элемент в конец списка\n3.Добавить элемент в середину списка\n";
            cin >> subcommand;
            switch (subcommand)
            {
            case 1:
            {
                cout << "Введите значение\n";
                cin >> data;
                addHead(&head, data);
                cout << '\n';
                break;
            }
            case 2:
            {
                cout << "Введите значение\n";
                cin >> data;
                addTail(&head, data);
                cout << '\n';
                break;
            }
            case 3:
            {
                cout << "Выберите подкоманду:\n1.Добавить элемент после заданного\n2.Добавить элемент перед заданным\n";
                cin >> subcommand;
                switch (subcommand)
                {
                case 1:
                {
                    cout << "Введите новое и старое значения элемента\n";
                    cin >> data >> num;
                    addAfter(&head, data, num);
                    cout << '\n';
                    break;
                }
                case 2:
                {
                    cout << "Введите новое и старое значения элемента\n";
                    cin >> data >> num;
                    addBefore(&head, data, num);
                    cout << '\n';
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
            default:
            {
                cout << "Некорректное значение- попробуйте снова\n";
                break;
            }
            }
            break;
        }
        case 2:
        {
            cout << "Выберите подкоманду:\n1.Удалить первый элемент\n2.Удалить последний элемент\n3.Удалить заданный элемент\n";
            cin >> subcommand;
            switch (subcommand)
            {
            case 1:
            {
                deleteByPosition(&head, 1);
                break;
            }
            case 2:
            {
                deleteByPosition(&head, getLength(&head));
                break;
            }
            case 3:
            {
                cout << "Выберите подкоманду:\n1.Первое вхождение\n2.Все вхождения\n";
                cin >> subcommand;
                switch (subcommand)
                {
                case 1:
                {
                    cout << "Введите значение\n";
                    cin >> data;
                    deleteByData(&head, data);
                    break;
                }
                case 2:
                {
                    cout << "Введите значение\n";
                    cin >> data;
                    deleteAllByData(&head, data);
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
            default:
            {
                cout << "Некорректное значение- попробуйте снова\n";
                break;
            }
            }
            break;
        }
        case 3:
        {
            cout << "Выберите подкоманду:\n1.Первое вхождение\n2.Все вхождения\n";
            cin >> subcommand;
            switch (subcommand)
            {
            case 1:
            {
                cout << "Введите значение\n";
                cin >> data;
                search(&head, data);
                break;
            }
            case 2:
            {
                cout << "Введите значение\n";
                cin >> data;
                searchAll(&head, data);
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
            cout << "Выберите подкоманду:\n1.По значению\n2.По порядковому номеру\n";
            cin >> subcommand;
            switch (subcommand)
            {
            case 1:
            {
                cout << "Выберите подкоманду:\n1.Первое вхождение\n2.Все вхождения\n";
                cin >> subcommand;
                switch (subcommand)
                {
                case 1:
                {
                    cout << "Введите искомое и новое значения\n";
                    cin >> data >> num;
                    changeByData(&head, data, num);
                    break;
                }
                case 2:
                {
                    cout << "Введите искомое и новое значения\n";
                    cin >> data >> num;
                    changeByDataAll(&head, data, num);
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
            case 2:
            {
                cout << "Введите индекс и новое значения\nПримечание: отсчет идет с 1\n";
                cin >> num >> data;
                changeByPosition(&head, num, data);
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
        case 5:
        {
            cout << "Введите два значения\n";
            cin >> data >> num;
            swapNode(&head, data, num);
            break;
        }
        case 6:
        {
            cout << "Размер списка: " << getLength(&head) << '\n';
            break;
        }
        case 7:
        {
            printAll(&head);
            break;
        }
        case 8:
        {
            deleteAll(&head);
            break;
        }
        default:
        {
            cout << "Некорректное значение- попробуйте снова\n";
            break;
        }
        }
    }

    //system("pause");
    return 0;
}
/*
0 1 2 3 4 5 6 7 8 9
1 2 1 3 1 4 1 5 1 1
*/