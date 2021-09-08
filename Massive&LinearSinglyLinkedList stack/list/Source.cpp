#include <iostream>
#include <string>

using namespace std;

struct node
{
    node* next = nullptr;//��������� �� ��������� �������
    int value;//�������� ��������
    node(int v);//�����������
};

struct s_stack
{
public:
    node* last = 0;//��������� �� ��������� �������
    bool s_empty();//�������� �� ������ ����
    void s_push(int v);//��������� �������� � ����
    int s_pop();//���������� � ������� �������� ���������� ��������
};

node::node(int v)
{
    value = v;//��������� ��������
    next = nullptr;//���������� �������� ���
}

void s_stack::s_push(int v)
{
    node* n = new node(v);//����� �������
    n->next = last;//��������� �� ��������� �������- �� ���������
    last = n;//����� ������� ���������� ���������
}

int s_stack::s_pop()
{
    node* temp = last;//��������� �������, ������ ����������
    if (last->next != nullptr)//���� �� ����� �����
        last = last->next;
    else
        last = nullptr;//� ��������� �������- ����
    int resp = temp->value;//�������� �������� ���������� ��������
    delete temp;//������� ���
    return resp;//� ���������� ��������� �������
}

bool s_stack::s_empty()
{
    return last == nullptr;//���� ��������� ������� "������"- ������ true
}

class stack
{
private: int size;//������ �����
         int i = 0;//����������, ���������� �� ������� ������� �����
         int *a;//���� � ���� ������������� �������
public: stack(int n);//����������� ��� �������� ����� � ��������������� ��������
      void push(int b);//��������� ������� � ����
      void pop();//����������
      int get();//�������� �������� ���� �����
      int cur();//�������� �������� ���� ����� ��� �������� ��������
      bool empty();//�������� �� ������� �����
      bool full();//�������� �� �������
      void pushNext();//�������� ������������ ��� �������� �������� �� ���������� ��������
      friend void summ(stack st1, stack st2);
};

stack::stack(int n)
{
    size = n;//������
    a = new int[size];//������
    for (int j = 0; j < size; j++)
        a[j] = 0;//�������� ������
}

void stack::push(int b)
{
    a[i] += b;//� �������� ������� ����������� ��������
    i++;//���� ������
}

void stack::pop()
{
    a[i] = -1;//� ����� ������������� ������ �� ����� ���� �������� �� ��������� -1- ������� ��� ���������
    i--;//���� ������
}

int stack::get()
{
    return a[i-1];//������� ��������� �������
}

void stack::pushNext()
{
    a[i] += 1;//���������� 1 � ���������� �������� �����
}

bool stack::empty()
{
    if (i == 0)//���� ��������� ���- ���������� true
        return true;
    else return false;
}

bool stack::full()
{
    if (i == size)//���� ������ ���������� �������� ����� ������� �����- �� �����
        return true;
    else return false;
}

int min(int f, int g)//��������������� ������� ������ �������������
{
    if (f < g)
        return f;
    else 
        return g;
}

int max(int f, int g)//��������������� ������� ������ ������������
{
    if (f > g)
        return f;
    else
        return g;
}

int stack::cur()
{
    return a[i];//���������� ��������� �������
}

void summ(stack st1, stack st2)
{
    int a, b;
    stack st3(max(st1.size, st2.size)+1);//������� ����-���������, ������ �������� �� 1 ������ (��� �������� �������� ����������� ������� ����� �� 1)
    while (st1.empty()==false && st2.empty()==false)//���� ����� �� �����
    {
        a = st1.get();//�������� ������� ��������
        b = st2.get();
        if (a + b > 9)//���� �� ����� ������ 9
        {
            st3.push(a + b - 10);//� ���� ���������� �� �����, �� -10
            st3.pushNext();//� � ��������� ������� ���������� 1 (��� �������� ��������)
        }
        else
            st3.push(a + b);//���� ����� ������- ������ ���������� �� �����
        st1.pop();//����������� ������� �����
        st2.pop();
    }

    while (st1.empty() == false)//���� �������� �������� � ������
    {
        if (st1.get() + st3.cur() > 9)//� ������� �������
        {
            st3.push(st1.get() - 10);//���������� ����� ����� � -10
            st3.pushNext();//� �������� ��������
        }
        else
            st3.push(st1.get());//���� ��� ��������- ������ ����������� ��������� ����� ��������� ����� ����������
        st1.pop();//�������� ����
    }

    while (st2.empty() == false)//����������, ���� "�������" ������
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
        cout << st3.a[i];//���� ��������� ������ �� ����- ������� ���

    for (i--; i >= 0; i--)//� ��� ���� ���������
        cout << st3.a[i];

}

int main()
{
    string number1, number2;//�������� ����� � ��������� ����������

    cin >> number1 >> number2;

    stack st1(number1.size());//������� ����� ��������������� ��������
    stack st2(number2.size());

    s_stack sa, sb;//����� �� �������� ������


   for (int i = 0; i < number1.size(); i++)//� ����� �������� �����, ���������� �� �� ���� char � int
   {
        int ts;
        ts = number1[i] - '0';
        st1.push(ts);//� ������ � ��� �����
        sa.s_push(ts);
   }

   for (int i = 0; i < number2.size(); i++)//���������� �� ������
   {
       int ts;
       ts = number2[i] - '0';
       st2.push(ts);
       sb.s_push(ts);
   }

   s_stack res;//���� �� �������� ������ ����������
   int d = 0;//���������� ��� ��������
   while (!(sa.s_empty() && sb.s_empty()))//���� ����� �� ������
   {
       int f = 0, s = 0;//���������� ��� ��������� ���� �� ������
       if (!sa.s_empty())
           f = sa.s_pop();//�������� �� �������
       if (!sb.s_empty())
           s = sb.s_pop();//� �������
       int t = f + s + d;//����������
       d = t / 10;//� �������� �������, ���� ��� ����� ������ 10
       res.s_push(t % 10);//� ������ ������� �� ������� �� 10
   }

   if (d != 0)
       res.s_push(d);//���� ������� ������� �� ����- ���������� ��� � ����

   while (!res.s_empty())
       cout << res.s_pop();//� ������� ���������

   cout << '\n';

    summ(st1, st2);//��������� ����� �� ����� �� ������������ �������
}