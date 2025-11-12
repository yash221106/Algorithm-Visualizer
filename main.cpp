#include <SFML/Graphics.hpp>

int main()
{
    // VideoMode takes a Vector2u in SFML 3
    sf::VideoMode vm({800u, 600u});

    // RenderWindow in SFML 3 expects an explicit State argument in the 2-arg form,
    // so pass an empty state object.
    sf::RenderWindow window(vm, "SFML 3.x Test", sf::State{});

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        // pollEvent() in SFML 3 returns std::optional<Event>
        while (auto opt = window.pollEvent())
        {
            auto &event = *opt;                // extract the event
            if (event.is<sf::Event::Closed>()) // new is<> API
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
