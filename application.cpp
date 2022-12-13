//
// Bar Chart Animation: This application uses BarChartAnimate (which uses BarChart, which uses Bar)
// to produce an animated bar chart.
//
// Creative Component: user can enter the desired speed they would like to see the frames output
// animate is overloaded with the parameter "double speed" to vary the speed
//
// Tyler Strach
// U. of Illinois, Chicago
// Fall 2022
//
// Original iteration of program developed by:
// Shanon Reckinger
// U. of Illinois, Chicago 

#include <iostream>
#include <map>
#include "barchartanimate.h"
using namespace std;

// runs the application to produce the animated barchart
int main() {
    string filename; // user-input file
    double speed; // user-input speed
    bool isIn = false;

	string files[11] = {"baby-names.txt", "brands.txt", "cities-us.txt", "cities.txt",
                      "countries.txt", "endgame.txt", "football.txt", "infinity-war.txt",
                      "movies.txt", "patents.txt", "trademarks.txt"};

    for(string &str : files) // outputs all possible file names
        cout << "\"" << str << "\"" << endl;

    do{ // gets a valid file from the user
        cout << "Chose a file to display: ";
        cin >> filename;
        for(string &str : files){
            if(filename == str)
                isIn = true;
        }
    }
    while(!isIn);

    // gets output speed from user
    cout << "Choose desired decimal speed (0.1-5.0 with 0.1 being the fastest, 3.0 default, 5.0 being the slowest): ";
    cin >> speed;

    // opens the file and gathers general file info
	ifstream inFile(filename);
	string title;
	getline(inFile, title);
	string xlabel;
	getline(inFile, xlabel);
	string source;
	getline(inFile, source);

	BarChartAnimate bca(title, xlabel, source); // creates new object to animate the data
	
	while (!inFile.eof()) { // add frames until the end of file
		bca.addFrame(inFile);
	}
	bca.animate(cout, 12, -1, speed); // animates the frames gathered

    return 0;
}
