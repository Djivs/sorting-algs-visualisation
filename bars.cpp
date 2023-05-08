#include <random>
#include <algorithm>
#include <functional>
#include <iostream>

#include "bars.h"

Bars::Bars() {
    buffer = new sf::SoundBuffer;
    sound = new sf::Sound;

    buffer->loadFromFile("beep.wav");
    sound->setBuffer(*buffer);
    sound->setVolume(100);

    winWidth = 1000;
    winHeight = 500;
    winStartingX = winStartingY = 0;

    winTitle = "Sorting algorithms visualisation";

    win = new sf::RenderWindow(sf::VideoMode(winWidth, winHeight), winTitle);

    barsAmount = 500;

    compareColor = sf::Color::Magenta;
    backColor = sf::Color::Black;
    swapColor = sf::Color::Green;
    updateColor = sf::Color::Blue;
    defaultColor = sf::Color::White;
    finalColor = sf::Color::Red;
}

Bars::~Bars() {
    win->close();

    delete win;
    delete buffer;
    delete sound;
}

void Bars::performSort(SORT_TYPE sortType) {
    setBarsValues(getRandomShuffledRange(1, barsAmount));

    void (Bars::*sortFunc)();
    switch(sortType) {
        case BUBBLE:
            sortFunc = &Bars::bubbleSort;
        break;
        case INSERTION:
            sortFunc = &Bars::insertionSort;
        break;
        case SELECTION:
            sortFunc = &Bars::selectionSort;
        break;
        case QUICK:
            sortFunc = &Bars::quickSort;
        break;
        case GNOME:
            sortFunc = &Bars::gnomeSort;
        break;
        case STOOGE:
            sortFunc = &Bars::stoogeSort;
        break;
        case MERGE:
            sortFunc = &Bars::mergeSort;
        break;
        case BOGO:
            sortFunc = &Bars::bogoSort;
        break;
        }
    std::invoke(sortFunc, this);

    animateSortEnding();
}

void Bars::bubbleSort() {
    for (int i = 0; i < barsAmount - 1; ++i) {
        for (int j = 0; j < barsAmount - i -1; ++j) {
            if (performOperation(COMPARE, j, j + 1) == 1) {
                performOperation(SWAP, j, j+1);
            }
        }
    }       
}
void Bars::insertionSort() {
    int key, j;
    for (int i = 1; i < barsAmount; ++i) {
        j = i - 1;
        key = barsValues[i]; 
        while (j >= 0 && performOperation(COMPARE_TO_VALUE, j, key) != -1) {
            performOperation(UPDATE, j+1, barsValues[j]);
            --j;
        }
        performOperation(UPDATE, j+1, key);
    }
}
void Bars::selectionSort() {
    int minIndex;
    for (int i = 0; i < barsAmount; ++i) {
        minIndex = i;
        for (int j = i + 1; j < barsAmount; ++j) {
            if (performOperation(COMPARE, j, minIndex) == -1) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            performOperation(SWAP, minIndex, i);
        }
    }
}
inline void Bars::quickSort() {
    quickSort(0, barsAmount - 1);
}
void Bars::gnomeSort() {
    int pos = 0;
    while (pos < barsAmount) {
        if (pos == 0 || performOperation(COMPARE, pos, pos - 1) != -1) {
            ++pos;
        } else {
            performOperation(SWAP, pos, pos-1);
            --pos;
        }
    }
}
inline void Bars::stoogeSort() {
    stoogeSort(0, barsAmount - 1);
}
inline void Bars::mergeSort() {
    mergeSort(0, barsAmount - 1);
}
inline void Bars::bogoSort() {
    while (!bogoCheckSorted()) {
        setBarsValues(getRandomShuffledRange(1, barsAmount));
        paintBars();
    }
}

void Bars::animateSortEnding() {
    for (int i = 0; i < barsAmount; ++i) {
        highlightBar(i, finalColor);
        paintBars();
        playSound(i);
        sf::sleep(sf::milliseconds(1));
    } 
}

