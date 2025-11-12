#ifndef BAR_HPP
#define BAR_HPP

#include <SFML/Graphics.hpp>

class Bar
{
private:
    float x;
    float y;
    float width;
    float height;
    sf::Color color;
    sf::RectangleShape shape;

public:
    Bar(float xPos, float barWidth, float barHeight, float windowHeight);

    void setColor(const sf::Color &newColor);
    void setHeight(float newHeight);
    void setPosition(float xPos);
    void updateShape(float windowHeight);

    float getHeight() const;
    float getX() const;
    float getWidth() const;

    void render(sf::RenderWindow &window);
};

#endif