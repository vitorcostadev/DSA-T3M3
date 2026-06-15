#include <iostream>
#include <vector> // utilizado para organizar os dados dos arquivos em memória
#include <fstream> // operações I/O
#include <algorithm>
#include <random>
#include <string>
#include <chrono> // acessar a data do sistema para salvar os resultados em arquivos txt (requer c++20)
#include <iomanip>
#include "Mergesort.h"
#include "ShellSort.h"
#include "HeapSort.h"

using namespace std;

/*
Trabalho feito por Vitor K Costa, Arthur Abreu e Fernando Nunes

Cada integrante ficou responsável por implementar um dos três algoritimos de ordenação, que foram
utilizados na produção deste programa de testes.

Existem três relatórios (um sobre cada algoritimo de ordenação) e mais um que é em relação a simulação completa
dos três algoritimos, todos estão na pasta data/ que foi junto do arquivo zipado.
*/

void generateTestFile(const string& filepath, int quantity) {
    ofstream file(filepath);
    if (file.is_open()) {
        for (int i = 1; i <= quantity; ++i) {
            file << i << endl;
        }
        file.close();
        cout << "Arquivo " << filepath << " gerado com sucesso com " << quantity << " dados crescentes." << endl;
    }
}

string getOrgName(int org) {
    if (org == 1) return "Crescente";
    if (org == 2) return "Decrescente";
    return "Aleatoria";
}

void executeTestAndLog(int n, int org, const vector<int>& baseData, mt19937& g, ofstream& of) {
    vector<int> simData(baseData.begin(), baseData.begin() + n);

    if (org == 2) {
        reverse(simData.begin(), simData.end());
    } else if (org == 3) {
        shuffle(simData.begin(), simData.end(), g);
    }

    vector<int> dataMerge = simData;
    vector<int> dataShell = simData;
    vector<int> dataHeap = simData;

    Metrics mMerge, mShell, mHeap;

    mergeSort(dataMerge, 0, static_cast<int>(dataMerge.size()) - 1, mMerge);
    ShellSort::ordenar(dataShell, mShell);
    heapSort(dataHeap, mHeap);

    unsigned long long maxC = max({mMerge.comparisons, mShell.comparisons, mHeap.comparisons});
    unsigned long long maxM = max({mMerge.movements, mShell.movements, mHeap.movements});

    auto printAndLog = [&](const string& name, Metrics m) {
        double relC = maxC > 0 ? (m.comparisons / static_cast<double>(maxC)) * 100.0 : 0.0;
        double relM = maxM > 0 ? (m.movements / static_cast<double>(maxM)) * 100.0 : 0.0;

        cout << left << setw(15) << name
             << right << setw(15) << m.comparisons << setw(14) << fixed << setprecision(1) << relC << "%"
             << setw(15) << m.movements << setw(14) << fixed << setprecision(1) << relM << "%" << endl;

        if (of.is_open()) {
            of << left << setw(15) << name
               << right << setw(15) << m.comparisons << setw(14) << fixed << setprecision(1) << relC << "%"
               << setw(15) << m.movements << setw(14) << fixed << setprecision(1) << relM << "%" << endl;
        }
    };

    cout << endl << "Resultados (N = " << n << ", Organizacao = " << getOrgName(org) << ") ---" << endl;
    cout << left << setw(15) << "Algoritmo"
         << right << setw(15) << "C(n) Absoluto" << setw(15) << "C(n) Rel(%)"
         << setw(15) << "M(n) Absoluto" << setw(15) << "M(n) Rel(%)" << endl;
    cout << string(75, '-') << endl;

    if (of.is_open()) {
        of << endl << "Resultados (N = " << n << ", Organizacao = " << getOrgName(org) << ") ---" << endl;
        of << left << setw(15) << "Algoritmo"
           << right << setw(15) << "C(n) Absoluto" << setw(15) << "C(n) Rel(%)"
           << setw(15) << "M(n) Absoluto" << setw(15) << "M(n) Rel(%)" << endl;
        of << string(75, '-') << endl;
    }

    printAndLog("Merge Sort", mMerge);
    printAndLog("Shell Sort", mShell);
    printAndLog("Heap Sort", mHeap);
}

