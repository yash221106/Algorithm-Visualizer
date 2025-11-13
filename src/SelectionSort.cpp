#include "../include/SelectionSort.hpp"
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>

namespace SelectionSort
{
    void sort(Visualizer &viz)
    {
        auto &bars = viz.getBars();
        auto &stats = viz.getStats();
        int n = bars.size();

        for (int i = 0; i < n - 1; ++i)
        {
            int minIndex = i;

            viz.highlightBars(i, -1, sf::Color(100, 100, 255));
            viz.renderFrame();

            for (int j = i + 1; j < n; ++j)
            {
                stats.incrementComparisons();
                stats.incrementArrayAccesses();
                stats.incrementArrayAccesses();
                viz.renderFrame();

                viz.highlightBars(minIndex, j, sf::Color(255, 255, 100));
                viz.renderFrame();
                sf::sleep(sf::milliseconds(10));

                if (bars[j].getHeight() < bars[minIndex].getHeight())
                {
                    viz.resetBarColors();
                    for (int k = 0; k < i; ++k)
                    {
                        viz.markAsSorted(k);
                    }
                    minIndex = j;
                }

                viz.resetBarColors();
                for (int k = 0; k < i; ++k)
                {
                    viz.markAsSorted(k);
                }
                viz.highlightBars(minIndex, -1, sf::Color(100, 100, 255));
            }

            if (minIndex != i)
            {
                stats.incrementSwaps();
                stats.incrementArrayAccesses();
                stats.incrementArrayAccesses();
                viz.renderFrame();

                viz.highlightBars(i, minIndex, sf::Color(255, 100, 100));

                float tempHeight = bars[i].getHeight();
                bars[i].setHeight(bars[minIndex].getHeight());
                bars[minIndex].setHeight(tempHeight);

                viz.renderFrame();
                sf::sleep(sf::milliseconds(50));
            }

            viz.resetBarColors();
            for (int k = 0; k <= i; ++k)
            {
                viz.markAsSorted(k);
            }
            viz.renderFrame();
        }
        viz.markAsSorted(n - 1);
    }
}