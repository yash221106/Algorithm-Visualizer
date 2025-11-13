#include "../include/InsertionSort.hpp"
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>

namespace InsertionSort
{
    void sort(Visualizer &viz)
    {
        auto &bars = viz.getBars();
        auto &stats = viz.getStats();
        int n = bars.size();

        viz.markAsSorted(0);

        for (int i = 1; i < n; ++i)
        {
            stats.incrementArrayAccesses();
            float keyHeight = bars[i].getHeight();
            int j = i - 1;

            viz.highlightBars(i, -1, sf::Color(255, 255, 100));
            viz.renderFrame();
            sf::sleep(sf::milliseconds(10));

            while (j >= 0 && bars[j].getHeight() > keyHeight)
            {
                stats.incrementComparisons();
                stats.incrementArrayAccesses();
                stats.incrementArrayAccesses();
                viz.renderFrame();

                viz.highlightBars(j, j + 1, sf::Color(255, 100, 100));

                bars[j + 1].setHeight(bars[j].getHeight());
                viz.renderFrame();
                sf::sleep(sf::milliseconds(10));

                j--;
            }

            if (j >= 0)
            {
                stats.incrementComparisons();
                viz.renderFrame();
            }

            stats.incrementArrayAccesses();
            bars[j + 1].setHeight(keyHeight);

            viz.resetBarColors();
            for (int k = 0; k <= i; ++k)
            {
                viz.markAsSorted(k);
            }
            viz.renderFrame();
        }
    }
}