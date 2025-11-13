#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include "Visualizer.hpp"

namespace QuickSort
{
    void sort(Visualizer &viz);
    void quickSort(std::vector<Bar> &bars, int low, int high, Visualizer &viz);
    int partition(std::vector<Bar> &bars, int low, int high, Visualizer &viz);
}

#endif