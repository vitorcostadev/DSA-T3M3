#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <cstdlib>
#include <vector>

struct Metrics;

// Implementado por: Fernando Nunes
void heapify(int v[], size_t n, size_t raiz,
             long long& c, long long& m)
{
    size_t maior = raiz;

    size_t esq = 2 * raiz + 1;
    size_t dir = 2 * raiz + 2;

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

void heapSort(int v[], size_t n,
              long long& c, long long& m)
{
    if (n <= 1)
    {
        return;
    }

    for (size_t i = n / 2; i > 0; i--)
    {
        heapify(v, n, i - 1, c, m);
    }

    for (size_t i = n - 1; i > 0; i--)
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
    if (arr.empty())
    {
        return;
    }

    long long c = 0;
    long long m = 0;

    heapSort(arr.data(), arr.size(), c, m);

    metrics.comparisons = c;
    metrics.movements = m;
}

int estaOrdenado(int v[], size_t n)
{
    if (n <= 1)
    {
        return 1;
    }

    for (size_t i = 0; i < n - 1; i++)
    {
        if (v[i] > v[i + 1])
        {
            return 0;
        }
    }

    return 1;
}

void montarVetor(int dados[], int v[], size_t n, int tipo)
{
    size_t i;

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

        srand(10 + n);

        for (i = n - 1; i > 0; i--)
        {
            size_t pos = rand() % (i + 1);

            int aux = v[i];
            v[i] = v[pos];
            v[pos] = aux;
        }
    }
}

string nomeTipo(int tipo)
{
    if (tipo == 1)
        return "crescente";

    if (tipo == 2)
        return "decrescente";

    return "aleatoria";
}

#endif
