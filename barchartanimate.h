//
// barchartanimate.h
// Object to hold all the gathered frames from the data file and display to console with color
//

#include <iostream>// cin/cout
#include <fstream> // file stream
#include <sstream> // output stream
#include <string> // string functions
#include <algorithm> // for sort()
#include <map> // for colormap
#include <vector> // for color vector
#include <unistd.h>
#include <cstdlib>
#include "myrandom.h" // used by graders, do not remove
#include "barchart.h" // using barchart objects
  
using namespace std;

// BarChartAnimate
class BarChartAnimate {
 private:
    BarChart* barcharts;  // pointer to a C-style array of barcharts
    int size; // size of the current barchart array
    int capacity; // max size of the current barchart array
    map<string, string> colorMap; // colorMap used to match categories with color

    // hold general info about the data file
    string title;
    string xlabel;
    string source;

 public:
    // a parameterized constructor
    // barcharts initialized with 4 empty spaces and size 0 because empty
    BarChartAnimate(string title, string xlabel, string source) {

        barcharts = new BarChart[4];  // we start with a capacity of 4:
        size = 0;
        capacity = 4;

        this->title = title;
        this->xlabel = xlabel;
        this->source = source;
        
    }

    // destructor frees the memory created inside the barcharts array
    virtual ~BarChartAnimate() {
        if(barcharts != nullptr)  // checks if data in the array
            delete[] barcharts;
    }

    // adds a new BarChart to the BarChartAnimate object from the file stream
    void addFrame(ifstream &file) {
        if (size == capacity) { // first checks if the array is full, doubles capacity if full
            int newCapacity = capacity * 2;
            BarChart* newBarCharts = new BarChart[newCapacity];

            // copy the elements to the new array:
            for (int i = 0; i < size; ++i)
                newBarCharts[i] = barcharts[i];

            // delete old array and update new array
            delete[] barcharts;
            barcharts = newBarCharts;
            capacity = newCapacity;
        }

        // gets the frameSize value and creates a BarChart
        string curLine;
        int frameSize, colorCounter = 0;
        getline(file, curLine);
        getline(file, curLine);
        if(curLine == "") // if the end of the file, return
            return;
        frameSize = stoi(curLine);
        BarChart curFrame(frameSize);

        // holds the data members for each bar
        string name, category, frame;
        int value;
        for(int i = 0; i < frameSize; i++){ // loops until the frame ends
            getline(file, curLine);
            frame = curLine.substr(0, curLine.find(',')); // string manip. to get frame

            curLine = curLine.substr(curLine.find(',')+1, curLine.size()+1);
            name = curLine.substr(0, curLine.find(',')); // string manip. to get name

            curLine = curLine.substr(curLine.find(',')+1, curLine.size()+1);
            curLine = curLine.substr(curLine.find(',')+1, curLine.size()+1); // skips 4th value
            value = stoi(curLine.substr(0, curLine.find(','))); // string manip. to get value

            category = curLine.substr(curLine.find(',')+1); // string manip. to get category

            if(!colorMap.count(category)){ // builds colorMap with NEW category value
                if(colorCounter >= COLORS.size()){ // loops to beginning once colors were all filled
                    colorCounter = 0;
                }
                colorMap.emplace(category, COLORS[colorCounter]);
                colorCounter++;
            }
            curFrame.addBar(name, value, category); // adds bar with the values obtained from file to barChart object
        }
        curFrame.setFrame(frame); // sets the frame value for this frame
        barcharts[size] = curFrame; // adds current frame(barchart) to array of gathered frames(barcharts)
        size++;
    }

    // this function plays each frame stored in barcharts
    // stores into output stream, given the number of bars to display (top) and how many frames to display (endIter)
	void animate(ostream &output, int top, int endIter) {
		unsigned int microsecond = 50000;
        if(endIter == -1) // displays all the frames stored in array
            endIter = getSize();

        for(int i = 0; i < endIter; i++){ // displays each frame along with the file info
            usleep(3 * microsecond); // pauses inbetween frames for readability
            output << CLEARCONSOLE; // wipes screan
            output << RESET << title << endl << source << endl;
            barcharts[i].graph(output, colorMap, top); // graphs each barchart
            output << RESET << xlabel << endl << "Frame: " << barcharts[i].getFrame() << endl;
        }
	}

    // *CREATIVE COMPONENT* overloaded function with speed to change how fast the user wants the frames displayed
    void animate(ostream &output, int top, int endIter, double speed) {
        unsigned int microsecond = 50000;
        if(endIter == -1)
            endIter = getSize();

        for(int i = 0; i < endIter; i++){
            usleep(speed * microsecond);
            output << CLEARCONSOLE;
            output << RESET << title << endl << source << endl;
            barcharts[i].graph(output, colorMap, top);
            output << RESET << xlabel << endl << "Frame: " << barcharts[i].getFrame() << endl;
        }
    }

    // Returns the size of the BarChartAnimate object.
    int getSize(){ return size; }

    // Returns BarChart element in BarChartAnimate if inbounds
    BarChart& operator[](int i){
        if (i < 0 || i >= size)
            throw out_of_range("BarChart: i out of bounds");

        return barcharts[i];
    }
};
