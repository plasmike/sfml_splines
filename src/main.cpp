#include <SFML/System/Vector2.hpp>
#include <vector>

#include <SFML/Graphics.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML Spline Test");

  // Points that should be connected in the spline
  std::vector<sf::Vector2f> points = {
    {100, 400}, {250, 100}, {400, 500}, {550, 200}
  };

  sf::VertexArray spline(sf::PrimitiveType::LineStrip);

  for (sf::Vector2f point : points)
  {
    spline.append(sf::Vertex{{point}, sf::Color::Green});
  }

  // run the program as long as the window is open
  while (window.isOpen())
  {
      // check all the window's events that were triggered since the last iteration of the loop
      while (const std::optional event = window.pollEvent())
      {
          if (event->is<sf::Event::Closed>())
              window.close();
      }

      window.clear();
      window.draw(spline);
      window.display();
  }

  return 0;
}
