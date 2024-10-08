#ifndef SUMMARY_HPP
#define SUMMARY_HPP

#include <sstream>
#include <fstream>
#include <algorithm>
#include <limits.h>
#include <string>
#include <chrono>
#include <iostream>
#include "ReadInput.hpp"
using namespace std;
using namespace chrono;

// Define the Word Frequency Node structure
struct WordFreqNode {
    string word;
    int frequency;
    WordFreqNode* next;

    WordFreqNode(const string& Word, int freq = 0) {
        word = Word;
        frequency = freq;
        next = nullptr;
    }
};

// Function prototypes
inline void displayWordFreq(WordFreqNode* head, const string& wordType);
inline void CheckWordOcc(string curReview, PowWord* posHead, NegWord* negHead, int& totalPosCount, int& totalNegCount);
inline void findMinMaxUsedWords(PowWord* posHead, NegWord* negHead, string*& minUsedWords, string*& maxUsedWords, int& minFreq, int& maxFreq, int& minWordCount, int& maxWordCount);
inline void displayWordUsage(const string* wordArray, int wordCount, int freq, const string& usageType);

// Main summary function
inline void summary(ReviewAndRating* reviewHead, PowWord* posHead, NegWord* negHead, const int lineNum) {
    cout << "\nProcessing the reviews... This might take some time. Please wait." << endl;
    auto start = high_resolution_clock::now();  // Start the timer

    int totalPosCount = 0;
    int totalNegCount = 0;

    // Traverse through the ReviewAndRating linked list
    ReviewAndRating* currentReview = reviewHead;
    while (currentReview != nullptr) {
        string curReview = currentReview->review;

        // Convert review to lowercase for case-insensitive matching
        transform(curReview.begin(), curReview.end(), curReview.begin(), ::tolower);

        // Check occurrences of positive and negative words
        CheckWordOcc(curReview, posHead, negHead, totalPosCount, totalNegCount);

        currentReview = currentReview->next;  // Move to the next review
    }

    // Title design
    cout << "\n \n";
    cout << "\033[0;34m"; // Set the text color to bright blue
    cout << "---------------------------------------" << endl;
    cout << "            Review Summary             " << endl;
    cout << "---------------------------------------" << endl;
    cout << "\033[0m";
    cout << "\n";

    // Display total counts of positive and negative words
    cout << "Total Reviews = " << lineNum << endl;
    cout << "Total Counts of positive words = " << totalPosCount << endl;
    cout << "Total Counts of negative words = " << totalNegCount << endl;

    // Display word frequencies
    cout << "\nFrequency of Positive Words:\n";
    PowWord* posCurrent = posHead;
    while (posCurrent != nullptr) {
        if (posCurrent->frequency > 0) {
            cout << posCurrent->word << " = " << posCurrent->frequency << " times\n";
        }
        posCurrent = posCurrent->next;
    }

    cout << "\nFrequency of Negative Words:\n";
    NegWord* negCurrent = negHead;
    while (negCurrent != nullptr) {
        if (negCurrent->frequency > 0) {
            cout << negCurrent->word << " = " << negCurrent->frequency << " times\n";
        }
        negCurrent = negCurrent->next;
    }

    // Find the minimum and maximum used words
    int minFreq = INT_MAX;
    int maxFreq = 0;
    int minWordCount = 0;
    int maxWordCount = 0;
    string* minUsedWords = nullptr;
    string* maxUsedWords = nullptr;

    findMinMaxUsedWords(posHead, negHead, minUsedWords, maxUsedWords, minFreq, maxFreq, minWordCount, maxWordCount);

    // Display max & min used words
    displayWordUsage(maxUsedWords, maxWordCount, maxFreq, "Maximum");
    displayWordUsage(minUsedWords, minWordCount, minFreq, "Minimum");

    // Clean up dynamically allocated memory for minUsedWords and maxUsedWords
    delete[] minUsedWords;
    delete[] maxUsedWords;

    auto end = high_resolution_clock::now();  // End the timer
    auto duration = duration_cast<seconds>(end - start);

    int minutes = duration.count() / 60;
    int seconds = duration.count() % 60;

    cout << "\nTime taken: " << minutes << " minutes " << seconds << " seconds" << endl;
}

