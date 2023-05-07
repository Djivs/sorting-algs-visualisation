#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>

#include "polygon.h"

class Engine {
public:
    explicit Engine();
    ~Engine();

    void run();
private:
    sf::RenderWindow *window;

    Polygon *polygon;

    const int width = 1000, height = 500;

};

#endif