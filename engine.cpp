#include "engine.h"

#include <iostream>

Engine::Engine() {
    window = new sf::RenderWindow(sf::VideoMode(width, height), "SFML works!");
    polygon = new Polygon(500, window, width, height);
}

Engine::~Engine() {
    window->close();
    delete window;
}

void Engine::run() {

    polygon->bubbleSort();
    polygon->insertionSort();
    polygon->selectionSort();
    polygon->quickSort();
    polygon->gnomeSort();

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->display();
    }
}