// Check word occurrences function
inline void CheckWordOcc(string curReview, PowWord* posHead, NegWord* negHead, int& totalPosCount, int& totalNegCount) {
    // Traverse positive words
    PowWord* currentPos = posHead;
    while (currentPos != nullptr) {
        if (curReview.find(currentPos->word) != string::npos) {
            currentPos->frequency++;
            totalPosCount++;
        }
        currentPos = currentPos->next;
    }

    // Traverse negative words
    NegWord* currentNeg = negHead;
    while (currentNeg != nullptr) {
        if (curReview.find(currentNeg->word) != string::npos) {
            currentNeg->frequency++;
            totalNegCount++;
        }
        currentNeg = currentNeg->next;
    }
}

// Display word usage function
inline void displayWordUsage(const string* wordArray, int wordCount, int freq, const string& usageType) {
    cout << "\n" << usageType << " used words in the reviews: ";
    for (int i = 0; i < wordCount; i++) {
        cout << wordArray[i];
        if (i < wordCount - 1) {
            cout << ", ";
        }
    }
    cout << " (" << freq << " times)" << endl;
}

// Find min & max used words function
inline void findMinMaxUsedWords(PowWord* posHead, NegWord* negHead, string*& minUsedWords, string*& maxUsedWords, int& minFreq, int& maxFreq, int& minWordCount, int& maxWordCount) {
    minFreq = INT_MAX;
    maxFreq = 0;

    // Traverse positive words
    PowWord* currentPos = posHead;
    while (currentPos != nullptr) {
        if (currentPos->frequency > 0) {
            if (currentPos->frequency < minFreq) {
                minFreq = currentPos->frequency;
                minWordCount = 1;
            }
            else if (currentPos->frequency == minFreq) {
                minWordCount++;
            }

            if (currentPos->frequency > maxFreq) {
                maxFreq = currentPos->frequency;
                maxWordCount = 1;
            }
            else if (currentPos->frequency == maxFreq) {
                maxWordCount++;
            }
        }
        currentPos = currentPos->next;
    }

    // Traverse negative words
    NegWord* currentNeg = negHead;
    while (currentNeg != nullptr) {
        if (currentNeg->frequency > 0) {
            if (currentNeg->frequency < minFreq) {
                minFreq = currentNeg->frequency;
                minWordCount = 1;
            }
            else if (currentNeg->frequency == minFreq) {
                minWordCount++;
            }

            if (currentNeg->frequency > maxFreq) {
                maxFreq = currentNeg->frequency;
                maxWordCount = 1;
            }
            else if (currentNeg->frequency == maxFreq) {
                maxWordCount++;
            }
        }
        currentNeg = currentNeg->next;
    }

    // Allocate arrays for min and max used words
    minUsedWords = new string[minWordCount];
    maxUsedWords = new string[maxWordCount];

    int minIndex = 0;
    int maxIndex = 0;

    // Traverse again to store the words
    currentPos = posHead;
    while (currentPos != nullptr) {
        if (currentPos->frequency == minFreq) {
            minUsedWords[minIndex++] = currentPos->word;
        }
        if (currentPos->frequency == maxFreq) {
            maxUsedWords[maxIndex++] = currentPos->word;
        }
        currentPos = currentPos->next;
    }

    currentNeg = negHead;
    while (currentNeg != nullptr) {
        if (currentNeg->frequency == minFreq) {
            minUsedWords[minIndex++] = currentNeg->word;
        }
        if (currentNeg->frequency == maxFreq) {
            maxUsedWords[maxIndex++] = currentNeg->word;
        }
        currentNeg = currentNeg->next;
    }
}

#endif
