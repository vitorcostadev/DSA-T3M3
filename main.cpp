#include <iostream>
#include <vector> // utilizado para organizar os dados dos arquivos em memória
#include <fstream> // operações I/O
#include <algorithm>
#include <random>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
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

void executeTestAndLog(int n, int org, const vector<int>& baseData, mt19937& g, ofstream& of)
{
    vector<int> simData(baseData.begin(), baseData.begin() + n);

    if (org == 2)
    {
        reverse(simData.begin(), simData.end());
    }
    else if (org == 3)
    {
        shuffle(simData.begin(), simData.end(), g);
    }

    vector<int> dataMerge = simData;
    vector<int> dataShell = simData;
    vector<int> dataHeap = simData;

    Metrics mMerge, mShell, mHeap;

    if (!dataMerge.empty())
    {
        mergeSort(dataMerge, 0, dataMerge.size() - 1, mMerge);
    }

    ShellSort::ordenar(dataShell, mShell);
    heapSort(dataHeap, mHeap);

    size_t maxC = max({mMerge.comparisons, mShell.comparisons, mHeap.comparisons});
    size_t maxM = max({mMerge.movements, mShell.movements, mHeap.movements});

    auto printAndLog = [&](const string& name, const Metrics& m)
    {
        double relC = maxC > 0 ? (m.comparisons * 100.0) / maxC : 0.0;
        double relM = maxM > 0 ? (m.movements * 100.0) / maxM : 0.0;

        cout << left << setw(15) << name
             << right << setw(15) << m.comparisons
             << setw(14) << fixed << setprecision(1) << relC << "%"
             << setw(15) << m.movements
             << setw(14) << fixed << setprecision(1) << relM << "%"
             << endl;

        if (of.is_open())
        {
            of << left << setw(15) << name
               << right << setw(15) << m.comparisons
               << setw(14) << fixed << setprecision(1) << relC << "%"
               << setw(15) << m.movements
               << setw(14) << fixed << setprecision(1) << relM << "%"
               << endl;
        }
    };

    cout << endl
         << "Resultados (N = " << n
         << ", Organizacao = " << getOrgName(org)
         << ") ---" << endl;

    cout << left << setw(15) << "Algoritmo"
         << right << setw(15) << "C(n) Absoluto"
         << setw(15) << "C(n) Rel(%)"
         << setw(15) << "M(n) Absoluto"
         << setw(15) << "M(n) Rel(%)"
         << endl;

    cout << string(75, '-') << endl;

    if (of.is_open())
    {
        of << endl
           << "Resultados (N = " << n
           << ", Organizacao = " << getOrgName(org)
           << ") ---" << endl;

        of << left << setw(15) << "Algoritmo"
           << right << setw(15) << "C(n) Absoluto"
           << setw(15) << "C(n) Rel(%)"
           << setw(15) << "M(n) Absoluto"
           << setw(15) << "M(n) Rel(%)"
           << endl;

        of << string(75, '-') << endl;
    }

    printAndLog("Merge Sort", mMerge);
    printAndLog("Shell Sort", mShell);
    printAndLog("Heap Sort", mHeap);
}

bool isInteger(const string& entrada)
{
    if (entrada.empty())
        return false;

    size_t inicio = 0;

    if (entrada[0] == '-')
    {
        if (entrada.size() == 1)
            return false;

        inicio = 1;
    }

    for (size_t i = inicio; i < entrada.size(); i++)
    {
        if (!isdigit(entrada[i]))
            return false;
    }

    return true;
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

    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    int year = localTime->tm_year + 1900;
    int month = localTime->tm_mon + 1;
    int day = localTime->tm_mday;

    cout << "=== Analise de Ordenacao ===" << endl;
    cout << "Informe o diretorio do arquivo (ex: C:/dados/ ou deixe em branco para criar um no diretório raiz): ";
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

    stringstream ss;
    ss << "metrics_"
       << year << "-"
       << setfill('0') << setw(2) << month << "-"
       << setfill('0') << setw(2) << day
       << ".txt";

    string outFilename = ss.str();



    if (!path.empty()) {
        outFilename = path + outFilename;
    }

    ifstream if_(outFilename, ios::ate);

    if(if_.tellg() != 0){
        ofstream(outFilename, ios::trunc).close(); // limpa o arquivo de metrics antes de povoar novamente
        if_.close();
    }

    ofstream of(outFilename, ios::app);

    if (!of.is_open()) {
        cerr << "Nao foi possivel abrir o arquivo de log: " << outFilename << endl;
        return 1;
    }

    random_device rd;
    mt19937 g(rd());
    string modo;

    do {
        do{
            cout << endl << "=== Simulação dos algoritimos de ordenação ===" << endl;
            cout << "[1] Executar Testes Manuais (Simulação Individual)" << endl;
            cout << "[2] Executar Testes Automáticos" << endl;
            cout << "[0] Sair" << endl;
            cout << ": ";
            cin >> modo;

            if(!isInteger(modo)) cout << "Numero digitado é inválido, tente novamente." << endl;
        }while(!isInteger(modo));

        int modo_cast = stoi(modo);

        switch(modo_cast)
        {
            case 0: {break;}

            case 1:
                {
                    int n, org;
                    cout << endl << "Quantidade de dados a ordenar (1 a " << baseData.size() << "): ";
                    cin >> n;
                    if (n < 1 || n > baseData.size()) n = baseData.size();

                    cout << "Organizacao inicial dos dados:" << endl;
                    cout << "[1] : Crescente (Ascendente)" << endl;
                    cout << "[2] : Decrescente (Descendente)" << endl;
                    cout << "[3] : Aleatoria" << endl;
                    cout << ": ";
                    cin >> org;

                    executeTestAndLog(n, org, baseData, g, of);
                    break;
                }
            case 2:
                {
                    vector<int> tamanhos = {100, 500, 1000, 5000, 10000};

                    for (int org = 1; org <= 3; ++org) {
                        for (int n : tamanhos) {
                            if (n > baseData.size()) n = baseData.size();
                            executeTestAndLog(n, org, baseData, g, of);
                        }
                    }
                    break;
                }
            default: {cerr << "Opção digitada não existe." << endl;}
        }
    } while (modo != "0");

    if (of.is_open()) {of.close();}

    return 0;
}
