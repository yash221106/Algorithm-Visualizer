#include "../include/QuickSort.hpp"
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>

namespace QuickSort
{

    int partition(std::vector<Bar> &bars, int low, int high, Visualizer &viz)
    {
        auto &stats = viz.getStats();

        stats.incrementArrayAccesses();
        viz.renderFrame();
        float pivot = bars[high].getHeight();

        viz.highlightBars(high, -1, sf::Color(255, 0, 255));
        viz.renderFrame();
        sf::sleep(sf::milliseconds(50));

        int i = low - 1;

        for (int j = low; j < high; ++j)
        {
            stats.incrementComparisons();
            stats.incrementArrayAccesses();
            viz.renderFrame();

            viz.highlightBars(j, high, sf::Color(255, 255, 100));
            viz.renderFrame();
            sf::sleep(sf::milliseconds(20));

            if (bars[j].getHeight() < pivot)
            {
                i++;
                stats.incrementSwaps();
                stats.incrementArrayAccesses();
                stats.incrementArrayAccesses();
                viz.renderFrame();

                viz.highlightBars(i, j, sf::Color(255, 100, 100));

                float tempHeight = bars[i].getHeight();
                bars[i].setHeight(bars[j].getHeight());
                bars[j].setHeight(tempHeight);

                viz.renderFrame();
                sf::sleep(sf::milliseconds(30));
            }

            viz.resetBarColors();
            viz.highlightBars(high, -1, sf::Color(255, 0, 255));
        }

        stats.incrementSwaps();
        stats.incrementArrayAccesses();
        stats.incrementArrayAccesses();
        viz.renderFrame();

        viz.highlightBars(i + 1, high, sf::Color(255, 100, 100));

        float tempHeight = bars[i + 1].getHeight();
        bars[i + 1].setHeight(bars[high].getHeight());
        bars[high].setHeight(tempHeight);

        viz.renderFrame();
        sf::sleep(sf::milliseconds(50));

        viz.resetBarColors();
        viz.markAsSorted(i + 1);
        viz.renderFrame();

        return i + 1;
    }

    void quickSort(std::vector<Bar> &bars, int low, int high, Visualizer &viz)
    {
        if (low < high)
        {
            int pi = partition(bars, low, high, viz);

            quickSort(bars, low, pi - 1, viz);
            quickSort(bars, pi + 1, high, viz);
        }
        else if (low == high)
        {
            viz.markAsSorted(low);
            viz.renderFrame();
        }
    }

    void sort(Visualizer &viz)
    {
        auto &bars = viz.getBars();
        int n = bars.size();

        quickSort(bars, 0, n - 1, viz);

        viz.resetBarColors();
        for (int i = 0; i < n; ++i)
        {
            viz.markAsSorted(i);
        }
        viz.renderFrame();
    }
}