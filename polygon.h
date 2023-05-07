#ifndef POLYGON_H
#define POLYGON_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
using std::vector;

class Polygon {
public:
    explicit Polygon();
    explicit Polygon(int size, sf::RenderWindow *newWin, int newW, int newH);
    ~Polygon();

    void bubbleSort();
    void insertionSort();
    void selectionSort();
    void quickSort();
    void gnomeSort();

    void playAnimation();

    vector <sf::RectangleShape> getBars() const {return bars;}
    int getWidth() const {return width;}
    int getHeight() const {return height;} 
private:
    void swapBars(int first, int second);
    void setBar(int index, int value);
    void highlightBar(int index,  sf::Color);
    void compareBars(int first, int second);

    void paintBars();

    void quickSort(int start, int end);
    int quickSortPartition(int start, int end);
    vector <int> getRandomVector(int size);
    void setNumbersToSort(vector <int> newNumbers);

    vector <sf::RectangleShape> bars;
    vector <int> numbersToSort;

    int width = 200, height = 200;

    sf::RenderWindow *window;

    sf::Sound *sound;
    sf::SoundBuffer *buffer;
};

#endif