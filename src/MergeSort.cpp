#include "../include/MergeSort.hpp"
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <vector>

namespace MergeSort
{

    void merge(std::vector<Bar> &bars, int left, int mid, int right, Visualizer &viz)
    {
        auto &stats = viz.getStats();
        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<float> leftHeights;
        std::vector<float> rightHeights;

        for (int i = 0; i < n1; ++i)
        {
            stats.incrementArrayAccesses();
            viz.renderFrame();
            leftHeights.push_back(bars[left + i].getHeight());
            viz.highlightBars(left + i, -1, sf::Color(100, 100, 255));
        }

        for (int i = 0; i < n2; ++i)
        {
            stats.incrementArrayAccesses();
            viz.renderFrame();
            rightHeights.push_back(bars[mid + 1 + i].getHeight());
            viz.highlightBars(mid + 1 + i, -1, sf::Color(150, 100, 255));
        }

        viz.renderFrame();
        sf::sleep(sf::milliseconds(100));

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2)
        {
            stats.incrementComparisons();
            stats.incrementArrayAccesses();
            viz.renderFrame();

            viz.highlightBars(k, -1, sf::Color(255, 255, 100));
            viz.renderFrame();
            sf::sleep(sf::milliseconds(30));

            if (leftHeights[i] <= rightHeights[j])
            {
                stats.incrementArrayAccesses();
                viz.renderFrame();
                bars[k].setHeight(leftHeights[i]);
                viz.highlightBars(k, -1, sf::Color(100, 255, 100));
                i++;
            }
            else
            {
                stats.incrementArrayAccesses();
                viz.renderFrame();
                bars[k].setHeight(rightHeights[j]);
                viz.highlightBars(k, -1, sf::Color(100, 255, 100));
                j++;
            }

            viz.renderFrame();
            sf::sleep(sf::milliseconds(30));
            k++;
        }

        while (i < n1)
        {
            stats.incrementArrayAccesses();
            viz.renderFrame();
            bars[k].setHeight(leftHeights[i]);
            viz.highlightBars(k, -1, sf::Color(100, 255, 100));
            viz.renderFrame();
            sf::sleep(sf::milliseconds(30));
            i++;
            k++;
        }

        while (j < n2)
        {
            stats.incrementArrayAccesses();
            viz.renderFrame();
            bars[k].setHeight(rightHeights[j]);
            viz.highlightBars(k, -1, sf::Color(100, 255, 100));
            viz.renderFrame();
            sf::sleep(sf::milliseconds(30));
            j++;
            k++;
        }

        viz.resetBarColors();
        for (int idx = left; idx <= right; ++idx)
        {
            viz.markAsSorted(idx);
        }
        viz.renderFrame();
        sf::sleep(sf::milliseconds(50));
    }

    void mergeSort(std::vector<Bar> &bars, int left, int right, Visualizer &viz)
    {
        if (left < right)
        {
            int mid = left + (right - left) / 2;

            mergeSort(bars, left, mid, viz);
            mergeSort(bars, mid + 1, right, viz);

            merge(bars, left, mid, right, viz);
        }
    }

    void sort(Visualizer &viz)
    {
        auto &bars = viz.getBars();
        int n = bars.size();

        mergeSort(bars, 0, n - 1, viz);

        viz.resetBarColors();
        for (int i = 0; i < n; ++i)
        {
            viz.markAsSorted(i);
        }
        viz.renderFrame();
    }
}