#ifndef SHELLSORT_H
#define SHELLSORT_H

#include <vector>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include "Mergesort.h"

using namespace std;

// Implementado por: Arthur Abreu
class ShellSort {
public:
    static inline void ordenar(int v[], size_t n, long long& c, long long& m) {
        size_t intervalo, i, j;
        int aux;

        for (intervalo = n / 2; intervalo > 0; intervalo /= 2) {
            for (i = intervalo; i < n; i++) {
                aux = v[i];
                m++;

                j = i;

                while (j >= intervalo) {
                    c++;

                    if (v[j - intervalo] <= aux) {
                        break;
                    }

                    v[j] = v[j - intervalo];
                    m++;

                    j -= intervalo;
                }

                v[j] = aux;
                m++;
            }
        }
    }

    static inline void ordenar(vector<int>& arr, Metrics& metrics) {
        if (arr.empty()) {
            return;
        }

        long long c = 0;
        long long m = 0;

        ordenar(arr.data(), arr.size(), c, m);

        metrics.comparisons = c;
        metrics.movements = m;
    }

    static inline int estaOrdenado(int v[], size_t n) {
        for (size_t i = 0; i < n - 1; i++) {
            if (v[i] > v[i + 1]) {
                return 0;
            }
        }

        return 1;
    }

    static inline void montarVetor(int dados[], int v[], size_t n, int tipo) {
        size_t i;

        if (tipo == 1) {
            for (i = 0; i < n; i++) {
                v[i] = dados[i];
            }
        }
        else if (tipo == 2) {
            for (i = 0; i < n; i++) {
                v[i] = dados[n - 1 - i];
            }
        }
        else {
            for (i = 0; i < n; i++) {
                v[i] = dados[i];
            }

            srand(10 + n);

            for (i = n - 1; i > 0; i--) {
                size_t pos = rand() % (i + 1);

                int troca = v[i];
                v[i] = v[pos];
                v[pos] = troca;
            }
        }
    }

    static inline void mostrarTipo(int tipo) {
        if (tipo == 1) {
            cout << "crescente";
        }
        else if (tipo == 2) {
            cout << "decrescente";
        }
        else {
            cout << "aleatoria";
        }
    }

    static inline void fazerTeste(int dados[], int quantidade, int tipo) {
        int v[10000];
        long long c = 0;
        long long m = 0;

        montarVetor(dados, v, quantidade, tipo);
        ordenar(v, quantidade, c, m);

        cout << "\nTipo inicial: ";
        mostrarTipo(tipo);

        cout << "\nQuantidade: " << quantidade;
        cout << "\nC(n): " << c;
        cout << "\nM(n): " << m;
        cout << "\nOrdenado: ";

        if (estaOrdenado(v, quantidade)) {
            cout << "sim\n";
        }
        else {
            cout << "nao\n";
        }

        cout << "Valor relativo de C(n): 100%\n";
        cout << "Valor relativo de M(n): 100%\n";
    }

    static inline void testesAutomaticos(int dados[]) {
        int quantidades[5] = {100, 500, 1000, 5000, 10000};

        cout << "\nTestes automaticos\n";
        cout << left << setw(14) << "Tipo"
             << right << setw(10) << "Qtd"
             << setw(15) << "C(n)"
             << setw(15) << "M(n)" << endl;

        cout << "------------------------------------------------------\n";

        for (int tipo = 1; tipo <= 3; tipo++) {
            for (int i = 0; i < 5; i++) {
                int v[10000];
                long long c = 0;
                long long m = 0;

                int quantidade = quantidades[i];

                montarVetor(dados, v, quantidade, tipo);
                ordenar(v, quantidade, c, m);

                cout << left << setw(14);
                mostrarTipo(tipo);

                cout << right << setw(10) << quantidade
                     << setw(15) << c
                     << setw(15) << m
                     << endl;
            }
        }
    }
};

#endif
