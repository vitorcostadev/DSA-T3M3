#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include <string>
#include "Mergesort.h"
#include "ShellSort.h"
#include "HeapSort.h"

using namespace std;

int main() {
    string path, filename, fullpath;

    cout << "=== Analise de Ordenacao ===\n";
    cout << "Informe o diretorio do arquivo (ex: C:/dados/ ou deixe em branco para o diretorio atual): ";
    getline(cin, path);
    cout << "Informe o nome do arquivo (ex: merge.txt): ";
    getline(cin, filename);

    fullpath = path + filename;

    ifstream infile(fullpath);
    if (!infile.is_open()) {
        cerr << "Arquivo nao encontrado. Gerando arquivo padrao em: " << filename << "\n";
        fullpath = filename;
        generateTestFile(fullpath);
        infile.open(fullpath);
    }

    vector<int> baseData;
    int value;
    while (infile >> value && baseData.size() < 10000) {
        baseData.push_back(value);
    }
    infile.close();

    if (baseData.empty()) {
        cerr << "Arquivo vazio ou dados invalidos.\n";
        return 1;
    }

    int n, org;
    char continuar;
    random_device rd;
    mt19937 g(rd());

    do {
        cout << "\n--- Nova Simulacao ---\n";
        cout << "Quantidade de dados a ordenar (1 a " << baseData.size() << "): ";
        cin >> n;

        if (n < 1 || n > static_cast<int>(baseData.size())) n = static_cast<int>(baseData.size());

        cout << "Organizacao inicial dos dados:\n";
        cout << "1 - Crescente (Ascendente)\n";
        cout << "2 - Decrescente (Descendente)\n";
        cout << "3 - Aleatoria\n";
        cout << "Opcao: ";
        cin >> org;

        int op;
        cout << "Qual algoritmo de ordenacao deseja usar para esta simulacao?\n";
        cout << "1 - Merge Sort\n";
        cout << "2 - Shell Sort\n";
        cout << "3 - Heap Sort\n";
        cout << "Opcao: ";
        cin >> op;

        vector<int> simData(baseData.begin(), baseData.begin() + n);

        if (org == 2) {
            reverse(simData.begin(), simData.end());
        } else if (org == 3) {
            shuffle(simData.begin(), simData.end(), g);
        }

        Metrics metrics;
        metrics.comparisons = 0;
        metrics.movements = 0;

        string algorithmName = "Desconhecido";
        if (op == 1) {
            algorithmName = "Merge Sort";
            mergeSort(simData, 0, static_cast<int>(simData.size()) - 1, metrics);
        } else if (op == 2) {
            algorithmName = "Shell Sort";
            ShellSort::ordenar(simData, metrics);
        } else if (op == 3) {
            algorithmName = "Heap Sort";
            heapSort(simData, metrics);
        }

        cout << "\n--- Resultados da Simulacao ---\n";
        cout << algorithmName << "\n";
        cout << "Tamanho de Entrada (N): " << n << "\n";
        cout << "Comparacoes C(n): " << metrics.comparisons << "\n";
        cout << "Movimentacoes M(n): " << metrics.movements << "\n";

        cout << "\nDeseja realizar outra simulacao? (S/N): ";
        cin >> continuar;

    } while (continuar == 'S' || continuar == 's');

    return 0;
}
