#ifndef REVANALYSISCALC_HPP
#define REVANALYSISCALC_HPP

#include <sstream>
#include <algorithm>
#include <limits.h>
#include <string>
#include "DataStruc.hpp".  // Use PowWord and NegWord structures
using namespace std;

class AnalysisCalc {
public:
    // Count occurrences of positive/negative words in a review using linked lists
    void countOccurrences(const string& review, PowWord* posWordHead, NegWord* negWordHead, PowWord*& foundPosWords, NegWord*& foundNegWords, int& posCount, int& negCount) {
        stringstream ss(review);
        string word;

        while (ss >> word) {
            PowWord* posWordTrav = posWordHead;
            while (posWordTrav != nullptr) {
                if (word == posWordTrav->word) {
                    PowWord* newNode = new PowWord(word);
                    if (foundPosWords == nullptr) {
                        foundPosWords = newNode;
                    }
                    else {
                        PowWord* temp = foundPosWords;
                        while (temp->next != nullptr) temp = temp->next;
                        temp->next = newNode;
                        newNode->prev = temp;
                    }
                    posCount++;
                    break;
                }
                posWordTrav = posWordTrav->next;
            }

            NegWord* negWordTrav = negWordHead;
            while (negWordTrav != nullptr) {
                if (word == negWordTrav->word) {
                    NegWord* newNode = new NegWord(word);
                    if (foundNegWords == nullptr) {
                        foundNegWords = newNode;
                    }
                    else {
                        NegWord* temp = foundNegWords;
                        while (temp->next != nullptr) temp = temp->next;
                        temp->next = newNode;
                        newNode->prev = temp;
                    }
                    negCount++;
                    break;
                }
                negWordTrav = negWordTrav->next;
            }
        }
    }

    // Calculate sentiment score
    double calculateSentimentScore(int posCount, int negCount) {
        int N = posCount + negCount;
        if (N == 0) return 3;  // Neutral if no positive/negative words found

        int rawScore = posCount - negCount;
        int minRawScore = -N;
        int maxRawScore = N;
        double normalizedScore = (rawScore - minRawScore) / (double)(maxRawScore - minRawScore);
        return 1 + 4 * normalizedScore;
    }

    // Clean up dynamically allocated linked list of found words
    void cleanupWordList(PowWord*& head) {
        while (head != nullptr) {
            PowWord* temp = head;
            head = head->next;
            delete temp;
        }
        head = nullptr;
    }

    void cleanupWordList(NegWord*& head) {
        while (head != nullptr) {
            NegWord* temp = head;
            head = head->next;
            delete temp;
        }
        head = nullptr;
    }
};

#endif
