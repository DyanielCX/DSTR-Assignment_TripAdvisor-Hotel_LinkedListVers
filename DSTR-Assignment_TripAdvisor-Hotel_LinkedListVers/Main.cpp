#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ReadInput.hpp"
#include "DataRefresh_Menu.hpp"
#include "RevAnalysis_Menu_Linear.hpp"
#include "RevAnalysis_Menu_Tenary.hpp"
#include "Summary.hpp"
using namespace std;

const int CSV_lines = 20491;    // Number of lines in the csv file
const int POS_WORDS = 2008;     // Number of positive words in the text file
const int NEG_WORDS = 4785;     // Number of negative words in the text file

int main() {
    int program;
    ReadFile fileReader;

    // Default data load
    ReviewAndRating* RevRat_Head = nullptr;
    ReviewAndRating* RevRat_Tail = nullptr; 
    PowWord* POS_Head = nullptr;
    PowWord* POS_Tail = nullptr;
    NegWord* NEG_Head = nullptr;
    NegWord* NEG_Tail = nullptr;

    fileReader.readCSV(RevRat_Head, RevRat_Tail, CSV_lines);
    fileReader.readPositiveWords(POS_Head, POS_Tail, POS_WORDS);
    fileReader.readNegativeWords(NEG_Head, NEG_Tail, NEG_WORDS);

    // Logo
    cout << "\n";
    cout << "\033[1;31m";  // Set the text color to bright red
    cout << "*************************************************************" << endl;
    cout << "*          T R I P A D V I S O R   H O T E L                *" << endl;
    cout << "*                                                           *" << endl;
    cout << "*     /$$$$$$$$        /$$            /$$$$$$        /$$    *" << endl;
    cout << "*    |__  $$__/       |__/           /$$__  $$      | $$    *" << endl;
    cout << "*       | $$  /$$$$$$  /$$  /$$$$$$ | $$  \\ $$  /$$$$$$$    *" << endl;
    cout << "*       | $$ /$$__  $$| $$ /$$__  $$| $$$$$$$$ /$$__  $$    *" << endl;
    cout << "*       | $$| $$  \\__/| $$| $$  | $$| $$__  $$| $$  | $$    *" << endl;
    cout << "*       | $$| $$      | $$| $$  | $$| $$  | $$| $$  | $$    *" << endl;
    cout << "*       | $$| $$      | $$| $$$$$$$/| $$  | $$|  $$$$$$$    *" << endl;
    cout << "*       |__/|__/      |__/| $$____/ |__/  |__/ \\_______/    *" << endl;
    cout << "*                         | $$                              *" << endl;
    cout << "*                         | $$                              *" << endl;
    cout << "*                         |__/                              *" << endl;
    cout << "*                                                           *" << endl;
    cout << "*     Your Trusted Source for Genuine Hotel Reviews!        *" << endl;
    cout << "*************************************************************" << endl;
    cout << "\033[0m";

    // Main Menu
    while (true) {
        // Title design
        cout << "\n";
        cout << "\033[1;36m";  // Sets the text color to bright cyan
        cout << "******************************" << endl;
        cout << "*         MAIN MENU          *" << endl;
        cout << "*    (Linked List Vers.)     *" << endl;
        cout << "******************************" << endl;
        cout << "\033[0m";
        cout << "\n";

        cout << "What do you want to do?" << endl;
        cout << "Choose your activities:" << endl;
        cout << "1. Data Refresh" << endl;
        cout << "2. Review Analysis (Linear Algorithm)" << endl;
        cout << "3. Review Analysis (Ternary Algorithm)" << endl;
        cout << "4. Show Summary" << endl;
        cout << "5. Show All Positive Word" << endl;
        cout << "6. Show All Negative Word" << endl;
        cout << "0. Exit System" << endl;
        cout << "Enter number: ";
        cin >> program;


        switch (program) {
        case 1:     // Refresh Data
            refreshData(RevRat_Head, RevRat_Tail, POS_Head, POS_Tail, NEG_Head, NEG_Tail, CSV_lines, POS_WORDS, NEG_WORDS);
            break;
        case 2:     // Review Analysis (Linear Algorithm)
            countSentimentWord(RevRat_Head, POS_Head, NEG_Head, CSV_lines);  
            break;
        case 3:     // Review Analysis (Ternary Algorithm)
            countSentimentWord_Ternary(RevRat_Head, POS_Head, NEG_Head, CSV_lines);
            break;
        case 4:     // Show Summary
            summary(RevRat_Head, POS_Head, NEG_Head, CSV_lines);
            break;
        case 5:     // Show All Positive Word
            fileReader.showPosWord(POS_Head);
            cout << endl;
            break;
        case 6:     // Show All Negative Word
            fileReader.showNegWord(NEG_Head);
            cout << endl;
            break;
        case 0:     // End the system
            return 0;
        default:    // Invalid Input
            cout << "Invalid option!" << endl;
            break;
        }
    }

    return 0;
}