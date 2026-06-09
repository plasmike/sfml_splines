#pragma once

#include <iostream>
#include <fstream>

#include <SFML/System/Vector2.hpp>

#include "portable-file-dialogs.h"


void savePoints(const std::vector<sf::Vector2f>& points);

void openPoints(std::vector<sf::Vector2f>& points);
