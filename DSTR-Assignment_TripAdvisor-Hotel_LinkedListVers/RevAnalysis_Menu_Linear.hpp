#ifndef REVANALYSIS_MENU_HPP
#define REVANALYSIS_MENU_HPP

#include <iostream>
#include "RevAnalysisCalc.hpp"
#include "DataStruc.hpp"
using namespace std;

void display_POS_NEG(PowWord* foundPosWords, NegWord* foundNegWords, int posCount, int negCount);
string Define_AnlysOutput(double sentimentScore, string curRating);

inline void countSentimentWord(ReviewAndRating* RevRat_Head, PowWord* PosWord_Head, NegWord* NegWord_Head, const int lineNum) {
    AnalysisCalc calculator;

    int reviewNum = 0;
    ReviewAndRating* reviewTrav = RevRat_Head;

    do {
        cout << "\n \n \n";
        cout << "\033[0;34m"; // Set the text color to bright blue
        cout << "---------------------------------------" << endl;
        cout << "            Review Analysis            " << endl;
        cout << "           (Linear Algorithm)          " << endl;
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

            // Traverse to the selected review
            ReviewAndRating* reviewTrav = RevRat_Head;
            for (int i = 1; i < reviewNum && reviewTrav != nullptr; i++) {
                reviewTrav = reviewTrav->next;
            }

            if (reviewTrav == nullptr) {
                cout << "Review not found!" << endl;
                return;
            }

            string curReview = reviewTrav->review;
            string curRating = reviewTrav->rating;

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
            cout << "\nAnalysis output: \n" << AnlysOutput << endl;

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

        cout << "\nTime taken: " << milliseconds << " milliseconds " << endl;\

    } while (reviewNum != 0);
}

// Display posWord negWord function
inline void display_POS_NEG(PowWord* foundPosWords, NegWord* foundNegWords, int posCount, int negCount) {
    cout << "\nPositive Words = " << posCount << ":\n";
    PowWord* posWord = foundPosWords;
    while (posWord != nullptr) {
        cout << "- " << posWord->word << endl;
        posWord = posWord->next;
    }

    cout << "\nNegative Words = " << negCount << ":\n";
    NegWord* negWord = foundNegWords;
    while (negWord != nullptr) {
        cout << "- " << negWord->word << endl;
        negWord = negWord->next;
    }
}

// Define analysis output function
inline string Define_AnlysOutput(double sentimentScore, string curRating) {
    string AnlysOutput;
    try {
        double Rating = stod(curRating);

        if (sentimentScore > Rating) {
            AnlysOutput = "The analysis indicates a more positive sentiment than the user’s personal rating.";
        }
        else if (sentimentScore == Rating) {
            AnlysOutput = "The user’s rating aligns with the sentiment score generated by the analysis.";
        }
        else {
            AnlysOutput = "The analysis reflects a more negative sentiment compared to the user's higher rating.";
        }
    }
    catch (const std::invalid_argument& e) {
        AnlysOutput = "Invalid rating format. Cannot compare with sentiment score.";
    }

    return AnlysOutput;
}

#endif
