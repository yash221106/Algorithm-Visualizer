#include "../include/BubbleSort.hpp"
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>

namespace BubbleSort
{
    void sort(Visualizer &viz)
    {
        auto &bars = viz.getBars();
        auto &stats = viz.getStats();
        int n = bars.size();

        for (int i = 0; i < n - 1; ++i)
        {
            for (int j = 0; j < n - i - 1; ++j)
            {
                stats.incrementComparisons();
                stats.incrementArrayAccesses();
                stats.incrementArrayAccesses();

                viz.highlightBars(j, j + 1, sf::Color(255, 255, 100));
                viz.renderFrame();
                sf::sleep(sf::milliseconds(10));

                if (bars[j].getHeight() > bars[j + 1].getHeight())
                {
                    stats.incrementSwaps();
                    stats.incrementArrayAccesses();
                    stats.incrementArrayAccesses();

                    float tempHeight = bars[j].getHeight();
                    bars[j].setHeight(bars[j + 1].getHeight());
                    bars[j + 1].setHeight(tempHeight);

                    viz.highlightBars(j, j + 1, sf::Color(255, 100, 100));
                    viz.renderFrame();
                    sf::sleep(sf::milliseconds(10));
                }

                viz.resetBarColors();
                for (int k = n - i; k < n; ++k)
                {
                    viz.markAsSorted(k);
                }
            }
            viz.markAsSorted(n - i - 1);
        }
        viz.markAsSorted(0);
    }
}