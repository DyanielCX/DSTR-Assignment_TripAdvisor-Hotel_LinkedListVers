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
#include "DataStruc.hpp"
using namespace std;
using namespace chrono;

// Function prototypes
inline void CheckWordOcc(string curReview, PowWord* posHead, NegWord* negHead, int& totalPosCount, int& totalNegCount);
inline void findMinMaxUsedWords(PowWord* posHead, NegWord* negHead, WordNode*& minUsedWordsHead, WordNode*& maxUsedWordsHead, int& minFreq, int& maxFreq);
inline void displayWordUsage(WordNode* wordList, int freq, const string& usageType);
void addToList(WordNode*& head, const string& word);
void deleteList(WordNode*& head);
void mergeSortIterative(PowWord*& head);
void mergeSortIterative(NegWord*& head);
PowWord* sortedMerge(PowWord* a, PowWord* b);
NegWord* sortedMerge(NegWord* a, NegWord* b);
PowWord* splitList(PowWord* head, int step);
NegWord* splitList(NegWord* head, int step);

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

    // Sort the lists before displaying them
    mergeSortIterative(posHead); // Sort the positive words by frequency in descending order
    mergeSortIterative(negHead); // Sort the negative words by frequency in descending order

    // Display word frequencies
    cout << "\nFrequency of Positive Words:\n";
    PowWord* posCurrent = posHead;
    while (posCurrent != nullptr) {
        // Display words even if they are used 0 times
        cout << posCurrent->word << " = " << posCurrent->frequency << " times\n";
        posCurrent = posCurrent->next;
    }

    cout << "\nFrequency of Negative Words:\n";
    NegWord* negCurrent = negHead;
    while (negCurrent != nullptr) {
        // Display words even if they are used 0 times
        cout << negCurrent->word << " = " << negCurrent->frequency << " times\n";
        negCurrent = negCurrent->next;
    }

    // Find the minimum and maximum used words
    int minFreq = INT_MAX;
    int maxFreq = 0;
    WordNode* minUsedWordsHead = nullptr;
    WordNode* maxUsedWordsHead = nullptr;

    findMinMaxUsedWords(posHead, negHead, minUsedWordsHead, maxUsedWordsHead, minFreq, maxFreq);

    // Display max & min used words
    displayWordUsage(maxUsedWordsHead, maxFreq, "Maximum");
    displayWordUsage(minUsedWordsHead, minFreq, "Minimum");

    // Clean up dynamically allocated memory for minUsedWords and maxUsedWords
    deleteList(minUsedWordsHead);
    deleteList(maxUsedWordsHead);

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

// Display word usage function for linked list
inline void displayWordUsage(WordNode* wordList, int freq, const string& usageType) {
    cout << "\n" << usageType << " used words in the reviews: ";
    WordNode* current = wordList;
    while (current != nullptr) {
        cout << current->word;
        if (current->next != nullptr) {
            cout << ", ";
        }
        current = current->next;
    }
    cout << " (" << freq << " times)" << endl;
}

// Find min & max used words function using linked list
inline void findMinMaxUsedWords(PowWord* posHead, NegWord* negHead, WordNode*& minUsedWordsHead, WordNode*& maxUsedWordsHead, int& minFreq, int& maxFreq) {
    minFreq = INT_MAX;
    maxFreq = 0;

    // Traverse positive words
    PowWord* currentPos = posHead;
    while (currentPos != nullptr) {
        if (currentPos->frequency > 0) {
            if (currentPos->frequency < minFreq) {
                minFreq = currentPos->frequency;
                deleteList(minUsedWordsHead);
                minUsedWordsHead = new WordNode(currentPos->word);
            }
            else if (currentPos->frequency == minFreq) {
                addToList(minUsedWordsHead, currentPos->word);
            }

            if (currentPos->frequency > maxFreq) {
                maxFreq = currentPos->frequency;
                deleteList(maxUsedWordsHead);
                maxUsedWordsHead = new WordNode(currentPos->word);
            }
            else if (currentPos->frequency == maxFreq) {
                addToList(maxUsedWordsHead, currentPos->word);
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
                deleteList(minUsedWordsHead);
                minUsedWordsHead = new WordNode(currentNeg->word);
            }
            else if (currentNeg->frequency == minFreq) {
                addToList(minUsedWordsHead, currentNeg->word);
            }

            if (currentNeg->frequency > maxFreq) {
                maxFreq = currentNeg->frequency;
                deleteList(maxUsedWordsHead);
                maxUsedWordsHead = new WordNode(currentNeg->word);
            }
            else if (currentNeg->frequency == maxFreq) {
                addToList(maxUsedWordsHead, currentNeg->word);
            }
        }
        currentNeg = currentNeg->next;
    }
}

