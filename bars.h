#ifndef BARS_H
#define BARS_H

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using std::vector;

enum SORT_TYPE {BUBBLE, INSERTION, SELECTION, QUICK, GNOME, STOOGE, MERGE, BOGO};
enum OPERATION_TYPE {COMPARE, COMPARE_TO_VALUE, UPDATE, SWAP};

static std::map <std::string, SORT_TYPE> sortTypeToStringMap{
  {"bubble", BUBBLE},
  {"sinking", BUBBLE},
  {"insertion", INSERTION},
  {"selection", SELECTION},
  {"stooge", STOOGE},
  {"gnome", GNOME},
  {"bogo", BOGO},
  {"permutation", BOGO},
  {"quick", QUICK},
  {"merge", MERGE}
};

class Bars {
public:
    explicit Bars();
    ~Bars();

    void performSort(SORT_TYPE sortType);
    void performSort(std::string sortType);

    void setBarsAmount(int newAmount) {barsAmount = newAmount;}
    void setWaitTime(int newWaitTime) {waitTimeMc = newWaitTime;}
    void setBarsValues(const vector <int> &newBarsValues);
private:
    void bubbleSort();
    void insertionSort();
    void selectionSort();
    inline void quickSort();
    void gnomeSort();
    inline void stoogeSort();
    inline void mergeSort();
    inline void bogoSort();

    void quickSort(int start, int end);
    void stoogeSort(int start, int end);
    void mergeSort(int start, int end);
    void merge(int start, int mid, int end);
    bool bogoCheckSorted();
    int quickSortPartition(int start, int end);


    void animateSortEnding();

    int performOperation(OPERATION_TYPE operationType, int firstValue, int secondValue);
    int compare(int firstIndex, int secondIndex);
    int compareToValue(int index, int value);
    int swap(int firstIndex, int secondIndex);
    int update(int index, int value);
    
    void highlightBar(int index, sf::Color color);
    void fillBarsRectangles();
    void paintBars();
    void paintBars(vector <int> indexes, sf::Color);
    void paintBar(int index, sf::Color);

    vector <int> getRange(int startingNumber, int endingNumber);
    vector <int> getRandomShuffledRange(int startingNumber, int endingNumber);
    inline SORT_TYPE getSortTypeFromString(std::string str);

    inline void playSound(int value);
    void processWinOperations();

    sf::RenderWindow *win;
    sf::Sound *sound;
    sf::SoundBuffer *buffer;

    sf::Color compareColor, backColor, swapColor, updateColor, defaultColor, finalColor;

    vector <sf::RectangleShape> barsRectangles;
    vector <int> barsValues;
    vector <int> lastChangedBars;

    std::string winTitle;

    short barsAmount;
    int waitTimeMc;

    short winWidth, winHeight;
    short winStartingX, winStartingY;
};

#endif