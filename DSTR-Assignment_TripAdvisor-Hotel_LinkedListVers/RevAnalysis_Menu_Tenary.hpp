#ifndef REVANALYSIS_TERNARY_MENU_HPP
#define REVANALYSIS_TERNARY_MENU_HPP

#include <iostream>
#include "RevAnalysis_Menu_Linear.hpp"
#include "Ternary_Function.hpp"
#include "RevAnalysisCalc.hpp"
#include "DataStruc.hpp"
using namespace std;

inline void countSentimentWord_Ternary(ReviewAndRating* RevRat_Head, PowWord* PosWord_Head, NegWord* NegWord_Head, const int lineNum) {
    AnalysisCalc calculator;
    Ternary_fucn ternarySearch;

    int reviewNum = 0;

    do {
        cout << "\n \n \n";
        cout << "\033[0;34m"; // Set the text color to bright blue
        cout << "---------------------------------------" << endl;
        cout << "            Review Analysis            " << endl;
        cout << "           (Ternary Algorithm)         " << endl;
        cout << "---------------------------------------" << endl;
        cout << "\033[0m";
        cout << "\n";

        cout << "There are total " << lineNum << " reviews \n";
        cout << "Select review from 1 to " << lineNum << " for analysis. Enter 0 back to main" << endl;
        cout << "Enter review number: ";
        cin >> reviewNum;
        cout << "\n";

        auto start = high_resolution_clock::now();    // Start the timer

        if (reviewNum > 0 && reviewNum <= lineNum) {
            // Reset found words for a new analysis
            PowWord* foundPosWords = nullptr;
            NegWord* foundNegWords = nullptr;
            int posCount = 0, negCount = 0;

            // Find the review at reviewNum using ternary search-like traversal
            ReviewAndRating* curRevNode = RevRat_Head;
            curRevNode = ternarySearch.ternarySearchReview(curRevNode, reviewNum, lineNum-1);

            if (curRevNode == nullptr) {
                cout << "Review not found!" << endl;
                continue;
            }

            string curReview = curRevNode->review;
            string curRating = curRevNode->rating;

            cout << "\033[1;33m";
            cout << "\nReview #" << reviewNum << "\n";
            cout << "\033[0m";
            cout << curReview << endl;

            // Count positive and negative word occurrences
            calculator.countOccurrences(curReview, PosWord_Head, NegWord_Head, foundPosWords, foundNegWords, posCount, negCount);

            // Calculate sentiment score
            double sentimentScore = calculator.calculateSentimentScore(posCount, negCount);

            // Display found positive and negative words
            display_POS_NEG(foundPosWords, foundNegWords, posCount, negCount);

            cout << "\nSentiment score (1 - 5) is " << sentimentScore << ", thus the rating should be equal to " << round(sentimentScore) << " (Neutral).\n \n" << endl;

            // Display review analysis conclusion
            string AnlysOutput = Define_AnlysOutput(sentimentScore, curRating);

            cout << "\033[1;33m";
            cout << "#------ Analysis Conclusion ------#" << endl;
            cout << "\033[0m";
            cout << "Sentiment Score(1-5) = " << round(sentimentScore) << endl;
            cout << "Rating given by user = " << curRating << endl;
            cout << "\nAnalysis output: \n \n" << AnlysOutput << endl;

            // Clean up dynamically allocated memory for found words
            calculator.cleanupWordList(foundPosWords);
            calculator.cleanupWordList(foundNegWords);
        }
        else if (reviewNum != 0) {
            cout << "Invalid review number! Please enter a number between 1 and " << lineNum << "." << endl;
        }

        // Display time used for review analysis
        auto end = high_resolution_clock::now();      // End the timer
        auto duration = duration_cast<milliseconds>(end - start);
        int milliseconds = duration.count() % 1000;

        cout << "\nTime taken: " << milliseconds << " milliseconds " << endl;

    } while (reviewNum != 0);
}

#endif
