#include <iostream>
#include <string>

using namespace std;

struct node //структура элемента очереди
{
    int data; //значение элемента
    node* next; //указатель на следующий элемент
    node(int n) //конструктор элемента очереди
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

    int qGet() //получаем значение первого элемента очереди
    {
        return front->data;
    }

    void qInsert(int n) //вставка в конец очереди
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

    int qRemove() //удаление из начала очереди
    {
        node* temp = front; //прравниваем рабочую переменную к front, а указатель front передаем следующей
        front = front->next;

        if (front == NULL)//если новый front NULL- элемент в очереди был один 
        {
            end = NULL;
        }

        int tempWord = temp->data;//получаем значение
        delete temp; //удаляем элемент
        return tempWord; //и возвращаем значение удаленного
    }

    void calcBalance(int size) //"балансировка" значений для калькулятора
    {
        for (int i = 1; i < size; i++) //наша цель- перенести с помощью смещений последний элемент на первое место, что мы и делаем в цикле
        {
            int num = front->data;
            for (node* q = front; q != NULL && q->next != NULL; q = q->next)
            {
                q->data = (q->next)->data;
            }
            end->data = num;
        }
    }
};

int main()
{
    setlocale(LC_CTYPE, "rus");//подключаем кириллицу
    int size = 0; //size- размер очереди
    string equation, tempr; //equation- выражение, tempr- временная переменная для цифр
    queue* inProcess = new queue; //рабочяя переменная для очереди

    cout << "Практическая работа №1, Шахгусейнов.\nВведите выражение в префиксной форме\n";
    cin >> equation;

    for (int i = equation.size() - 1; i > -1;) //идем с конца, так как всегда получим две цифры
    {
        while (equation[i] >= '0' && equation[i] <= '9' && size > -1) //получаем в цикле все цифры подряд и "кладем" их в temp, уменьшая счетчик i
        {
            tempr.push_back(equation[i]);
            i--;
        }
        if (equation[i] == '+' || equation[i] == '-' || equation[i] == '*' || equation[i] == '/')//когда получаем знаки- принимаем их все, так как все сохраненные цифры и принятые знаки будут в одном выражении по логике префиксной формы
        {
            for (int j = tempr.size() - 1; j > -1; j--) //идем с конца tempr, чтобы установить порядок выражения, и кладем значения в очередь, увеличивая ее размер
            {
                inProcess->qInsert(tempr[j] - '0');
                size++;
            }
            while ((equation[i] == '+' || equation[i] == '-' || equation[i] == '*' || equation[i] == '/')) //начинаем арифметические операции
            {
                tempr.clear(); //очищаем tempr, так как в нее в дальнейшем положим результат
                if (equation[i] == '+')//в зависимости от знака- выполняемм операцию, "доставая" первые два числа из начала очереди и кладем результат в конец, что является проблемой для вычисления ответа, что решим дальше
                {
                    inProcess->qInsert(inProcess->qRemove() + inProcess->qRemove());
                }
                if (equation[i] == '-')
                {
                    inProcess->qInsert(inProcess->qRemove() - inProcess->qRemove());
                }
                if (equation[i] == '*')
                {
                    inProcess->qInsert(inProcess->qRemove() * inProcess->qRemove());
                }
                if (equation[i] == '/')
                {
                    inProcess->qInsert(inProcess->qRemove() / inProcess->qRemove());
                }
                size--; //уменьшаем размер, так как "поменяли" два значения на одно
                inProcess->calcBalance(size); //и восстанваливаем порядок цифр (кладем результат, полученный выше, в самое начало путем смещений)
                i--;//двигаемся по выражению дальше
                if (i < 0) //"костыль" из-за принятия операндов в цикле while, что может привести к i=-1, а к -1-му элементу строки нельзя обращаться
                    break;//выходим из всех циклов
            }
            tempr += to_string(inProcess->qRemove());//получаем результат всех подряд идущих операций. В конце (i=-1) эта строчка содержит результат
            size = 0;//размер очереди теперь 0
        }
    }

    cout << "Ответ: " << tempr; //вывод результата
}