/*
Este main realiza testes manuais e automáticos, e salva-os sempre um arquivo de log, utilizado para gerar o relatório final
que sempre será salvo na pasta principal do projeto com o nome "metrics_year-month-day.txt".

Logo acima temos 3 subrotinas complementares:

generateTestFile : responsável por gerar o arquivo de testes, que foi solicitado.
getOrgName : Retorna o tipo de ordenação dos dados, criado apenas para não ficar repetindo a mesma coisa.
executeTestAndLog : Rotina principal, é a que vai executar os testes e salvar no arquivo de log.
*/
int main() {
    string path, filename, fullpath;

    auto now = chrono::system_clock::now();
    auto days = chrono::floor<chrono::days>(now);
    chrono::year_month_day ymd(days);

    cout << "=== Analise de Ordenacao ===" << endl;
    cout << "Informe o diretorio do arquivo (ex: C:/dados/ ou deixe em branco): ";
    getline(cin, path);
    cout << "Informe o nome do arquivo de leitura (ex: merge.txt): ";
    getline(cin, filename);

    fullpath = path + filename;

    ifstream infile(fullpath);
    if (!infile.is_open()) {
        cerr << "Arquivo nao encontrado. Gerando arquivo padrao em: " << filename << endl;
        fullpath = filename;
        generateTestFile(fullpath, 10000);
        infile.open(fullpath);
    }

    vector<int> baseData;
    int value;
    while (infile >> value && baseData.size() < 10000) {
        baseData.push_back(value);
    }
    infile.close();

    if (baseData.empty()) {
        cerr << "Arquivo vazio ou dados invalidos." << endl;
        return 1;
    }

    string outFilename = "metrics_" +
                         to_string(int(ymd.year())) + "-" +
                         to_string(unsigned(ymd.month())) + "-" +
                         to_string(unsigned(ymd.day())) + ".txt";

    if (!path.empty()) {
        outFilename = path + outFilename;
    }

    ofstream of(outFilename, ios::app);
    if (!of.is_open()) {
        cerr << "Nao foi possivel abrir o arquivo de log: " << outFilename << endl;
        return 1;
    }

    random_device rd;
    mt19937 g(rd());
    int modo;

    do {
        cout << endl << "=== Simulação dos algoritimos de ordenação ===" << endl;
        cout << "[1] Executar Testes Manuais (Simulação Individual)" << endl;
        cout << "[2] Executar Testes Automáticos" << endl;
        cout << "[0] Sair" << endl;
        cout << ": ";
        cin >> modo;

        if (modo == 1) {
            int n, org;
            cout << endl << "Quantidade de dados a ordenar (1 a " << baseData.size() << "): ";
            cin >> n;
            if (n < 1 || n > static_cast<int>(baseData.size())) n = static_cast<int>(baseData.size());

            cout << "Organizacao inicial dos dados:" << endl;
            cout << "[1] : Crescente (Ascendente)" << endl;
            cout << "[2] : Decrescente (Descendente)" << endl;
            cout << "[3] : Aleatoria" << endl;
            cout << ": ";
            cin >> org;

            executeTestAndLog(n, org, baseData, g, of);

        } else if (modo == 2) {
            vector<int> tamanhos = {100, 500, 1000, 5000, 10000};

            for (int org = 1; org <= 3; ++org) {
                for (int n : tamanhos) {
                    if (n > static_cast<int>(baseData.size())) n = static_cast<int>(baseData.size());
                    executeTestAndLog(n, org, baseData, g, of);
                }
            }
            cout << endl << "Simulação automática finalizada, resultado foi salvo em " << outFilename << endl;
        }

    } while (modo != 0);

    if (of.is_open()) {
        of.close();
    }

    return 0;
}
