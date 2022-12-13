//
// barchart.h
// Object that holds the data for a specific barchart (frame) of data
// File also contains all the constant color values used for graph()
//

#include <iostream> // cout/cin
#include <algorithm> // for sort()
#include <map> // for colormap
#include "myrandom.h" // used in graders, do not remove
#include "bar.h" // uses bar objects

using namespace std;

// Constants used for bar chart animation.
const string BOX = "\u29C8";
const string CLEARCONSOLE = "\033[2J";


// NOTE: COMMENT AND UNCOMMENT AS NEEDED BASED ON YOUR TERMINAL

// Color codes for LIGHT mode terminals
// const string RED("\033[1;36m");
// const string PURPLE("\033[1;32m");
// const string BLUE("\033[1;33m");
// const string CYAN("\033[1;31m");
// const string GREEN("\033[1;35m");
// const string GOLD("\033[1;34m");
// const string BLACK("\033[1;37m");
// const vector<string> COLORS = {RED, PURPLE, BLUE, CYAN, GREEN, GOLD, BLACK};

// Color codes for DARK mode terminals
const string CYAN("\033[1;36m");
const string GREEN("\033[1;32m");
const string GOLD("\033[1;33m");
const string RED("\033[1;31m");
const string PURPLE("\033[1;35m");
const string BLUE("\033[1;34m");
const string WHITE("\033[1;37m");
const string RESET("\033[0m");
const vector<string> COLORS = {CYAN, GREEN, GOLD, RED, PURPLE, BLUE, WHITE};

// BarChart
class BarChart {
 private:
    Bar* bars;  // pointer to a C-style array of bar objects
    int capacity; // max size of bars
    int size; // current size of bars
    string frame; // description of current frame

 public:
    // default constructor: sets to default values
    BarChart() {
        bars = nullptr;
        capacity = 0;
        size = 0;
        frame = "";
    }

    // parameterized constructor:
    // Parameter passed in determines memory allocated for bars.
    BarChart(int n) {
        bars = new Bar[n]; // creates n many bars
        capacity = n; // updates capacity
        size = 0;
        frame = "";
    }

    // copy constructor:
    // copies values into identical new barchart
    BarChart(const BarChart& other) {
        this->bars = new Bar[other.capacity];
        this->capacity = other.capacity;
        this->size = other.size;
        this->frame = other.frame;

        for(int i = 0; i < other.size; i++){
            this->bars[i] = other.bars[i];
        }
    }

    // copy operator=
    BarChart& operator=(const BarChart& other) {
        if (this == &other) // if already the same
            return *this;

        delete[] this->bars; // deletes the old array

        // sets the old values to the other BarChart values
        this->bars = new Bar[other.capacity];
        this->capacity = other.capacity;
        this->size = other.size;
        this->frame = other.frame;

        for(int i = 0; i < other.size; i++){
            this->bars[i] = other.bars[i];
        }

        return *this; // returns the updated BarChart object
    }

    // frees memory and resets all private member variables to default values.
    void clear() {
        delete[] this->bars;
        this->bars = nullptr;
        capacity = 0;
        size = 0;
        frame = "";
    }

    // destructor: destroys the values in bars array
    virtual ~BarChart() {
        if(bars != nullptr)
            delete[] bars;
    }

    // sets the frame of the BarChart object.
    void setFrame(string frame) { this->frame = frame; }

    // returns the frame of the BarChart object.
    string getFrame() { return frame; }

    // Returns the size (number of bars) of the BarChart object.
    int getSize() { return size; }

    // adds a Bar to the BarChart.
    // returns true if successful
    // returns false if there is no room
    bool addBar(string name, int value, string category) {
        if(size < capacity){
            bars[size] = Bar(name, value, category);
            size++;
            return true;
        }
        else
            return false;
    }

    // returns BarChart element in BarChartAnimate if inbounds
    Bar& operator[](int i) {
        if (i < 0 || i >= size)
            throw out_of_range("BarChart: i out of bounds");

        return bars[i];
    }

    // used for printing the BarChart object / debugging purposes
    void dump(ostream &output) {
        string barInfo;
        barInfo = "frame: " + this->frame + "\n";
        output << barInfo; // stores frame value
        for(int i = 0; i < size; i++){ // for all the bars, adds to the string with spaces
            barInfo.clear();
            barInfo += bars[i].getName() + " ";
            barInfo += to_string(bars[i].getValue()) + " ";
            barInfo += bars[i].getCategory() + "\n";

            output << barInfo; // stores the values
        }
    }

    // used for printing out the bar.
    // output is any stream (cout, file stream, string stream)
    // colorMap maps category -> color
    // top is number of bars you'd like plotted on each frame (top 10? top 12?)
    void graph(ostream &output, map<string, string> &colorMap, int top) {
    	int lenMax = 60;  // this is number of BOXs that should be printed for the top bar (max value)
        sort(bars, bars + size, greater<Bar>()); // sorts the bars in bars from greatest to least

        string color, boxes; // color and boxes for specific bar
        double numBoxes; // num of boxes
        for(int i = 0; i < size; i++){ // for all the elements in bars
            if(i > top-1) // stops at the top value (top 10, 11, 12 etc)
                break;

            boxes = ""; // resets boxes for each bar
            color = colorMap.at(bars[i].getCategory()); // gets color from colormap
            numBoxes = ( double(bars[i].getValue()) / bars[0].getValue() ) * lenMax; // calculates the num of boxes
            for(int j = 0; j < int(numBoxes); j++) // adds correct boxes to string
                boxes += BOX;

            // stores completed colored string into output
            output << color << boxes << " " << bars[i].getName() <<  " " << bars[i].getValue() << endl;
        }
    }
};

