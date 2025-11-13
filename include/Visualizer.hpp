#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include "Bar.hpp"
#include "Statistics.hpp"
#include "Config.hpp"

class Visualizer
{
private:
    sf::RenderWindow window;
    std::vector<Bar> bars;
    sf::Font font;
    std::unique_ptr<sf::Text> titleText;
    std::unique_ptr<sf::Text> instructionText;
    std::unique_ptr<sf::Text> statsText;
    std::unique_ptr<sf::Text> controlsText;

    const int windowWidth;
    const int windowHeight;
    const int barCount;

    bool fontLoaded;
    bool isSorting;
    bool isPaused;
    std::string selectedAlgorithm;
    int algorithmIndex;

    SortSpeed currentSpeed;
    ColorTheme currentTheme;
    ThemeColors themeColors;

    Statistics stats;

    void handleEvents();
    void update();
    void render();
    void createBars(const std::vector<int> &heights);
    void randomizeBars();
    void setupText();
    void updateTitleText();
    void updateStatsText();
    void updateControlsText();
    void startSorting();
    void changeSpeed(SortSpeed newSpeed);
    void changeTheme(ColorTheme newTheme);
    void applyThemeToAllBars();

public:
    Visualizer(int width, int height, int numBars);
    void run();

    void renderFrame();
    void highlightBars(int index1, int index2, const sf::Color &color);
    void resetBarColors();
    void markAsSorted(int index);

    std::vector<Bar> &getBars();
    Statistics &getStats();
    int getWindowHeight() const;
    int getCurrentDelay() const;
    bool getIsSorting() const;
    bool getIsPaused() const;
    void setIsSorting(bool sorting);
    void setIsPaused(bool paused);

    ThemeColors getThemeColors() const;
};

#endif