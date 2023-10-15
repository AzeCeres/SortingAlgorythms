#include <iostream>
#include <array>
#include <random>
#include <chrono>
using namespace std;
using namespace chrono;
int const SIZE = 10000;
/**
 * Creates a random seed based on the system clock
 * Fills an array based on an arbitrary random range
 * returns the filled Array
 * @return
 */
array<int, SIZE> initializeRandomList(){
    array<int, SIZE> newArray;
    unsigned seed = system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    uniform_int_distribution<int> distribution(-10000,10000);
    for (int i = 0; i < newArray.size(); ++i) {
        newArray[i] = distribution(generator);
    }
    return newArray;
}
/**
 * Prints the array in its current state, does not modify the array.
 * @param arrayIn
 */
void PrintList(array<int, SIZE> arrayIn){
    for (int i = 0; i < arrayIn.size(); ++i) {
        cout << arrayIn[i] << " ";
    }
    cout << std::endl;
}
auto TimeTaken(time_point<system_clock, duration<long long, ratio<1, 1000000000>>> timeIn){
    auto timeNow = high_resolution_clock::now();

    duration<double, milli> ms_double = timeNow - timeIn;
    return ms_double;
}

template<size_t SIZE>
int MinIndex(array<int, SIZE> arrayIn, size_t i, size_t j){
    if (i == j)
        return i;
    if (i > j) {
        // Return a value that indicates an error or an invalid index
        return -1;
    }
    // Find the smallest element index in rest of the array
    int k = MinIndex(arrayIn, i + 1, j);
    // Return the smallest element of current and rest
    if (k == -1 || arrayIn[i] < arrayIn[k]) {
        return i;
    } else {
        return k;
    }
}

/**
 * Recursive Selection Sort
 * @param arrayIn
 * @param index
 */
template<size_t SIZE>
void recursiveSelectionSort(array<int, SIZE>& arrayIn, size_t index = 0){
    // Return when index is equal to size of array (Has reached the end)
    if (index >= SIZE)
        return;
    // Find minimum index
    int k = MinIndex(arrayIn, index, SIZE-1);
    // Swapping when current index and the minimum index aren't the same
    if (k != -1 && k != index)
        swap(arrayIn.at(k), arrayIn.at(index));
    // Recursively calling itself
    recursiveSelectionSort(arrayIn, index + 1);
}
/**
 * Goes through the array to check if the array is sorted.
 * Makes sure that the first index is the lowest, and that the last is the highest.
 * @param arrayIn
 * @return
 */
bool isSorted(array<int, SIZE> arrayIn){
    bool isSorted{true};
    if (arrayIn.size() == 1 || arrayIn.size() == 0)
        return isSorted;
    int prevVal{INT_MIN};
    int curLowestVal{INT_MAX};
    int curHighestVal{INT_MIN};
    for (int i = 0; i < arrayIn.size(); ++i) {
        //lowest value have to be set at the beginning, no value shall be lower than it, highest value should either remain the same or get higher as the list continues.
        if (i == 0) {
            prevVal = arrayIn.at(i);
            curLowestVal = prevVal;
            curHighestVal = prevVal;
            continue;
        }
        if (arrayIn.at(i) >= curHighestVal) {
            curHighestVal = arrayIn.at(i);
        } else{
            isSorted = false;
            break;
        }
        if (arrayIn.at(i) >= curLowestVal && arrayIn.at(i) >= prevVal){
            continue;
        } else{
            isSorted = false;
            break;
        }
    }
    return isSorted;
}
void BubbleSorter(array<int, SIZE>& arrayIn){
    int prevVal{INT_MIN};
    bool switchedValues{true};
    while(switchedValues){
        switchedValues = false;
        for (int i = 0; i < arrayIn.size(); ++i) {
            if (i == 0) {
                prevVal = arrayIn.at(i);
                continue;
            }
            if (arrayIn.at(i) < prevVal){
                switchedValues = true;
                swap(arrayIn.at(i-1), arrayIn.at(i));
            }
            prevVal = arrayIn.at(i);
        }
    }
}
template<size_t SIZE>
/**
 * Recursive Bubble Sort
 * @param arrayIn
 * @param size
 */
void recursiveBubbleSort(std::array<int, SIZE>& arrayIn, size_t size = SIZE) {
    // Base case: If the size of the remaining portion is 1, the array is sorted.
    if (size == 1) {
        return;
    }
    for (size_t i = 0; i < size - 1; ++i) {
        if (arrayIn[i] > arrayIn[i + 1]) {
            std::swap(arrayIn[i], arrayIn[i + 1]);
        }
    }
    // Recursive call on the smaller array (excluding the last element, which is the largest).
    recursiveBubbleSort(arrayIn, size - 1);
}
/**
 * Lets the user provide input. And sends it forward.
 * Does error checking, such as disregarding non answers
 * Returns a lowercase char (numbers have to be numbers)
 * @param questionText
 * @param nrOfOptions
 * @param option1
 * @param option2
 * @param option3
 * @return
 */
//make it take in a string, and then a vector of chars, and then check if the input is in the vector.
char Options(string questionText, vector<char>& options){
    char answer{' '};
    while (true) {
        std::cout << questionText << " (";
        for (size_t i = 0; i < options.size(); ++i) {
            std::cout << options[i];
            if (i < options.size() - 1) {
                std::cout << "/";
            }
        }
        std::cout << ") ? \n";

        std::cin >> answer;

        for (char option: options) {
            if (std::tolower(answer) == std::tolower(option)) {
                return std::tolower(answer);
            }
        }
    }
}
/**
 * Gnome Sorter, goes down the line comparing the current value with the previous value.
 * If the previous value is higher, it swaps the two values and goes back one step.
 * If the previous value is lower, it goes forward one step.
 * @param arrayIn
 */
void GnomeSorter(array<int, SIZE>& arrayIn){
    int index = 0;
    while(index < arrayIn.size()){
        if (index == 0)
            index++;
        if (arrayIn.at(index)>= arrayIn.at(index-1))
            index++;
        else{
            swap(arrayIn.at(index),arrayIn.at(index-1));
            index--;
        }
    }
}
/**
 *
 * @return
 */
int main() {
    bool runSortingAlgorithm{true};
    while (runSortingAlgorithm){
        string questionText = "Do you want to sort an array of size: " + to_string(SIZE);
        vector<char> ansOptions{'y', 'n'};
        if(Options(questionText, ansOptions) == 'n') {
            runSortingAlgorithm = false;
            break;
        }
        array<int, SIZE> intArray = initializeRandomList();
        //PrintList(intArray);
        questionText = "Do you want to sort with 1: Bubble Sort, 2: Gnome Sort, 3: Recursive Selection Sort?, or 4: Recursive Bubble Sort";
        char SorterToUse = 0;
        ansOptions = {'1', '2', '3', '4'};
        SorterToUse = Options(questionText, ansOptions);
        auto startTime = high_resolution_clock::now();
        if(SorterToUse == '1'){
            BubbleSorter(intArray);
        } else if (SorterToUse == '2'){
            GnomeSorter(intArray);
        } else if (SorterToUse == '3'){
            recursiveSelectionSort(intArray);
        } else if (SorterToUse == '4'){
            recursiveBubbleSort(intArray);
        }
        cout << "List is Sorted: " << isSorted(intArray) << endl;
        cout << "Time Taken: "<< TimeTaken(startTime).count() << " ms\n" << "Size of Array: " << SIZE << endl;
        //PrintList(intArray);
    }
    return 0;
}
