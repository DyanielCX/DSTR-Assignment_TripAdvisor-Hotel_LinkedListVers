#ifndef DATAREFRESH_MENU_HPP
#define DATAREFRESH_MENU_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include "ReadInput.hpp"
using namespace std;
using namespace chrono;

inline void timeUsedShow(high_resolution_clock::time_point start, high_resolution_clock::time_point end);


inline void refreshData(ReviewAndRating*& RevRat_Head, ReviewAndRating*& RevRat_Tail, PowWord*& POS_Head, PowWord*& POS_Tail, NegWord*& NEG_Head, NegWord*& NEG_Tail, const int CSV_lines, const int POS_WORDS, const int NEG_WORDS) {
    
    int program;
    ReadFile fileReader;

    while (true) {
        // Title design
        cout << "\n \n \n";
        cout << "\033[0;34m"; // Set the text color to bright blue
        cout << "---------------------------------------" << endl;
        cout << "             Data Refresh              " << endl;
        cout << "---------------------------------------" << endl;
        cout << "\033[0m";
        cout << "\n";

        cout << "Choose the data that you want to refresh" << endl;
        cout << "1. Review & Rating" << endl;
        cout << "2. Positive words" << endl;
        cout << "3. Negative words" << endl;
        cout << "0. Back to main" << endl;
        cout << "Enter number: ";
        cin >> program;


        switch (program) {
        case 1: // Refresh CSV File
            {
                auto startCSV = high_resolution_clock::now();    // Start the timer
                if (fileReader.readCSV(RevRat_Head, RevRat_Tail, CSV_lines)) {
                    cout << "<-- The review & rating array is refreshed -->" << endl;
                    auto endCSV = high_resolution_clock::now();  // End the timer

                    // Calculate & display time used
                    timeUsedShow(startCSV, endCSV);
                }
                continue;
            }

        case 2: // Refresh Positive Word Text File
            {
                auto startPos = high_resolution_clock::now();
                if (fileReader.readPositiveWords(POS_Head, POS_Tail, POS_WORDS)) {
                    cout << "<-- The positive word array is refreshed -->" << endl;
                    auto endPos = high_resolution_clock::now();

                    timeUsedShow(startPos, endPos);
                }
                continue;
            }

        case 3: // Refresh Negative Word Text File
            {
                auto startNeg = high_resolution_clock::now();
                if (fileReader.readNegativeWords(NEG_Head, NEG_Tail, NEG_WORDS)) {
                    cout << "<-- The negative word array is refreshed -->" << endl;
                    auto endNeg = high_resolution_clock::now();

                    timeUsedShow(startNeg, endNeg);
                }
                continue;
            }

        case 0: // Refresh Negative Word Text File
            cout << "\n \n";
            break;

        default:    // Re-prompt the user option
            cout << "Invalid option!\n" << endl;
            continue;
        }

        break;  // Back to main page
    }

    return;
}

// Display time used function
inline void timeUsedShow(high_resolution_clock::time_point start, high_resolution_clock::time_point end) {
    auto duration = duration_cast<milliseconds>(end - start);

    int milliseconds = duration.count() % 1000;

    cout << "\nTime taken: " << milliseconds << " milliseconds " << endl;
}

#endif 