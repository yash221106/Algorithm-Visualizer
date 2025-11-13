#include "../include/Statistics.hpp"

Statistics::Statistics()
    : comparisons(0), swaps(0), arrayAccesses(0), isRunning(false)
{
}

void Statistics::reset()
{
    comparisons = 0;
    swaps = 0;
    arrayAccesses = 0;
    timer.restart();
    isRunning = false;
}

void Statistics::start()
{
    reset();
    isRunning = true;
    timer.restart();
}

void Statistics::stop()
{
    isRunning = false;
}

void Statistics::incrementComparisons()
{
    comparisons++;
}

void Statistics::incrementSwaps()
{
    swaps++;
}

void Statistics::incrementArrayAccesses()
{
    arrayAccesses++;
}

int Statistics::getComparisons() const
{
    return comparisons;
}

int Statistics::getSwaps() const
{
    return swaps;
}

int Statistics::getArrayAccesses() const
{
    return arrayAccesses;
}

float Statistics::getElapsedTime() const
{
    return timer.getElapsedTime().asSeconds();
}

bool Statistics::getIsRunning() const
{
    return isRunning;
}