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

inline void displayWordFreq(const string* wordList, const int* wordFreq, const int wordCount, const string& wordType);
inline void CheckWordOcc(string curReview, string* wordList, int* wordFreq, int& totalCount, const int wordCount);
inline void findMinMaxUsedWords(const int* wordFreq, const string* wordList, const int wordCount, string*& minUsedWords, string*& maxUsedWords, int& minFreq, int& maxFreq, int& minWordCount, int& maxWordCount);
inline void displayWordUsage(const string* wordArray, int wordCount, int freq, const string& usageType);


inline void summary(ReviewAndRating Review_Data, string* PosWord_Data, string* NegWord_Data, const int lineNum, const int POS_WORDS, const int NEG_WORDS) {
    cout << "\nProcessing the reviews... This might take some time. Please wait." << endl;
    auto start = high_resolution_clock::now();  // Start the timer

    // Sort the word lists for binary searching
    sort(PosWord_Data, PosWord_Data + POS_WORDS);
    sort(NegWord_Data, NegWord_Data + NEG_WORDS);


    // Arrays to store the frequency of each positive and negative word
    int* posWordFreq = new int[POS_WORDS]();
    int* negWordFreq = new int[NEG_WORDS]();

    int totalPosCount = 0;
    int totalNegCount = 0;

    // Process each review
    for (int i = 0; i < lineNum; i++) {
        string curReview = Review_Data.review_arr[i];

        // Convert review to lowercase for case-insensitive matching
        transform(curReview.begin(), curReview.end(), curReview.begin(), ::tolower);

        // Check for occurrences of positive words & negative word
        CheckWordOcc(curReview, PosWord_Data, posWordFreq, totalPosCount, POS_WORDS);
        CheckWordOcc(curReview, NegWord_Data, negWordFreq, totalNegCount, NEG_WORDS);
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
    displayWordFreq(PosWord_Data, posWordFreq, POS_WORDS, "postive");
    displayWordFreq(NegWord_Data, negWordFreq, NEG_WORDS, "negative");

    // Find the minimum and maximum used words
    int minFreq = INT_MAX;
    int maxFreq = 0;
    int minWordCount = 0;
    int maxWordCount = 0;
    string* minUsedWords = new string[minWordCount];
    string* maxUsedWords = new string[maxWordCount];

    findMinMaxUsedWords(posWordFreq, PosWord_Data, POS_WORDS, minUsedWords, maxUsedWords, minFreq, maxFreq, minWordCount, maxWordCount);
    findMinMaxUsedWords(negWordFreq, NegWord_Data, NEG_WORDS, minUsedWords, maxUsedWords, minFreq, maxFreq, minWordCount, maxWordCount);

    // Display max & min used words
    displayWordUsage(maxUsedWords, maxWordCount, maxFreq, "Maximum");
    displayWordUsage(minUsedWords, minWordCount, minFreq, "Minimum");

    // Clean up dynamically allocated memory
    delete[] posWordFreq;
    delete[] negWordFreq;
    delete[] minUsedWords;
    delete[] maxUsedWords;

    auto end = high_resolution_clock::now();  // End the timer
    auto duration = duration_cast<seconds>(end - start);

    int minutes = duration.count() / 60;
    int seconds = duration.count() % 60;

    cout << "\nTime taken: " << minutes << " minutes " << seconds << " seconds" << endl;
}


// Check word occurences fucntion
inline void CheckWordOcc(string curReview, string* wordList, int* wordFreq, int& totalCount, const int wordCount) {
    for (int j = 0; j < wordCount; j++) {
        if (curReview.find(wordList[j]) != string::npos) {
            wordFreq[j]++;
            totalCount++;
        }
    }
}


// Display word frequency function
inline void displayWordFreq(const string* wordList, const int* wordFreq, const int wordCount, const string& wordType) {
    cout << "\nFrequency of each" << wordType<< "word in reviews : \n";
    for (int i = 0; i < wordCount; i++) {
        if (wordFreq[i] > 0) {
            cout << wordList[i] << " = " << wordFreq[i] << " times" << endl;
        }
    }
}


// Find min & max used function
inline void findMinMaxUsedWords(const int* wordFreq, const string* wordList, const int wordCount, string*& minUsedWords, string*& maxUsedWords, int& minFreq, int& maxFreq, int& minWordCount, int& maxWordCount) {
    minFreq = INT_MAX;
    maxFreq = 0;

    for (int i = 0; i < wordCount; i++) {
        if (wordFreq[i] > 0 && wordFreq[i] < minFreq) {
            minFreq = wordFreq[i];
            minWordCount = 1;
        }
        else if (wordFreq[i] == minFreq) {
            minWordCount++;
        }

        if (wordFreq[i] > maxFreq) {
            maxFreq = wordFreq[i];
            maxWordCount = 1;
        }
        else if (wordFreq[i] == maxFreq) {
            maxWordCount++;
        }
    }

    minUsedWords = new string[minWordCount];
    maxUsedWords = new string[maxWordCount];
    int minIndex = 0;
    int maxIndex = 0;

    for (int i = 0; i < wordCount; i++) {
        if (wordFreq[i] == minFreq) {
            minUsedWords[minIndex++] = wordList[i];
        }
        if (wordFreq[i] == maxFreq) {
            maxUsedWords[maxIndex++] = wordList[i];
        }
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