#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class Statistics
{
private:
    int comparisons;
    int swaps;
    int arrayAccesses;
    sf::Clock timer;
    bool isRunning;

public:
    Statistics();

    void reset();
    void start();
    void stop();

    void incrementComparisons();
    void incrementSwaps();
    void incrementArrayAccesses();

    int getComparisons() const;
    int getSwaps() const;
    int getArrayAccesses() const;
    float getElapsedTime() const;
    bool getIsRunning() const;
};

#endif