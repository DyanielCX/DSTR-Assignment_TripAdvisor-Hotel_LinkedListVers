#ifndef READINPUT_HPP
#define READINPUT_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "DataStruc.hpp"

using namespace std;



class ReadFile {
public:
    // Read review & rating csv file function
    inline void readCSV(ReviewAndRating*& head, ReviewAndRating*& tail,const int lineNum) {

        DataIO DataIO;
        ifstream file_read("tripadvisor_hotel_reviews.csv");

        if (file_read.is_open()) {
            for (int i = 0; i < lineNum; i++) {
                string empty_1, review, empty_2, rating;

                getline(file_read, empty_1, '"');
                getline(file_read, review, '"');
                getline(file_read, empty_2, ',');
                getline(file_read, rating, '\n');

                // Insert the review and rating into the linked list
                DataIO.Insert_RevRat(head, tail, review, rating);
            }

            file_read.close();
        }
        else {
            cout << "ERROR: Unable to open tripadvisor_hotel_reviews.csv" << endl;
        }
    }

    // Read positive word text file function
    inline void readPositiveWords(PowWord*& head, PowWord*& tail, const int lineNum) {
        
        DataIO DataIO;
        ifstream file_read("positive-words.txt");

        if (file_read.is_open()) {
            for (int i = 0; i < lineNum; i++) {
                string word;
                file_read >> word;

                // Insert the positive word into the linked list
                DataIO.Insert_PosWord(head, tail, word);
            }
            file_read.close();
        }
        else {
            cout << "ERROR: Unable to open positive-words.txt" << endl;
        }
    }

    // Read negative word text file function
    inline void readNegativeWords(NegWord*& head, NegWord*& tail, const int lineNum) {

        DataIO DataIO;
        ifstream file_read("negative-words.txt");

        if (file_read.is_open()) {
            for (int i = 0; i < lineNum; i++) {
                string word;
                file_read >> word;

                // Insert the negative word into the linked list
                DataIO.Insert_NegWord(head, tail, word);
            }
            file_read.close();
        }
        else {
            cout << "ERROR: Unable to open negative-words.txt" << endl;
        }
    }

    // Display all positive words
    inline void showPosWord(PowWord* head) {
        PowWord* current = head;
        while (current != nullptr) {
            cout << current->word << endl;
            current = current->next;
        }
    }

    // Display all negative words
    inline void showNegWord(NegWord* head) {
        NegWord* current = head;
        while (current != nullptr) {
            cout << current->word << endl;
            current = current->next;
        }
    }
};

#endif 
