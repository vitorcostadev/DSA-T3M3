#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <string>

struct Metrics {
    unsigned long long comparisons = 0;
    unsigned long long movements = 0;
};

void merge(std::vector<int>& arr, int left, int mid, int right, Metrics& metrics) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(static_cast<std::size_t>(n1));
    std::vector<int> R(static_cast<std::size_t>(n2));

    for (int i = 0; i < n1; ++i) {
        L[static_cast<std::size_t>(i)] = arr[static_cast<std::size_t>(left + i)];
        metrics.movements++;
    }
    for (int j = 0; j < n2; ++j) {
        R[static_cast<std::size_t>(j)] = arr[static_cast<std::size_t>(mid + 1 + j)];
        metrics.movements++;
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        metrics.comparisons++;
        if (L[static_cast<std::size_t>(i)] <= R[static_cast<std::size_t>(j)]) {
            arr[static_cast<std::size_t>(k)] = L[static_cast<std::size_t>(i)];
            i++;
        } else {
            arr[static_cast<std::size_t>(k)] = R[static_cast<std::size_t>(j)];
            j++;
        }
        metrics.movements++;
        k++;
    }

    while (i < n1) {
        arr[static_cast<std::size_t>(k)] = L[static_cast<std::size_t>(i)];
        i++;
        k++;
        metrics.movements++;
    }

    while (j < n2) {
        arr[static_cast<std::size_t>(k)] = R[static_cast<std::size_t>(j)];
        j++;
        k++;
        metrics.movements++;
    }
}

void mergeSort(std::vector<int>& arr, int left, int right, Metrics& metrics) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, metrics);
        mergeSort(arr, mid + 1, right, metrics);
        merge(arr, left, mid, right, metrics);
    }
}

void generateTestFile(const std::string& filepath) {
    std::ofstream file(filepath);
    if (file.is_open()) {
        for (int i = 1; i <= 10000; ++i) {
            file << i << "\n";
        }
        file.close();
        std::cout << "Arquivo " << filepath << " gerado com sucesso com 10.000 dados crescentes.\n";
    }
}
