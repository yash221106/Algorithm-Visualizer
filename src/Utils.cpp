#include "../include/Utils.hpp"
#include <random>

namespace Utils
{
    std::vector<int> generateRandomArray(int size, int minVal, int maxVal)
    {
        std::vector<int> array;
        array.reserve(size);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(minVal, maxVal);

        for (int i = 0; i < size; ++i)
        {
            array.push_back(dis(gen));
        }

        return array;
    }
}