int Bars::performOperation(OPERATION_TYPE operationType, int firstValue, int secondValue) {
    int (Bars::*operationFunc)(int, int);
    int soundValue;
    switch(operationType) {
    case COMPARE:
        soundValue = barsValues[secondValue];
        operationFunc = &Bars::compare;
        break;
    case COMPARE_TO_VALUE:
        soundValue = barsValues[firstValue];
        operationFunc = &Bars::compareToValue;
        break;
    case UPDATE:
        soundValue = barsValues[secondValue];
        operationFunc = &Bars::update;
        break;
    case SWAP:
        soundValue = barsValues[secondValue];
        operationFunc = &Bars::swap;
        break;
    }

    playSound(soundValue);
    return std::invoke(operationFunc, this, firstValue, secondValue);
}

int Bars::compare(int firstIndex, int secondIndex) {
    const int firstNumber = barsValues[firstIndex];
    const int secondNumber = barsValues[secondIndex];



    highlightBar(firstIndex, compareColor);
    highlightBar(secondIndex, compareColor);
    paintBars();
    highlightBar(firstIndex, defaultColor);
    highlightBar(secondIndex, defaultColor);

    if (firstNumber > secondNumber) {
        return 1;
    }
    if (firstNumber < secondNumber) {
        return -1;
    }
    return 0;
}

int Bars::compareToValue(int index, int value) {
    highlightBar(index, compareColor);
    paintBars();
    highlightBar(index, defaultColor);

    if (barsValues[index] > value) {
        return 1;
    }
    if (barsValues[index] < value) {
        return -1;
    }
    return 0;
}

int Bars::swap(int firstIndex, int secondIndex) {
    std::swap(barsValues[firstIndex], barsValues[secondIndex]);

    const auto firstSize = barsRectangles[firstIndex].getSize();
    barsRectangles[firstIndex].setSize(barsRectangles[secondIndex].getSize());
    barsRectangles[secondIndex].setSize(firstSize);

    barsRectangles[firstIndex].setPosition(barsRectangles[firstIndex].getPosition().x, winHeight - barsRectangles[firstIndex].getSize().y);
    barsRectangles[secondIndex].setPosition(barsRectangles[secondIndex].getPosition().x, winHeight - barsRectangles[secondIndex].getSize().y);


    highlightBar(firstIndex, compareColor);
    highlightBar(secondIndex, compareColor);
    paintBars();
    highlightBar(firstIndex, defaultColor);
    highlightBar(secondIndex,defaultColor);
    return 1;
}

int Bars::update(int index, int value) {
    barsValues[index] = value;

    const int rectHeight = (static_cast<float>(winHeight) * 0.9)/static_cast<float>(barsAmount)*static_cast<float>(value);

    barsRectangles[index].setSize(sf::Vector2f(barsRectangles[index].getSize().x, rectHeight));
    barsRectangles[index].setPosition(barsRectangles[index].getPosition().x, winHeight - barsRectangles[index].getSize().y);

    highlightBar(index, updateColor);
    paintBars();
    highlightBar(index, defaultColor);

    return 1;
}

void Bars::highlightBar(int index, sf::Color color) {
    barsRectangles[index].setFillColor(color);
    processWinClosing();
}

void Bars::fillBarsRectangles() {
    barsRectangles.clear();

    const int rectWidth = (static_cast<float>(winWidth)) / static_cast<float>(barsValues.size());

    for (int i = 0; i < barsValues.size(); ++i) {
        sf::RectangleShape rect;

        const int rectHeight = (static_cast<float>(winHeight) * 0.9)/static_cast<float>(barsValues.size())*static_cast<float>(barsValues[i]);
        const int rectX = winStartingX + i * rectWidth;
        const int rectY = winStartingY + (winHeight - rectHeight);

        rect.setSize(sf::Vector2f(rectWidth, rectHeight));
        rect.setPosition(sf::Vector2f(rectX, rectY));
        rect.setFillColor(sf::Color::White);
        barsRectangles.push_back(rect);
    }
}

void Bars::paintBars() {
    win->clear();

    for (auto &rect : barsRectangles) {
        win->draw(rect);
    }
    win->display();
}

