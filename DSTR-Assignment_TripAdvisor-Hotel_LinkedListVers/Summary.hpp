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

    WordFreqNode(const string& w, int freq = 0) : word(w), frequency(freq), next(nullptr) {}
};

// Function prototypes
inline void displayWordFreq(WordFreqNode* head, const string& wordType);
inline void CheckWordOcc(string curReview, WordFreqNode* head, int& totalCount);
inline void findMinMaxUsedWords(WordFreqNode* head, string*& minUsedWords, string*& maxUsedWords, int& minFreq, int& maxFreq, int& minWordCount, int& maxWordCount);
inline void displayWordUsage(const string* wordArray, int wordCount, int freq, const string& usageType);


// Main summary function
inline void summary(ReviewAndRating* Review_Data, WordFreqNode* PosWord_Data, WordFreqNode* NegWord_Data, const int lineNum){
    cout << "\nProcessing the reviews... This might take some time. Please wait." << endl;
    auto start = high_resolution_clock::now();  // Start the timer

    // Arrays to store the frequency of each positive and negative word
    WordFreqNode* posWordFreqHead = nullptr;
    WordFreqNode* negWordFreqHead = nullptr;

    int totalPosCount = 0;
    int totalNegCount = 0;

    // Process each review
    for (int i = 0; i < lineNum; i++) {
        string curReview = Review_Data[i].review; // Adjust this line according to your struct

        // Convert review to lowercase for case-insensitive matching
        transform(curReview.begin(), curReview.end(), curReview.begin(), ::tolower);

        // Check for occurrences of positive words & negative word
        CheckWordOcc(curReview, PosWord_Data, totalPosCount);
        CheckWordOcc(curReview, NegWord_Data, totalNegCount);
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

    // Display frequency of each positive word & negative word used
    displayWordFreq(posWordFreqHead, "positive");
    displayWordFreq(negWordFreqHead, "negative");

    // Find the minimum and maximum used words
    int minFreq = INT_MAX;
    int maxFreq = 0;
    int minWordCount = 0;
    int maxWordCount = 0;
    string* minUsedWords = nullptr;  // Use pointers to store min and max words
    string* maxUsedWords = nullptr;

    findMinMaxUsedWords(posWordFreqHead, minUsedWords, maxUsedWords, minFreq, maxFreq, minWordCount, maxWordCount);
    findMinMaxUsedWords(negWordFreqHead, minUsedWords, maxUsedWords, minFreq, maxFreq, minWordCount, maxWordCount);

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
inline void CheckWordOcc(string curReview, WordFreqNode* head, int& totalCount) {
    WordFreqNode* current = head;
    while (current != nullptr) {
        if (curReview.find(current->word) != string::npos) {
            current->frequency++;
            totalCount++;
        }
        current = current->next;
    }
}

// Display word frequency function
inline void displayWordFreq(WordFreqNode* head, const string& wordType) {
    cout << "\nFrequency of each " << wordType << " word in reviews : \n";
    WordFreqNode* current = head;
    while (current != nullptr) {
        if (current->frequency > 0) {
            cout << current->word << " = " << current->frequency << " times" << endl;
        }
        current = current->next;
    }
}

// Find min & max used function
inline void findMinMaxUsedWords(WordFreqNode* head, string*& minUsedWords, string*& maxUsedWords, int& minFreq, int& maxFreq, int& minWordCount, int& maxWordCount) {
    minFreq = INT_MAX;
    maxFreq = 0;

    WordFreqNode* current = head;
    while (current != nullptr) {
        if (current->frequency > 0) {
            if (current->frequency < minFreq) {
                minFreq = current->frequency;
                minWordCount = 1;
            }
            else if (current->frequency == minFreq) {
                minWordCount++;
            }

            if (current->frequency > maxFreq) {
                maxFreq = current->frequency;
                maxWordCount = 1;
            }
            else if (current->frequency == maxFreq) {
                maxWordCount++;
            }
        }
        current = current->next;
    }

    // Allocate arrays for min and max used words
    minUsedWords = new string[minWordCount];
    maxUsedWords = new string[maxWordCount];

    int minIndex = 0;
    int maxIndex = 0;
    current = head;
    while (current != nullptr) {
        if (current->frequency == minFreq) {
            minUsedWords[minIndex++] = current->word;
        }
        if (current->frequency == maxFreq) {
            maxUsedWords[maxIndex++] = current->word;
        }
        current = current->next;
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

#endif
