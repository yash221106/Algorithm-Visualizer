#include "../include/Bar.hpp"

Bar::Bar(float xPos, float barWidth, float barHeight, float windowHeight)
    : x(xPos), width(barWidth), height(barHeight), color(sf::Color(100, 150, 255))
{

    y = windowHeight - barHeight;

    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(sf::Vector2f(x, y));
    shape.setFillColor(color);
}

void Bar::setColor(const sf::Color &newColor)
{
    color = newColor;
    shape.setFillColor(color);
}

void Bar::setHeight(float newHeight)
{
    height = newHeight;
    shape.setSize(sf::Vector2f(width, height));
}

void Bar::setPosition(float xPos)
{
    x = xPos;
}

void Bar::updateShape(float windowHeight)
{
    y = windowHeight - height;
    shape.setPosition(sf::Vector2f(x, y));
    shape.setSize(sf::Vector2f(width, height));
}

float Bar::getHeight() const
{
    return height;
}

float Bar::getX() const
{
    return x;
}

float Bar::getWidth() const
{
    return width;
}

void Bar::render(sf::RenderWindow &window)
{
    window.draw(shape);
}