#include "filemanager.h"

void savePoints(const std::vector<sf::Vector2f>& points)
{
  auto f = pfd::save_file("Choose file to save",
                          ".",
                            { "Comma Seperated Value (.csv)", "*.csv" },
                            pfd::opt::force_overwrite);
  std::cout << "Selected file: "  << f.result() << "\n";

  std::string path = f.result();
  if (path.empty())
      return;

  std::ofstream file(path);
  file << "x,y" << "/n";
  for (sf::Vector2f point : points)
  {
    file << point.x << "," << point.y << "\n";
  }
}

void openPoints(std::vector<sf::Vector2f>& points)
{
  auto f = pfd::open_file("Choose a csv file to open", ".",
                          { "Comma Seperated Value Files (.csv)", "*.csv"});
  std::vector<std::string> results = f.result();

  if (results.empty())
      return;

  std::string path = results[0]; // get first file only
  std::ifstream file(path);
  std::string line;
  std::getline(file, line); // remove first "x,y" line
  points.clear();
  while (std::getline(file, line))
  {
      std::stringstream ss(line);
      std::string x, y;
      std::getline(ss, x, ',');
      std::getline(ss, y, ',');
      points.push_back({std::stof(x), std::stof(y)}); // convert values to floats and insert them
  }
}
