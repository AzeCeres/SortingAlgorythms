#include <iostream>
#include <array>
#include <random>
#include <chrono>
using namespace std;
using namespace chrono;
int const SIZE = 50000;
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
void Sorter(array<int, SIZE>& arrayIn){
    int prevVal{INT_MIN};
    while(!isSorted(arrayIn)){
        for (int i = 0; i < arrayIn.size(); ++i) {
            if (i == 0) {
                prevVal = arrayIn.at(i);
                continue;
            }
            if (arrayIn.at(i) < prevVal){
                arrayIn.at(i-1) = arrayIn.at(i);
                arrayIn.at(i) = prevVal;
            }
            prevVal = arrayIn.at(i);
        }
    }
}
void
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
char Options(string questionText, int nrOfOptions, char option1, char option2, char option3){
    char answer{'x'};
    while  (answer != option1 && answer != char(toupper(option1)) &&
            answer != option2 && answer != char(toupper(option2)) &&
            answer != option3 && answer != char(toupper(option3))) {

        cout << questionText << " " << option1 << "/" << option2;
        if(nrOfOptions == 3)
            cout << "/" << option3;
        cout << " ? \n";
        cin >> answer;
        if (answer == option1 || answer == char(toupper(option1))) {

        } else if (answer == option2 || answer == char(toupper(option2))) {

        } else if (answer == option3 && nrOfOptions>2 || answer == char(toupper(option3)) && nrOfOptions>2) {

        } else {
            cout << "Please enter a valid option.\n";
        }
    }
    if (char(tolower(answer)) == option1 || char(tolower(answer)) == option2){
        answer = char(tolower(answer));
    }
    return answer;
}
/**
 *
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
        if(Options(questionText, 2, 'y', 'n', ' ') == 'n') {
            runSortingAlgorithm = false;
            break;
        }
        array<int, SIZE> intArray = initializeRandomList();
        //PrintList(intArray);
        questionText = "Do you want to sort with 1: Bubble Sort, or 2: Gnome Sort";
        char SorterToUse = 0;
        SorterToUse = Options(questionText, 3, '1', '2', '3');
        auto startTime = high_resolution_clock::now();
        if(SorterToUse == '1'){
            Sorter(intArray);
        } else if (SorterToUse == '2'){
            GnomeSorter(intArray);
        }
        cout << "List is Sorted: " << isSorted(intArray) << endl;
        cout << "Time Taken: "<< TimeTaken(startTime).count() << " ms\n" << "Size of Array: " << SIZE << endl;
        //PrintList(intArray);
    }
    return 0;
}
