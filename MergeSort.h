#pragma once
#include <iostream>
#include <vector>
#include <string>

// Implementado por: Vitor Costa
struct Metrics {
    size_t comparisons = 0;
    size_t movements = 0;
};

void merge(std::vector<int>& arr, int left, int mid, int right, Metrics& metrics)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1);
    std::vector<int> R(n2);

    for (int i = 0; i < n1; ++i)
    {
        L[i] = arr[left + i];
        metrics.movements++;
    }

    for (int j = 0; j < n2; ++j)
    {
        R[j] = arr[mid + 1 + j];
        metrics.movements++;
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        metrics.comparisons++;

        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }

        metrics.movements++;
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
        metrics.movements++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
        metrics.movements++;
    }
}

void mergeSort(std::vector<int>& arr, int left, int right, Metrics& metrics)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid, metrics);
        mergeSort(arr, mid + 1, right, metrics);

        merge(arr, left, mid, right, metrics);
    }
}
