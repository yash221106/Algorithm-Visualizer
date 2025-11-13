#include "../include/Config.hpp"

int Config::getDelayForSpeed(SortSpeed speed)
{
    switch (speed)
    {
    case SortSpeed::SLOW:
        return 50;
    case SortSpeed::MEDIUM:
        return 20;
    case SortSpeed::FAST:
        return 5;
    case SortSpeed::ULTRA_FAST:
        return 1;
    default:
        return 20;
    }
}

ThemeColors Config::getThemeColors(ColorTheme theme)
{
    ThemeColors colors;

    switch (theme)
    {
    case ColorTheme::DARK:
        colors.background = sf::Color(25, 25, 35);
        colors.defaultBar = sf::Color(100, 150, 255);
        colors.comparingBar = sf::Color(255, 255, 100);
        colors.swappingBar = sf::Color(255, 100, 100);
        colors.sortedBar = sf::Color(50, 200, 50);
        colors.pivotBar = sf::Color(255, 0, 255);
        colors.textPrimary = sf::Color::White;
        colors.textSecondary = sf::Color(200, 200, 200);
        break;

    case ColorTheme::LIGHT:
        colors.background = sf::Color(240, 240, 245);
        colors.defaultBar = sf::Color(70, 130, 220);
        colors.comparingBar = sf::Color(255, 200, 50);
        colors.swappingBar = sf::Color(220, 50, 50);
        colors.sortedBar = sf::Color(50, 180, 50);
        colors.pivotBar = sf::Color(200, 0, 200);
        colors.textPrimary = sf::Color(20, 20, 30);
        colors.textSecondary = sf::Color(60, 60, 80);
        break;

    case ColorTheme::OCEAN:
        colors.background = sf::Color(15, 30, 50);
        colors.defaultBar = sf::Color(50, 150, 200);
        colors.comparingBar = sf::Color(100, 230, 230);
        colors.swappingBar = sf::Color(255, 140, 100);
        colors.sortedBar = sf::Color(100, 255, 200);
        colors.pivotBar = sf::Color(200, 100, 255);
        colors.textPrimary = sf::Color(200, 240, 255);
        colors.textSecondary = sf::Color(150, 200, 230);
        break;

    case ColorTheme::SUNSET:
        colors.background = sf::Color(40, 20, 40);
        colors.defaultBar = sf::Color(255, 120, 100);
        colors.comparingBar = sf::Color(255, 200, 100);
        colors.swappingBar = sf::Color(255, 80, 150);
        colors.sortedBar = sf::Color(150, 255, 150);
        colors.pivotBar = sf::Color(200, 100, 255);
        colors.textPrimary = sf::Color(255, 220, 200);
        colors.textSecondary = sf::Color(255, 180, 150);
        break;
    }

    return colors;
}