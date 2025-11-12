#include "../include/MergeSort.hpp"
#include <SFML/System/Sleep.hpp>

namespace MergeSort
{
    void merge(Visualizer &viz, int left, int mid, int right);
    void sortRecursive(Visualizer &viz, int left, int right);

    void sort(Visualizer &viz) // <-- new wrapper
    {
        auto &bars = viz.getBars();
        if (bars.empty())
            return;
        sortRecursive(viz, 0, bars.size() - 1);
    }

    void sortRecursive(Visualizer &viz, int left, int right)
    {
        if (left >= right)
            return;

        int mid = left + (right - left) / 2;
        sortRecursive(viz, left, mid);
        sortRecursive(viz, mid + 1, right);
        merge(viz, left, mid, right);
    }

    void merge(Visualizer &viz, int left, int mid, int right)
    {
        auto &bars = viz.getBars();

        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<float> L(n1), R(n2);
        for (int i = 0; i < n1; ++i)
            L[i] = bars[left + i].getHeight();
        for (int j = 0; j < n2; ++j)
            R[j] = bars[mid + 1 + j].getHeight();

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2)
        {
            viz.highlightBars(left + i, mid + 1 + j, sf::Color(255, 255, 100));
            viz.renderFrame();
            sf::sleep(sf::milliseconds(30));

            if (L[i] <= R[j])
                bars[k++].setHeight(L[i++]);
            else
                bars[k++].setHeight(R[j++]);
        }

        while (i < n1)
        {
            bars[k++].setHeight(L[i++]);
            viz.renderFrame();
            sf::sleep(sf::milliseconds(30));
        }
        while (j < n2)
        {
            bars[k++].setHeight(R[j++]);
            viz.renderFrame();
            sf::sleep(sf::milliseconds(30));
        }

        viz.resetBarColors();
    }
}
