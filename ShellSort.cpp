#include <cstdlib>
#include <iomanip>
#include <iostream>
#include "ShellSort.h"

using namespace std;

inline void ShellSort::ordenar(int v[], int n, long long &c, long long &m) {
    int intervalo, i, j, aux;

    for (intervalo = n / 2; intervalo > 0; intervalo = intervalo / 2) {
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
                j = j - intervalo;
            }

            v[j] = aux;
            m++;
        }
    }
}

void ShellSort::ordenar(std::vector<int>& arr, Metrics& metrics) {
    if (arr.empty()) return;
    long long c = 0, m = 0;
    ordenar(arr.data(), static_cast<int>(arr.size()), c, m);
    metrics.comparisons = static_cast<unsigned long long>(c);
    metrics.movements = static_cast<unsigned long long>(m);
}

int ShellSort::estaOrdenado(int v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (v[i] > v[i + 1]) {
            return 0;
        }
    }

    return 1;
}

void ShellSort::montarVetor(int dados[], int v[], int n, int tipo) {
    int i;

    if (tipo == 1) {
        for (i = 0; i < n; i++) {
            v[i] = dados[i];
        }
    } else if (tipo == 2) {
        for (i = 0; i < n; i++) {
            v[i] = dados[n - 1 - i];
        }
    } else {
        for (i = 0; i < n; i++) {
            v[i] = dados[i];
        }

        srand(static_cast<unsigned int>(10 + n));
        for (i = n - 1; i > 0; i--) {
            int pos = rand() % (i + 1);
            int troca = v[i];
            v[i] = v[pos];
            v[pos] = troca;
        }
    }
}

void ShellSort::mostrarTipo(int tipo) {
    if (tipo == 1) {
        cout << "crescente";
    } else if (tipo == 2) {
        cout << "decrescente";
    } else {
        cout << "aleatoria";
    }
}

void ShellSort::fazerTeste(int dados[], int quantidade, int tipo) {
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
    } else {
        cout << "nao\n";
    }

    cout << "Valor relativo de C(n): 100%\n";
    cout << "Valor relativo de M(n): 100%\n";
}

void ShellSort::testesAutomaticos(int dados[]) {
    int quantidades[5] = {100, 500, 1000, 5000, 10000};
    int tipo, quantidade;

    cout << "\nTestes automaticos\n";
    cout << left << setw(14) << "Tipo"
         << right << setw(10) << "Qtd"
         << setw(15) << "C(n)"
         << setw(15) << "M(n)" << endl;
    cout << "------------------------------------------------------\n";

    for (tipo = 1; tipo <= 3; tipo++) {
        for (int i = 0; i < 5; i++) {
            int v[10000];
            long long c = 0;
            long long m = 0;

            quantidade = quantidades[i];
            montarVetor(dados, v, quantidade, tipo);
            ordenar(v, quantidade, c, m);

            cout << left << setw(14);
            mostrarTipo(tipo);
            cout << right << setw(10) << quantidade
                 << setw(15) << c
                 << setw(15) << m << endl;
        }
    }
}
