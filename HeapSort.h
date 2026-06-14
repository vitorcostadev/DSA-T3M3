#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <cstdlib>
#include <vector>
struct Metrics;

// Implementado por: Fernando Nunes
void heapify(int v[], int n, int raiz,
             long long &c, long long &m)
{
    int maior = raiz;

    int esq = 2 * raiz + 1;
    int dir = 2 * raiz + 2;

    if (esq < n)
    {
        c++;

        if (v[esq] > v[maior])
        {
            maior = esq;
        }
    }

    if (dir < n)
    {
        c++;

        if (v[dir] > v[maior])
        {
            maior = dir;
        }
    }

    if (maior != raiz)
    {
        int aux = v[raiz];
        m++;

        v[raiz] = v[maior];
        m++;

        v[maior] = aux;
        m++;

        heapify(v, n, maior, c, m);
    }
}

void heapSort(int v[], int n,
              long long &c, long long &m)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(v, n, i, c, m);
    }

    for (int i = n - 1; i > 0; i--)
    {
        int aux = v[0];
        m++;

        v[0] = v[i];
        m++;

        v[i] = aux;
        m++;

        heapify(v, i, 0, c, m);
    }
}

inline void heapSort(std::vector<int>& arr, Metrics& metrics)
{
    if (arr.empty()) return;
    long long c = 0, m = 0;
    heapSort(arr.data(), static_cast<int>(arr.size()), c, m);
    metrics.comparisons = static_cast<unsigned long long>(c);
    metrics.movements = static_cast<unsigned long long>(m);
}

int estaOrdenado(int v[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (v[i] > v[i + 1])
        {
            return 0;
        }
    }

    return 1;
}

void montarVetor(int dados[],int v[],int n,int tipo)
{
    int i;

    if (tipo == 1)
    {
        for (i = 0; i < n; i++)
        {
            v[i] = dados[i];
        }
    }
    else if (tipo == 2)
    {
        for (i = 0; i < n; i++)
        {
            v[i] = dados[n - 1 - i];
        }
    }
    else
    {
        for (i = 0; i < n; i++)
        {
            v[i] = dados[i];
        }

        srand(static_cast<unsigned int>(10 + n));

        for (i = n - 1; i > 0; i--)
        {
            int pos = rand() % (i + 1);

            int aux = v[i];
            v[i] = v[pos];
            v[pos] = aux;
        }
    }
}

const char* nomeTipo(int tipo)
{
    if (tipo == 1)
        return "crescente";

    if (tipo == 2)
        return "decrescente";

    return "aleatoria";
}

#endif
