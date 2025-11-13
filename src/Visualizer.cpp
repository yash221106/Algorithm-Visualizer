#include "../include/Visualizer.hpp"
#include "../include/Utils.hpp"
#include "../include/BubbleSort.hpp"
#include "../include/InsertionSort.hpp"
#include "../include/SelectionSort.hpp"
#include "../include/MergeSort.hpp"
#include "../include/QuickSort.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

Visualizer::Visualizer(int width, int height, int numBars)
    : windowWidth(width), windowHeight(height), barCount(numBars),
      window(sf::VideoMode(sf::Vector2u(width, height)), "Algorithm Visualizer"),
      fontLoaded(false), instructionText(nullptr), titleText(nullptr), statsText(nullptr),
      isSorting(false), selectedAlgorithm("None"), algorithmIndex(0)
{

    window.setFramerateLimit(60);

    if (font.openFromFile("assets/fonts/OpenSans-Regular.ttf"))
    {
        fontLoaded = true;
        setupText();
    }
    else
    {
        std::cerr << "Warning: Could not load font from assets/fonts/OpenSans-Regular.ttf" << std::endl;
    }

    randomizeBars();
}

void Visualizer::setupText()
{
    titleText = std::make_unique<sf::Text>(font);
    titleText->setString("Algorithm: None Selected");
    titleText->setCharacterSize(24);
    titleText->setFillColor(sf::Color::White);
    titleText->setPosition(sf::Vector2f(20.0f, 15.0f));

    statsText = std::make_unique<sf::Text>(font);
    statsText->setString("Comparisons: 0 | Swaps: 0 | Array Accesses: 0 | Time: 0.00s");
    statsText->setCharacterSize(18);
    statsText->setFillColor(sf::Color(150, 255, 150));
    statsText->setPosition(sf::Vector2f(20.0f, 50.0f));

    instructionText = std::make_unique<sf::Text>(font);
    instructionText->setString("Press R to Randomize | Press 1-5 to Select Algorithm | Press SPACE to Start");
    instructionText->setCharacterSize(18);
    instructionText->setFillColor(sf::Color(200, 200, 200));

    sf::FloatRect textBounds = instructionText->getLocalBounds();
    instructionText->setOrigin(sf::Vector2f(textBounds.size.x / 2.0f, 0.0f));
    instructionText->setPosition(sf::Vector2f(windowWidth / 2.0f, windowHeight - 40.0f));
}

void Visualizer::updateTitleText()
{
    if (titleText)
    {
        std::string status = isSorting ? " (Sorting...)" : "";
        titleText->setString("Algorithm: " + selectedAlgorithm + status);
    }
}

void Visualizer::updateStatsText()
{
    if (statsText)
    {
        std::ostringstream oss;
        oss << "Comparisons: " << stats.getComparisons()
            << " | Swaps: " << stats.getSwaps()
            << " | Array Accesses: " << stats.getArrayAccesses()
            << " | Time: " << std::fixed << std::setprecision(2) << stats.getElapsedTime() << "s";
        statsText->setString(oss.str());
    }
}

void Visualizer::randomizeBars()
{
    if (isSorting)
        return;

    std::vector<int> heights = Utils::generateRandomArray(barCount, 50, windowHeight - 120);
    createBars(heights);
    resetBarColors();
    stats.reset();
    updateStatsText();
}

void Visualizer::createBars(const std::vector<int> &heights)
{
    bars.clear();
    float barWidth = static_cast<float>(windowWidth) / barCount;

    for (size_t i = 0; i < heights.size(); ++i)
    {
        float xPos = i * barWidth;
        bars.emplace_back(xPos, barWidth - 2, static_cast<float>(heights[i]), windowHeight);
    }
}