// Add a word to the linked list
void addToList(WordNode*& head, const string& word) {
    WordNode* newNode = new WordNode(word);
    if (head == nullptr) {
        head = newNode;
    }
    else {
        WordNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Delete the linked list
void deleteList(WordNode*& head) {
    while (head != nullptr) {
        WordNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// Iterative merge sort for PowWord
void mergeSortIterative(PowWord*& head) {
    if (!head || !head->next)
        return;

    PowWord* curr;
    PowWord* left;
    PowWord* right;
    PowWord* sorted;

    int length = 0;
    curr = head;
    while (curr) {
        ++length;
        curr = curr->next;
    }

    for (int step = 1; step < length; step *= 2) {
        PowWord* prevTail = nullptr;
        PowWord* newHead = nullptr;
        curr = head;
        while (curr) {
            left = curr;
            right = splitList(left, step);
            curr = splitList(right, step);

            sorted = sortedMerge(left, right);
            if (!newHead)
                newHead = sorted;
            if (prevTail)
                prevTail->next = sorted;

            while (sorted->next)
                sorted = sorted->next;
            prevTail = sorted;
        }
        head = newHead;
    }
}

// Iterative merge sort for NegWord
void mergeSortIterative(NegWord*& head) {
    if (!head || !head->next)
        return;

    NegWord* curr;
    NegWord* left;
    NegWord* right;
    NegWord* sorted;

    int length = 0;
    curr = head;
    while (curr) {
        ++length;
        curr = curr->next;
    }

    for (int step = 1; step < length; step *= 2) {
        NegWord* prevTail = nullptr;
        NegWord* newHead = nullptr;
        curr = head;
        while (curr) {
            left = curr;
            right = splitList(left, step);
            curr = splitList(right, step);

            sorted = sortedMerge(left, right);
            if (!newHead)
                newHead = sorted;
            if (prevTail)
                prevTail->next = sorted;

            while (sorted->next)
                sorted = sorted->next;
            prevTail = sorted;
        }
        head = newHead;
    }
}

// Helper function to split the list into two parts (PowWord)
PowWord* splitList(PowWord* head, int step) {
    PowWord* curr = head;
    for (int i = 1; curr && i < step; ++i)
        curr = curr->next;
    if (!curr)
        return nullptr;

    PowWord* next = curr->next;
    curr->next = nullptr;
    return next;
}

// Helper function to split the list into two parts (NegWord)
NegWord* splitList(NegWord* head, int step) {
    NegWord* curr = head;
    for (int i = 1; curr && i < step; ++i)
        curr = curr->next;
    if (!curr)
        return nullptr;

    NegWord* next = curr->next;
    curr->next = nullptr;
    return next;
}

// Iterative sorted merge for PowWord
PowWord* sortedMerge(PowWord* a, PowWord* b) {
    PowWord dummy;
    PowWord* tail = &dummy;

    dummy.next = nullptr;

    while (a != nullptr && b != nullptr) {
        if (a->frequency >= b->frequency) { // Descending order
            tail->next = a;
            a = a->next;
        }
        else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }

    if (a != nullptr) {
        tail->next = a;
    }
    else {
        tail->next = b;
    }

    return dummy.next;
}

// Iterative sorted merge for NegWord
NegWord* sortedMerge(NegWord* a, NegWord* b) {
    NegWord dummy;
    NegWord* tail = &dummy;

    dummy.next = nullptr;

    while (a != nullptr && b != nullptr) {
        if (a->frequency >= b->frequency) { // Descending order
            tail->next = a;
            a = a->next;
        }
        else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }

    if (a != nullptr) {
        tail->next = a;
    }
    else {
        tail->next = b;
    }

    return dummy.next;
}

#endif // SUMMARY_HPP
