#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/System/Time.hpp>
#include <algorithm>
#include <random>
#include <iostream>

#include "polygon.h"

Polygon::Polygon() {
    window = new sf::RenderWindow(sf::VideoMode(width, height), "SFML works!");

    buffer = new sf::SoundBuffer;
    sound = new sf::Sound;
    buffer->loadFromFile("beep.wav");
    sound->setBuffer(*buffer);
    sound->setVolume(100);

    setNumbersToSort(getRandomVector(numbersAmount));
}

Polygon::Polygon(int size, sf::RenderWindow *newWin, int newW, int newH) {
    buffer = new sf::SoundBuffer;
    sound = new sf::Sound;

    buffer->loadFromFile("beep.wav");
    sound->setBuffer(*buffer);
    sound->setVolume(100);
    window = newWin;
    width = newW; height = newH;


    setNumbersToSort(getRandomVector(size));

    

}

Polygon::~Polygon() {
    window->close();

    delete window;
    delete buffer;
    delete sound;
}

void Polygon::allSorts() {
    bubbleSort();
    insertionSort();
    selectionSort();
    quickSort();
    gnomeSort();
    stoogeSort();
    mergeSort();
    bogoSort();

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

void Polygon::paintBars() {
    window->clear();
    for (auto &i : bars) {
        window->draw(i);
    }
    window->display();

}

void Polygon::swapBars(int first, int second) {
    const auto firstSize = bars[first].getSize();
    bars[first].setSize(bars[second].getSize());
    bars[second].setSize(firstSize);

    bars[first].setPosition(bars[first].getPosition().x, height - bars[first].getSize().y);
    bars[second].setPosition(bars[second].getPosition().x, height - bars[second].getSize().y);

    sound->setPitch(static_cast<float>(numbersToSort[second])/static_cast<float>(numbersToSort.size()) * 3.0);
    sound->play();

    highlightBar(first, sf::Color::Green);
    highlightBar(second, sf::Color::Green);
    paintBars();
    highlightBar(first, sf::Color::White);
    highlightBar(second, sf::Color::White);
    //sf::sleep(sf::microseconds(10000));

}

void Polygon::setBar(int index, int value) {

    const int rectHeight = (static_cast<float>(height) * 0.9)/static_cast<float>(numbersToSort.size())*static_cast<float>(value);

    bars[index].setSize(sf::Vector2f(bars[index].getSize().x, rectHeight));
    bars[index].setPosition(bars[index].getPosition().x, height - bars[index].getSize().y);

    sound->setPitch(static_cast<float>(value)/static_cast<float>(numbersToSort.size()) * 3.0 + 1);
    sound->play();

    highlightBar(index, sf::Color::Green);
    paintBars();
    highlightBar(index, sf::Color::White);
    //sf::sleep(sf::microseconds(10000));
}

void Polygon::compareBars(int first, int second) {
    highlightBar(first, sf::Color::Magenta);
    highlightBar(second, sf::Color::Magenta);
    paintBars();
    sound->setPitch(static_cast<float>(second)/static_cast<float>(numbersToSort.size()) * 3.0 + 1);
    sound->play();
    highlightBar(first, sf::Color::White);
    highlightBar(second, sf::Color::White);
    //sf::sleep(sf::milliseconds(100));
}

void Polygon::highlightBar(int index, sf::Color color) {
    bars[index].setFillColor(color);
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            window->close();
            exit(0);

        }
    }
}

void Polygon::bubbleSort() {

    setNumbersToSort(getRandomVector(numbersToSort.size()));

    for (int i = 0; i < numbersToSort.size() - 1; ++i) {
        for (int j = 0; j < numbersToSort.size() - i -1; ++j) {
            compareBars(j, j+1);
            if (numbersToSort[j] > numbersToSort[j+1]) {
                std::swap(numbersToSort[j], numbersToSort[j+1]);
                swapBars(j, j+1);
            }
        }
        
    }

    playAnimation();
    
}

void Polygon::stoogeSort() {
    setNumbersToSort(getRandomVector(numbersToSort.size()));

    stoogeSort(0, numbersToSort.size() - 1);

    playAnimation();
}


void Polygon::mergeSort() {
    setNumbersToSort(getRandomVector(numbersToSort.size()));

    mergeSort(0, numbersToSort.size() - 1);

    playAnimation();
}

void Polygon::mergeSort(int start, int end) {
    if (start >= end) {
        return;
    }

    auto mid = (end - start) / 2 + start;
    mergeSort(start, mid);
    mergeSort(mid + 1, end);
    merge(start, mid, end);

}

void Polygon::merge(int start, int mid, int end) {
    int leftIndex = start;
    int rightIndex = mid + 1;
    vector <int> temp;
    while (leftIndex != mid + 1 && rightIndex != end + 1) {
        compareBars(leftIndex, rightIndex);
        if (numbersToSort[leftIndex] < numbersToSort[rightIndex]) {
            temp.push_back(numbersToSort[leftIndex]);
            setBar(leftIndex, numbersToSort[leftIndex]);
            ++leftIndex;
        } else {
            temp.push_back(numbersToSort[rightIndex]);
            setBar(leftIndex, numbersToSort[rightIndex]);
            ++rightIndex;
        }
    }
    for (int i = 0; i < temp.size(); ++i) {
        numbersToSort[i + start] = temp[i];
        setBar(i + start, temp[i]);
    } 
}

void Polygon::bogoSort() {
    setNumbersToSort(getRandomVector(numbersToSort.size()));

    while (!bogoCheckSorted()) {
        shuffleNumbers(numbersToSort);
        updateBars();
        paintBars();
    }

    playAnimation();
}

