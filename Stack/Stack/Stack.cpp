#include <iostream>
#include <string>
#include <cmath>

using namespace std;

struct node
{
    node* next = NULL;//указатель на следующий элемент
    int value;//значение элемента
    node(int data);//конструктор
};

struct stack
{
public:
    node* last = NULL;//указатель на последний элемент
    void s_push(int data);//втолкнуть значение в стек
    int s_pop();//вытолкнуть и вернуть значения последнего элемента
};

node::node(int data)
{
    value = data;//присвоить значение
    next = NULL;//следующего элемента нет
}

void stack::s_push(int data)
{
    node* n = new node(data);//новый элемент
    n->next = last;//указатель на следующий элемент- на последний
    last = n;//новый элемент становится последним
}

int stack::s_pop()
{
    node* temp = last;//временный элемент, равный последнему
    if (last->next != NULL)//идем до конца стека
        last = last->next;
    else
        last = NULL;//и последний элемент- нуль
    int result = temp->value;//получаем значение последнего элемента
    delete temp;//удаляем его
    return result;//и возвращаем последний элемент
}

int main()
{
    stack st1; //объект для стека
    string equasion, part; //строковые переменные- equasion для обратной польской записи, записанной через пробел, part- часть выражения
    setlocale(LC_CTYPE, "rus");
    bool flag = true;
    
    while (true)
    {
        cout << "Введите выражение в виде обратной польской записи, где операнды перечислены через пробел\n";

        getline(cin, equasion); //получаем выражение

        int op = 0, zn = 0; //переменные для высчитывания некорректности
        flag = true;

        for (int i = 0; i < equasion.length(); i++)
        {
            if ((equasion[i] == '+') || (equasion[i] == '-') || (equasion[i] == '*') || (equasion[i] == '/'))
                zn++;
            else
                if ((equasion[i] == '0') || (equasion[i] == '1') || (equasion[i] == '2') || (equasion[i] == '3') || (equasion[i] == '4') || (equasion[i] == '5') || (equasion[i] == '6') || (equasion[i] == '7') || (equasion[i] == '8') || (equasion[i] == '9'))
                    op++;
                else
                    if (equasion[i] != ' ')
                    {
                        cout << "Введено неккоректное выражение\n";
                        flag = false;
                        break;
                    }
        }

        if (flag == false) //если введен символ
            continue;

        if (zn + 1 != op) //нарушен баланс знаков/чисел
        {
            cout << "Введено неккоректное выражение\n";
            continue;
        }

        while (equasion.length() != 0) //в дальнейшем мы будем "вырезать" части строки, поэтому цикл выполняется пока строка есть
        {
            int space = equasion.find(' '); //ищем пробел в строке
            if (space == -1) //если пробел не найден- мы прошли до конца выражения, остался последний знак, который мы получаем в переменную check, а размер equasion сводится к 0
            {
                part = equasion.substr(0, equasion.length());
                equasion.erase(0, equasion.length());
            }
            else //иначе- вы вычленяем операнд
            {
                part = equasion.substr(0, space);
                equasion.erase(0, space + 1);
            }

            if (part[0] == '+') //проверяем в 4 if-else полученную подстроку- не является ли она операцией, если да- выполянем ее, результат- обратно в стек
                st1.s_push(st1.s_pop() + st1.s_pop());
            else
                if (part[0] == '-')
                {
                    int temp = st1.s_pop();
                    st1.s_push(st1.s_pop() - temp);
                }
                else
                    if (part[0] == '*')
                        st1.s_push(st1.s_pop() * st1.s_pop());
                    else
                        if (part[0] == '/')
                        {
                            int temp = st1.s_pop();
                            st1.s_push(st1.s_pop() / temp);
                        }
                        else //иначе- у нас число, которое нужно правильно получить и записать в стек
                        {
                            int number = 0, power = 0; //number- само число, power- степень числа 10, на которую мы будем домножать цифры исходного числа, чтобы получить верно число, так как будем идти с конца
                            for (int j = part.length() - 1; j >= 0; j--)
                            {
                                number += (part[j] - '0') * pow(10, power);
                                power++;
                            }
                            st1.s_push(number); //и запись полученного числа- в стек
                        }
        }

        cout << "Результат выражения: " << st1.s_pop(); //вывод результата
        return 0;
    }
}