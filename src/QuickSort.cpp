#include "../include/QuickSort.hpp"
#include <SFML/System/Sleep.hpp>

namespace QuickSort
{
    int partition(Visualizer &viz, int low, int high);
    void sortRecursive(Visualizer &viz, int low, int high);

    void sort(Visualizer &viz) // <-- new wrapper
    {
        auto &bars = viz.getBars();
        if (bars.empty())
            return;
        sortRecursive(viz, 0, bars.size() - 1);
    }

    void sortRecursive(Visualizer &viz, int low, int high)
    {
        if (low < high)
        {
            int pi = partition(viz, low, high);
            sortRecursive(viz, low, pi - 1);
            sortRecursive(viz, pi + 1, high);
        }
    }

    int partition(Visualizer &viz, int low, int high)
    {
        auto &bars = viz.getBars();
        float pivot = bars[high].getHeight();
        int i = low - 1;

        for (int j = low; j < high; ++j)
        {
            viz.highlightBars(j, high, sf::Color(255, 255, 100));
            viz.renderFrame();
            sf::sleep(sf::milliseconds(30));

            if (bars[j].getHeight() < pivot)
            {
                i++;
                std::swap(bars[i], bars[j]);
                viz.renderFrame();
                sf::sleep(sf::milliseconds(30));
            }
        }

        std::swap(bars[i + 1], bars[high]);
        viz.renderFrame();
        sf::sleep(sf::milliseconds(30));

        viz.resetBarColors();
        return i + 1;
    }
}
