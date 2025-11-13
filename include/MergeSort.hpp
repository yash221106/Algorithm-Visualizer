#ifndef MERGESORT_HPP
#define MERGESORT_HPP

#include "Visualizer.hpp"

namespace MergeSort
{
    void sort(Visualizer &viz);
    void mergeSort(std::vector<Bar> &bars, int left, int right, Visualizer &viz);
    void merge(std::vector<Bar> &bars, int left, int mid, int right, Visualizer &viz);
}

#endif