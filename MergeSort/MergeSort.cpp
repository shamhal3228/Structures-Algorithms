#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void merge(int* A, int nA, int* B, int nB, int* C)
{
    int a = 0, b = 0;

    while (a + b < nA + nB)
    {
        if ((b >= nB) || ((a < nA) && (A[a] <= B[b])))
        {
            C[a + b] = A[a];
            a++;
        }
        else {
            C[a + b] = B[b];
            b++;
        }
    }
}

void natural(int* A, int n)
{
    float start = clock();
    int* B = new int[n];

    while (true)
    {
        int start1, end1, //Первый отсортированный участок
            start2 = -1, end2 = -1;//Второй отсортированный участок

        while (true)
        {
            //Начало первого участка для слияния находится после конца второго участка предыдущей пары:
            start1 = end2 + 1;
            end1 = start1;
            //Двигаемся вправо до нарушения сортировки:
            while ((end1 < n - 1) && (A[end1] <= A[end1 + 1]))
                end1++;
            //Первый участок пары простирается до конца массива:
            if (end1 == n - 1)
                break;
            //Начало второго участка для слияния находится после конца первого участка текущей пары:
            start2 = end1 + 1;
            end2 = start2;
            //Двигаемся вправо до нарушения сортировки:
            while ((end2 < n - 1) && (A[end2] <= A[end2 + 1]))
                end2++;

            //Выполняем слияние двух отсортированных участков
            merge(A + start1, end1 - start1 + 1, A + start2, end2 - start2 + 1, B + start1);

            //Второй участок пары простирается до конца массива:
            if (end2 == n - 1)
                break;
        }

        //Данные полностью отсортированы и находятся в массиве A:
        if ((start1 == 0) && (end1 == n - 1))
            break;

        //Если последний кусочек остался без пары, просто копируем его из A в B:
        if (end1 == n - 1)
            for (start1; start1 < n; ++start1)
                B[start1] = A[start1];

        int* temp = B;
        B = A;
        A = temp;
    }
    float end = clock();
    cout << end - start;
    delete[n] B;
}

int main()
{
    int* a = new int[1000];
    for (int i = 0; i < 1000; i++)
        a[i] = rand();
    natural(a, 1000);
}