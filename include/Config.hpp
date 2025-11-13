#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <SFML/Graphics.hpp>

enum class SortSpeed
{
    SLOW,
    MEDIUM,
    FAST,
    ULTRA_FAST
};

enum class ColorTheme
{
    DARK,
    LIGHT,
    OCEAN,
    SUNSET
};

struct ThemeColors
{
    sf::Color background;
    sf::Color defaultBar;
    sf::Color comparingBar;
    sf::Color swappingBar;
    sf::Color sortedBar;
    sf::Color pivotBar;
    sf::Color textPrimary;
    sf::Color textSecondary;
};

class Config
{
public:
    static int getDelayForSpeed(SortSpeed speed);
    static ThemeColors getThemeColors(ColorTheme theme);
};

#endif