vector <int> Bars::getRange(int startingNumber, int endingNumber) {
    vector <int> range;
    for (int i = startingNumber; i <= endingNumber; ++i) {
        range.push_back(i);
    }

    return range;
}
vector <int> Bars::getRandomShuffledRange(int startingNumber, int endingNumber) {
    auto range = getRange(startingNumber, endingNumber);

    std::random_device rnd_device;
    std::mt19937 mersenne_engine {rnd_device()};

    std::shuffle(begin(range), end(range), mersenne_engine);

    return range;
}

void Bars::setBarsValues(const vector <int> &newBarsValues) {
    barsValues = newBarsValues;

    fillBarsRectangles();
}

inline void Bars::playSound(int value) {
    sound->setPitch(static_cast<float>(value)/static_cast<float>(barsAmount) * 3.0 + 1);
    sound->play();
}

void Bars::processWinClosing() {
    sf::Event event;
    while (win->pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            win->close();
            exit(0);
        }
    }
}

void Bars::quickSort(int start, int end) {
    if (start >= end)
        return;
    
    int p = quickSortPartition(start, end);
 
    // Sorting the left part
    quickSort(start, p - 1);
 
    // Sorting the right part
    quickSort(p + 1, end);
}
void Bars::stoogeSort(int start, int end) {
    const int curLen = (end - start + 1);

    if (curLen == 2) {
        if (performOperation(COMPARE, start, end) == 1) {
            performOperation(SWAP, start, end);
        }
        return;
    }

    const int sortLen = ceil(curLen * 2.0 / 3.0) ;
    stoogeSort(start, start + sortLen - 1);
    stoogeSort(end - sortLen + 1, end);
    stoogeSort(start, start + sortLen - 1);
}
void Bars::mergeSort(int start, int end) {
    if (start >= end) {
        return;
    }

    const int mid = start + (end - start) / 2;
    mergeSort(start, mid);
    mergeSort(mid + 1, end);
    merge(start, mid, end);
}
void Bars::merge(int start, int mid, int end) {
    const int leftSubVecSize = mid - start + 1;
    const int rightSubVecSize = end - mid;

    vector <int> leftSubVec(leftSubVecSize);
    vector <int> rightSubVec(rightSubVecSize);

    for (int i = 0; i < leftSubVecSize; ++i) {
        leftSubVec[i] = barsValues[start + i];
    }
    for (int i = 0; i < rightSubVecSize; ++i) {
        rightSubVec[i] = barsValues[mid + 1 + i];
    }

    int leftIndex = 0, rightIndex = 0, mergedIndex = start;
    while (leftIndex < leftSubVecSize && rightIndex < rightSubVecSize) {
        if (leftSubVec[leftIndex] <= rightSubVec[rightIndex]) {
            performOperation(UPDATE, mergedIndex, leftSubVec[leftIndex]);
            leftIndex++;
        }
        else {
            performOperation(UPDATE, mergedIndex, rightSubVec[rightIndex]);
            rightIndex++;
        }
        mergedIndex++;
    }

    // Copy the remaining elements of
    // left[], if there are any
    while (leftIndex < leftSubVecSize) {
        performOperation(UPDATE, mergedIndex, leftSubVec[leftIndex]);
        leftIndex++;
        mergedIndex++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (rightIndex < rightSubVecSize) {
        performOperation(UPDATE, mergedIndex, rightSubVec[rightIndex]);
        rightIndex++;
        mergedIndex++;
    }
}
bool Bars::bogoCheckSorted() {
    for (int i = 1; i < barsAmount; ++i) {
        if (performOperation(COMPARE, i-1, i) == 1) {
            return false;
        }
    }
    return true;
}
int Bars::quickSortPartition(int start, int end) {
    int pivot = barsValues[start];

    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (performOperation(COMPARE_TO_VALUE, i, pivot) != 1)
            count++;
    }
 
    // Giving pivot element its correct position
    int pivotIndex = start + count;
    performOperation(SWAP,pivotIndex, start);
    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (performOperation(COMPARE_TO_VALUE, i, pivot) != 1) {
            ++i;
        }
 
        while (performOperation(COMPARE_TO_VALUE, j, pivot) == 1) {
            --j;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            performOperation(SWAP, i++, j--);
        }
    }
 
    return pivotIndex;
}