bool Polygon::bogoCheckSorted() {
    for (int i = 1; i < numbersToSort.size(); ++i) {
        compareBars(i-1, i);
        if (numbersToSort[i-1] > numbersToSort[i]) {
            return false;
        }
    }
    return true;
}

void Polygon::stoogeSort(int start, int end) {
    if (start == end) {
        return;
    }
    if (end - start == 1) {
        compareBars(start, end);
        if (numbersToSort[start] > numbersToSort[end]) {
            std::swap(numbersToSort[start], numbersToSort[end]);
            swapBars(start, end);
        }
        return;
    }
    const float curLen = (end - start + 1);
    const int sortLen = ceil(curLen * 2.0 / 3.0) ;
    stoogeSort(start, start + sortLen - 1);
    stoogeSort(end - sortLen + 1, end);
    stoogeSort(start, start + sortLen - 1);
}

void Polygon::gnomeSort() {
    setNumbersToSort(getRandomVector(numbersToSort.size()));

    int pos = 0;
    while (pos < numbersToSort.size()) {
        if (pos) compareBars(pos, pos - 1);
        if (pos == 0 || numbersToSort[pos] >= numbersToSort[pos - 1]) {
            ++pos;
        } else {
            std::swap(numbersToSort[pos], numbersToSort[pos-1]);
            swapBars(pos, pos - 1);
            --pos;
        }
    }

    playAnimation();
}

void Polygon::insertionSort() {
    setNumbersToSort(getRandomVector(numbersToSort.size()));

    int i, key, j;
    for (int i = 1; i < numbersToSort.size(); ++i) {
        key = numbersToSort[i];
        j = i - 1;
        while (j >= 0 && numbersToSort[j] >= key) {
            compareBars(j, i);
            numbersToSort[j+1] = numbersToSort[j];
            setBar(j+1, numbersToSort[j+1]);
            j = j - 1;
        }
        numbersToSort[j+1] = key;
        setBar(j+1, numbersToSort[j+1]);
    }

    playAnimation();
}

void Polygon::selectionSort() {
    setNumbersToSort(getRandomVector(numbersToSort.size()));
    int min_index;
    for (int i = 0; i < numbersToSort.size(); ++i) {
        min_index = i;
        for (int j = i + 1; j < numbersToSort.size(); ++j) {
            compareBars(j, min_index);
            if (numbersToSort[j] < numbersToSort[min_index]) {
                min_index = j;
            }
        }

        if (min_index != i) {
            std::swap(numbersToSort[min_index], numbersToSort[i]);
            swapBars(min_index, i);

        }
    }
    playAnimation();
}

void Polygon::quickSort(int start, int end) {
    if (start >= end)
        return;
    
    int p = quickSortPartition(start, end);
 
    // Sorting the left part
    quickSort(start, p - 1);
 
    // Sorting the right part
    quickSort(p + 1, end);
}


void Polygon::quickSort() {
    setNumbersToSort(getRandomVector(numbersToSort.size()));

    quickSort(0, numbersToSort.size() - 1);
    
    playAnimation();
    
}

int Polygon::quickSortPartition(int start, int end) {
    int pivot = numbersToSort[start];
 
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        compareBars(i, start);
        if (numbersToSort[i] <= pivot)
            count++;
    }
 
    // Giving pivot element its correct position
    int pivotIndex = start + count;
    std::swap(numbersToSort[pivotIndex], numbersToSort[start]);
    swapBars(pivotIndex, start);
 
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (numbersToSort[i] <= pivot) {
            i++;
            compareBars(i, pivotIndex);
        }
 
        while (numbersToSort[j] > pivot) {
            j--;
            compareBars(j, pivotIndex);
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            swapBars(i, j);
            std::swap(numbersToSort[i++], numbersToSort[j--]);
        }
    }
 
    return pivotIndex;
}

void Polygon::playAnimation() {
    for (int i = 0; i < bars.size(); ++i) {
        highlightBar(i, sf::Color::Red);
        paintBars();
        sound->setPitch(static_cast<float>(i)/static_cast<float>(numbersToSort.size()) * 3.0 + 1);
        sound->play();
        sf::sleep(sf::milliseconds(2));
    } 
}




vector <int> Polygon::getRandomVector(int size) {
    vector <int> numbers(size);
    for (int i = 0; i < size; ++i) {
        numbers[i] = i + 1;
    }

    shuffleNumbers(numbers);


    return numbers;
}

void Polygon::shuffleNumbers(vector <int> &numbers) {
    std::random_device rnd_device;
    std::mt19937 mersenne_engine {rnd_device()};

    std::shuffle(begin(numbers), end(numbers), mersenne_engine);
}

void Polygon::setNumbersToSort(vector <int> newNumbers) {
    numbersToSort.clear();
    numbersToSort = newNumbers;
    updateBars();
    
}

void Polygon::updateBars() {
    bars.clear();
    int rectWidth = (static_cast<float>(width)) / static_cast<float>(numbersToSort.size());
    for (int i = 0; i < numbersToSort.size(); ++i) {
        sf::RectangleShape rect;
        const int rectHeight = (static_cast<float>(height) * 0.9)/static_cast<float>(numbersToSort.size())*static_cast<float>(numbersToSort[i]);
        const int rectX = i * rectWidth;
        const int rectY = (height - rectHeight);

        rect.setSize(sf::Vector2f(rectWidth, rectHeight));
        rect.setPosition(sf::Vector2f(rectX, rectY));
        rect.setFillColor(sf::Color::White);
        bars.push_back(rect);
    }
}
