#ifndef REVANALYSISCALC_HPP
#define REVANALYSISCALC_HPP

#include <sstream>
#include <algorithm>
#include <limits.h>
#include <string>
using namespace std;

class AnalysisCalc {
public:
    // Function to count and collect occurrences of positive/negative words in a review
    inline void countOccurrences(const string& review, string* wordList, int wordCount, string* foundWords, int& count) {
        stringstream ss(review);
        string word;
        while (ss >> word) {
            for (int i = 0; i < wordCount; i++) {
                if (word == wordList[i]) {
                    foundWords[count] = word;  // Store matched word
                    count++;
                }
            }
        }
    }

    // Function to calculate the sentiment score
    inline double calculateSentimentScore(int posCount, int negCount) {
        int N = posCount + negCount;
        if (N == 0) return 3;  // Neutral if no positive/negative words found

        int rawScore = posCount - negCount;
        int minRawScore = -N;
        int maxRawScore = N;
        double normalizedScore = (rawScore - minRawScore) / (double)(maxRawScore - minRawScore);
        return 1 + 4 * normalizedScore;
    }
};

#endif 