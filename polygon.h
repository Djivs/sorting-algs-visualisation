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

    void allSorts();

    void bubbleSort();
    void insertionSort();
    void selectionSort();
    void quickSort();
    void gnomeSort();
    void stoogeSort();
    void mergeSort();
    void bogoSort();

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
    void stoogeSort(int start, int end);
    void mergeSort(int start, int end);
    void merge(int start, int mid, int end);
    bool bogoCheckSorted();
    int quickSortPartition(int start, int end);
    
    vector <int> getRandomVector(int size);
    void setNumbersToSort(vector <int> newNumbers);
    void shuffleNumbers(vector <int> &numbers);
    void updateBars();

    vector <sf::RectangleShape> bars;
    vector <int> numbersToSort;

    int width = 1000, height = 500;
    int numbersAmount = 100;

    sf::RenderWindow *window;

    sf::Sound *sound;
    sf::SoundBuffer *buffer;
};

#endif