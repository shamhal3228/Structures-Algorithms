#include <iostream>
#include <string>

using namespace std;

struct node
{
    node* next = nullptr;//указатель на следующий элемент
    int value;//значение элемента
    node(int v);//конструктор
};

struct s_stack
{
public:
    node* last = 0;//указатель на последний элемент
    bool s_empty();//проверка на пустой стек
    void s_push(int v);//втолкнуть значение в стек
    int s_pop();//вытолкнуть и вернуть значения последнего элемента
};

node::node(int v)
{
    value = v;//присвоить значение
    next = nullptr;//следующего элемента нет
}

void s_stack::s_push(int v)
{
    node* n = new node(v);//новый элемент
    n->next = last;//указатель на следующий элемент- на последний
    last = n;//новый элемент становится последним
}

int s_stack::s_pop()
{
    node* temp = last;//временный элемент, равный последнему
    if (last->next != nullptr)//идем до конца стека
        last = last->next;
    else
        last = nullptr;//и последний элемент- нуль
    int resp = temp->value;//получаем значение последнего элемента
    delete temp;//удаляем его
    return resp;//и возвращаем последний элемент
}

bool s_stack::s_empty()
{
    return last == nullptr;//если последний элемент "пустой"- вернет true
}

class stack
{
private: int size;//размер стека
         int i = 0;//переменная, отвечающая за верхний элемент стека
         int *a;//стек в виде динамического массива
public: stack(int n);//конструктор для создания стека с соответствующим размером
      void push(int b);//втолкнуть элемент в стек
      void pop();//вытолкнуть
      int get();//получить значение узла стека
      int cur();//получить значение узла стека для операции переноса
      bool empty();//проверка на пустоту стека
      bool full();//проверка на полноту
      void pushNext();//операция вталкинвания для операции переноса дл следующего элемента
      friend void summ(stack st1, stack st2);
};

stack::stack(int n)
{
    size = n;//размер
    a = new int[size];//массив
    for (int j = 0; j < size; j++)
        a[j] = 0;//обнуляем массив
}

void stack::push(int b)
{
    a[i] += b;//к элементу массива присваиваем значение
    i++;//идем дельше
}

void stack::pop()
{
    a[i] = -1;//в нашей специфической задаче не может быть элемента со значением -1- поэтому это обнуление
    i--;//идем дальше
}

int stack::get()
{
    return a[i-1];//получем последний элемент
}

void stack::pushNext()
{
    a[i] += 1;//прибавляем 1 к следующему элементу стека
}

bool stack::empty()
{
    if (i == 0)//если элементов нет- возвращаем true
        return true;
    else return false;
}

bool stack::full()
{
    if (i == size)//если индекс последнего элемента равен размеру стека- он полон
        return true;
    else return false;
}

int min(int f, int g)//вспомогательная функция поиска максимального
{
    if (f < g)
        return f;
    else 
        return g;
}

int max(int f, int g)//вспомогательная функция поиска минимального
{
    if (f > g)
        return f;
    else
        return g;
}

int stack::cur()
{
    return a[i];//возвращает следующий элемент
}

void summ(stack st1, stack st2)
{
    int a, b;
    stack st3(max(st1.size, st2.size)+1);//создаем стек-результат, размер которого на 1 больше (при сложении возможно увелничение размера числа на 1)
    while (st1.empty()==false && st2.empty()==false)//пока стеки не пусты
    {
        a = st1.get();//получаем верхние элементы
        b = st2.get();
        if (a + b > 9)//если их сумма больше 9
        {
            st3.push(a + b - 10);//в стек отправляем их сумму, но -10
            st3.pushNext();//а в следующий элемент прибавляем 1 (как операция переноса)
        }
        else
            st3.push(a + b);//если сумма меньше- просто отправляем их сумму
        st1.pop();//выталкиваем элемент стека
        st2.pop();
    }

    while (st1.empty() == false)//если остались элементы в стеках
    {
        if (st1.get() + st3.cur() > 9)//и остался перенос
        {
            st3.push(st1.get() - 10);//прибавляем сумму цифры и -10
            st3.pushNext();//и операция переноса
        }
        else
            st3.push(st1.get());//если нет переноса- просто присваиваем последней цифре последную цифру слагаемого
        st1.pop();//уменьшаю стек
    }

    while (st2.empty() == false)//аналогично, если "остался" второй
    {
        if (st2.get() + st3.cur() > 9)
        {
            st3.push(st2.get() - 10);
            st3.pushNext();
        }
        else 
            st3.push(st2.get());
        st2.pop();
    }

    int i = st3.size - 1;
    if (st3.a[i] != 0)
        cout << st3.a[i];//если последний разряд не ноль- выводим его

    for (i--; i >= 0; i--)//и так весь результат
        cout << st3.a[i];

}

int main()
{
    string number1, number2;//получаем числа в строковую переменную

    cin >> number1 >> number2;

    stack st1(number1.size());//создаем стеки соответствующих размеров
    stack st2(number2.size());

    s_stack sa, sb;//стеки на линейном списке


   for (int i = 0; i < number1.size(); i++)//в цикле получаем цифры, преобразуя их из типа char в int
   {
        int ts;
        ts = number1[i] - '0';
        st1.push(ts);//и кладем в оба стека
        sa.s_push(ts);
   }

   for (int i = 0; i < number2.size(); i++)//аналогично со вторым
   {
       int ts;
       ts = number2[i] - '0';
       st2.push(ts);
       sb.s_push(ts);
   }

   s_stack res;//стек на линейном списке результата
   int d = 0;//переменная для переноса
   while (!(sa.s_empty() && sb.s_empty()))//пока стеки не пустые
   {
       int f = 0, s = 0;//переменные для получения цифр из стеков
       if (!sa.s_empty())
           f = sa.s_pop();//получаем из первого
       if (!sb.s_empty())
           s = sb.s_pop();//и второго
       int t = f + s + d;//складываем
       d = t / 10;//и получаем остаток, если это число больше 10
       res.s_push(t % 10);//и кладем остаток от деления на 10
   }

   if (d != 0)
       res.s_push(d);//если остался остаток не ноль- отправляем его в стек

   while (!res.s_empty())
       cout << res.s_pop();//и выводим результат

   cout << '\n';

    summ(st1, st2);//вычисляем сумму на стеке на динамическом массиве
}