void Visualizer::startSorting()
{
    if (isSorting || algorithmIndex == 0)
        return;

    isSorting = true;
    stats.start();
    updateTitleText();

    if (algorithmIndex == 1)
    {
        BubbleSort::sort(*this);
    }
    else if (algorithmIndex == 2)
    {
        InsertionSort::sort(*this);
    }
    else if (algorithmIndex == 3)
    {
        SelectionSort::sort(*this);
    }
    else if (algorithmIndex == 4)
    {
        MergeSort::sort(*this);
    }
    else if (algorithmIndex == 5)
    {
        QuickSort::sort(*this);
    }

    stats.stop();

    for (size_t i = 0; i < bars.size(); ++i)
    {
        bars[i].setColor(sf::Color(50, 200, 50));
    }
    renderFrame();

    isSorting = false;
    updateTitleText();
    updateStatsText();
}

void Visualizer::handleEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (isSorting)
                continue;

            if (keyPressed->code == sf::Keyboard::Key::R)
            {
                randomizeBars();
            }
            else if (keyPressed->code == sf::Keyboard::Key::Num1)
            {
                algorithmIndex = 1;
                selectedAlgorithm = "Bubble Sort";
                updateTitleText();
            }
            else if (keyPressed->code == sf::Keyboard::Key::Num2)
            {
                algorithmIndex = 2;
                selectedAlgorithm = "Insertion Sort";
                updateTitleText();
            }
            else if (keyPressed->code == sf::Keyboard::Key::Num3)
            {
                algorithmIndex = 3;
                selectedAlgorithm = "Selection Sort";
                updateTitleText();
            }
            else if (keyPressed->code == sf::Keyboard::Key::Num4)
            {
                algorithmIndex = 4;
                selectedAlgorithm = "Merge Sort";
                updateTitleText();
            }
            else if (keyPressed->code == sf::Keyboard::Key::Num5)
            {
                algorithmIndex = 5;
                selectedAlgorithm = "Quick Sort";
                updateTitleText();
            }
            else if (keyPressed->code == sf::Keyboard::Key::Space)
            {
                startSorting();
            }
        }
    }
}

void Visualizer::update()
{
    if (isSorting)
    {
        updateStatsText();
    }
}

void Visualizer::render()
{
    window.clear(sf::Color(25, 25, 35));

    for (auto &bar : bars)
    {
        bar.render(window);
    }

    if (fontLoaded)
    {
        if (titleText)
            window.draw(*titleText);
        if (statsText)
            window.draw(*statsText);
        if (instructionText)
            window.draw(*instructionText);
    }

    window.display();
}

void Visualizer::renderFrame()
{
    window.clear(sf::Color(25, 25, 35));

    for (auto &bar : bars)
    {
        bar.updateShape(windowHeight);
        bar.render(window);
    }

    if (fontLoaded)
    {
        if (titleText)
            window.draw(*titleText);
        if (statsText)
        {
            updateStatsText(); // Update stats text every frame during sorting
            window.draw(*statsText);
        }
        if (instructionText)
            window.draw(*instructionText);
    }

    window.display();
}

void Visualizer::highlightBars(int index1, int index2, const sf::Color &color)
{
    if (index1 >= 0 && index1 < static_cast<int>(bars.size()))
    {
        bars[index1].setColor(color);
    }
    if (index2 >= 0 && index2 < static_cast<int>(bars.size()))
    {
        bars[index2].setColor(color);
    }
}

void Visualizer::resetBarColors()
{
    for (auto &bar : bars)
    {
        bar.setColor(sf::Color(100, 150, 255));
    }
}

void Visualizer::markAsSorted(int index)
{
    if (index >= 0 && index < static_cast<int>(bars.size()))
    {
        bars[index].setColor(sf::Color(50, 200, 50));
    }
}

std::vector<Bar> &Visualizer::getBars()
{
    return bars;
}

Statistics &Visualizer::getStats()
{
    return stats;
}

int Visualizer::getWindowHeight() const
{
    return windowHeight;
}

bool Visualizer::getIsSorting() const
{
    return isSorting;
}

void Visualizer::setIsSorting(bool sorting)
{
    isSorting = sorting;
}

void Visualizer::run()
{
    while (window.isOpen())
    {
        handleEvents();
        update();
        render();
    }
}