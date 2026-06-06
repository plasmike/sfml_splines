#include <iostream>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

sf::Vector2f catmullRom(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, float t)
{
  float t2 = t*t;
  float t3 = t*t2;

  return 0.5f * (
    (-3.f*p2 + 3.f*p1 - p0 + p3) * t3
    + (-p3 - 5.f*p1 + 4.f*p2 + 2.f*p0) * t2
    + (p2 - p0) * t
    + (2.f*p1)
  );
}

int main() {
  sf::RenderWindow window(sf::VideoMode({1000, 1000}), "SFML Spline Test");

  // Spline points
  std::vector<sf::Vector2f> points = {
    {100, 400}, {250, 100}, {400, 500}, {450, 550}, {700, 400}
  };

  int samplesPerSegment = 100;
  float pointRadius = 5.f; // Radius for grabbing the points of the curve
  int dragPointIndex = -1; // point being currently moved/dragged by the mouse | -1 = none

  // run the program as long as the window is open
  while (window.isOpen())
  {
      // check all the window's events that were triggered since the last iteration of the loop
      while (const std::optional event = window.pollEvent())
      {
          if (event->is<sf::Event::Closed>())
              window.close();

          if (const auto* evnt = event->getIf<sf::Event::MouseButtonPressed>())
          {
            sf::Vector2f mousePos = {static_cast<float>(evnt->position.x), static_cast<float>(evnt->position.y)};
            bool found = false;

            for (int i = 0; i < points.size(); i++)
            {
              sf::Vector2f diff = mousePos - points[i];
              if (sqrt(diff.x * diff.x + diff.y * diff.y) < pointRadius)
              {
                if (evnt->button == sf::Mouse::Button::Left) // drag/move point
                {
                  found = true;
                  dragPointIndex = i;
                }
                else if (evnt->button == sf::Mouse::Button::Right) // remove point
                {
                  points.erase(points.begin() + i);
                  found = true;
                  dragPointIndex = -1;
                }
                break;
              }
            }
            if (!found && evnt->button == sf::Mouse::Button::Left)
            {
              points.push_back(mousePos); // create new point
            }
          }

          if (event->is<sf::Event::MouseButtonReleased>())
            dragPointIndex = -1;

          // Move point
          if (const auto* evnt = event->getIf<sf::Event::MouseMoved>())
          {
            if (dragPointIndex != -1)
              points[dragPointIndex] = {static_cast<float>(evnt->position.x), static_cast<float>(evnt->position.y)};
          }
      }

      sf::VertexArray spline(sf::PrimitiveType::LineStrip);
      for (int i = 0; i+3 < points.size(); i++)
      {
        for (int j = 0; j < samplesPerSegment; j++)
        {
          float t = j / static_cast<float>(samplesPerSegment);
          sf::Vector2f pos = catmullRom(points[i], points[i+1], points[i+2], points[i+3], t);
          spline.append(sf::Vertex{pos, sf::Color::Green});
        }
      }

      window.clear();
      window.draw(spline);
      for (sf::Vector2f point : points)
      {
        sf::CircleShape pointCircle(pointRadius);
        pointCircle.setFillColor(sf::Color::Red);
        pointCircle.setOrigin({pointRadius, pointRadius});
        pointCircle.setPosition(point);
        window.draw(pointCircle);
      }
      window.display();
  }

  return 0;
}
