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
      fontLoaded(false), instructionText(nullptr), titleText(nullptr),
      statsText(nullptr), controlsText(nullptr),
      isSorting(false), isPaused(false), selectedAlgorithm("None"), algorithmIndex(0),
      currentSpeed(SortSpeed::MEDIUM), currentTheme(ColorTheme::DARK)
{

    window.setFramerateLimit(60);

    themeColors = Config::getThemeColors(currentTheme);

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
    titleText->setFillColor(themeColors.textPrimary);
    titleText->setPosition(sf::Vector2f(20.0f, 15.0f));

    statsText = std::make_unique<sf::Text>(font);
    statsText->setString("Comparisons: 0 | Swaps: 0 | Array Accesses: 0 | Time: 0.00s");
    statsText->setCharacterSize(18);
    statsText->setFillColor(sf::Color(150, 255, 150));
    statsText->setPosition(sf::Vector2f(20.0f, 50.0f));

    controlsText = std::make_unique<sf::Text>(font);
    controlsText->setCharacterSize(16);
    controlsText->setFillColor(themeColors.textSecondary);
    controlsText->setPosition(sf::Vector2f(20.0f, windowHeight - 70.0f));
    updateControlsText();

    instructionText = std::make_unique<sf::Text>(font);
    instructionText->setString("R: Randomize | 1-5: Select Algorithm | SPACE: Start | P: Pause");
    instructionText->setCharacterSize(18);
    instructionText->setFillColor(themeColors.textSecondary);

    sf::FloatRect textBounds = instructionText->getLocalBounds();
    instructionText->setOrigin(sf::Vector2f(textBounds.size.x / 2.0f, 0.0f));
    instructionText->setPosition(sf::Vector2f(windowWidth / 2.0f, windowHeight - 40.0f));
}

void Visualizer::updateTitleText()
{
    if (titleText)
    {
        std::string status = isSorting ? (isPaused ? " (Paused)" : " (Sorting...)") : "";
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

void Visualizer::updateControlsText()
{
    if (controlsText)
    {
        std::string speedStr;
        switch (currentSpeed)
        {
        case SortSpeed::SLOW:
            speedStr = "Slow";
            break;
        case SortSpeed::MEDIUM:
            speedStr = "Medium";
            break;
        case SortSpeed::FAST:
            speedStr = "Fast";
            break;
        case SortSpeed::ULTRA_FAST:
            speedStr = "Ultra Fast";
            break;
        }

        std::string themeStr;
        switch (currentTheme)
        {
        case ColorTheme::DARK:
            themeStr = "Dark";
            break;
        case ColorTheme::LIGHT:
            themeStr = "Light";
            break;
        case ColorTheme::OCEAN:
            themeStr = "Ocean";
            break;
        case ColorTheme::SUNSET:
            themeStr = "Sunset";
            break;
        }

        std::ostringstream oss;
        oss << "Speed: " << speedStr << " (Q/W to change) | Theme: " << themeStr << " (T to cycle)";
        controlsText->setString(oss.str());
    }
}

void Visualizer::changeSpeed(SortSpeed newSpeed)
{
    currentSpeed = newSpeed;
    updateControlsText();
}

void Visualizer::changeTheme(ColorTheme newTheme)
{
    currentTheme = newTheme;
    themeColors = Config::getThemeColors(currentTheme);

    if (titleText)
        titleText->setFillColor(themeColors.textPrimary);
    if (instructionText)
        instructionText->setFillColor(themeColors.textSecondary);
    if (controlsText)
        controlsText->setFillColor(themeColors.textSecondary);

    applyThemeToAllBars();
    updateControlsText();
}

void Visualizer::applyThemeToAllBars()
{
    if (!isSorting)
    {
        resetBarColors();
    }
}

void Visualizer::randomizeBars()
{
    if (isSorting)
        return;

    std::vector<int> heights = Utils::generateRandomArray(barCount, 50, windowHeight - 140);
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
    isPaused = false;
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
        bars[i].setColor(themeColors.sortedBar);
    }
    renderFrame();

    isSorting = false;
    isPaused = false;
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
            if (keyPressed->code == sf::Keyboard::Key::R && !isSorting)
            {
                randomizeBars();
            }
            else if (keyPressed->code == sf::Keyboard::Key::P && isSorting)
            {
                isPaused = !isPaused;
                updateTitleText();
            }
            else if (keyPressed->code == sf::Keyboard::Key::Q && !isSorting)
            {
                if (currentSpeed == SortSpeed::MEDIUM)
                    changeSpeed(SortSpeed::SLOW);
                else if (currentSpeed == SortSpeed::FAST)
                    changeSpeed(SortSpeed::MEDIUM);
                else if (currentSpeed == SortSpeed::ULTRA_FAST)
                    changeSpeed(SortSpeed::FAST);
            }
            else if (keyPressed->code == sf::Keyboard::Key::W && !isSorting)
            {
                if (currentSpeed == SortSpeed::SLOW)
                    changeSpeed(SortSpeed::MEDIUM);
                else if (currentSpeed == SortSpeed::MEDIUM)
                    changeSpeed(SortSpeed::FAST);
                else if (currentSpeed == SortSpeed::FAST)
                    changeSpeed(SortSpeed::ULTRA_FAST);
            }
            else if (keyPressed->code == sf::Keyboard::Key::T && !isSorting)
            {
                ColorTheme nextTheme;
                switch (currentTheme)
                {
                case ColorTheme::DARK:
                    nextTheme = ColorTheme::LIGHT;
                    break;
                case ColorTheme::LIGHT:
                    nextTheme = ColorTheme::OCEAN;
                    break;
                case ColorTheme::OCEAN:
                    nextTheme = ColorTheme::SUNSET;
                    break;
                case ColorTheme::SUNSET:
                    nextTheme = ColorTheme::DARK;
                    break;
                }
                changeTheme(nextTheme);
            }
            else if (!isSorting)
            {
                if (keyPressed->code == sf::Keyboard::Key::Num1)
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
    window.clear(themeColors.background);

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
        if (controlsText)
            window.draw(*controlsText);
        if (instructionText)
            window.draw(*instructionText);
    }

    window.display();
}

void Visualizer::renderFrame()
{
    window.clear(themeColors.background);

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
            updateStatsText();
            window.draw(*statsText);
        }
        if (controlsText)
            window.draw(*controlsText);
        if (instructionText)
            window.draw(*instructionText);
    }

    window.display();

    while (isPaused && window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
                return;
            }
            if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::P)
                {
                    isPaused = false;
                    updateTitleText();
                    return;
                }
            }
        }
    }
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
        bar.setColor(themeColors.defaultBar);
    }
}

void Visualizer::markAsSorted(int index)
{
    if (index >= 0 && index < static_cast<int>(bars.size()))
    {
        bars[index].setColor(themeColors.sortedBar);
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

int Visualizer::getCurrentDelay() const
{
    return Config::getDelayForSpeed(currentSpeed);
}

bool Visualizer::getIsSorting() const
{
    return isSorting;
}

bool Visualizer::getIsPaused() const
{
    return isPaused;
}

void Visualizer::setIsSorting(bool sorting)
{
    isSorting = sorting;
}

void Visualizer::setIsPaused(bool paused)
{
    isPaused = paused;
}

ThemeColors Visualizer::getThemeColors() const
{
    return themeColors;
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