//
// bar.h
// Class to hold the data for each bar object which makes up the frame (BarChart)
// which makes up the animation (BarChartAnimate)

#include <iostream> // cin/cout
#include <string> // string manipulation
#include "myrandom.h" // used in graders, do not remove
using namespace std;

class Bar {
 private:
    string name; // name of bar
    int value; // value of bar
    string category; // category of bar
 public:
    // default constructor with default values
    Bar() {
        name = "";
        value = 0;
        category = "";
    }
    // Parameter passed in constructor Bar object.
    Bar(string name, int value, string category) {
        this->name = name;
        this->value = value;
        this->category = category;
    }

    // destructor:
    virtual ~Bar() { }

    // returns the name of bar object
	string getName() { return name; }

    // returns the value of bar object
	int getValue() { return value; }

    // returns the category of bar object
	string getCategory() { return category; }

    // This allows you to compare two Bar objects
    // used to sort in barchart.h
	bool operator<(const Bar &other) const {
        return this->value < other.value;
	}

	bool operator>(const Bar &other) const {
        return this->value > other.value;
	}

    bool operator<=(const Bar &other) const {
        if(*this < other || this->value == other.value) // calls greater than operator
            return true;
        else
            return false;
    }

	bool operator>=(const Bar &other) const {
        if(*this > other || this->value == other.value) // calls less than operator
            return true;
        else
            return false;
	}
};

