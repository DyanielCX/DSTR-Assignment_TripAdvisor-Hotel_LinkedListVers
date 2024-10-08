#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>
#include <cctype>
#include <climits>

using namespace std;
using namespace chrono;

void summary();

int main() {
    int program;

    cout << "What do you want to do?" << endl;
    cout << "Choose your activities:" << endl;
    cout << "1. Read File" << endl;
    cout << "2. Read Review" << endl;
    cout << "3. Summary" << endl;
    cout << "Enter number: ";
    cin >> program;

    switch (program) {
    case 1:
        //readfile();
        break;
    case 2:
        //countSentimentWord();
        break;
    case 3:
        summary();
        break;
    default:
        cout << "Invalid option!" << endl;
        break;
    }
    return 0;
}

struct Node {
    string word;
    int frequency;
    Node* next;
};

// Function to insert a word into the linked list (in sorted order)
void insertWordSorted(Node*& head, const string& word) {
    Node* newNode = new Node{ word, 0, nullptr };

    // If the list is empty or the new word should be the first element
    if (!head || word < head->word) {
        newNode->next = head;
        head = newNode;
    }
    else {
        Node* current = head;
        while (current->next && current->next->word < word) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Function to find a word in the linked list
Node* findWord(Node* head, const string& word) {
    Node* temp = head;
    while (temp) {
        if (temp->word == word) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Function to delete the linked list and free memory
void deleteList(Node*& head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void summary() {
    cout << "Processing the reviews... This might take some time. Please wait." << endl;
    auto start = high_resolution_clock::now();  // Start the timer

    // Linked lists for positive and negative words
    Node* posWords = nullptr;
    Node* negWords = nullptr;

    // Load positive and negative words from files
    ifstream posFile("positive-words.txt");
    ifstream negFile("negative-words.txt");

    string word;
    if (posFile.is_open()) {
        while (posFile >> word) {
            insertWordSorted(posWords, word);
        }
        posFile.close();
    }

    if (negFile.is_open()) {
        while (negFile >> word) {
            insertWordSorted(negWords, word);
        }
        negFile.close();
    }

    // Load reviews from CSV file
    ifstream csv_read("tripadvisor_hotel_reviews.csv");

    if (csv_read.is_open()) {
        string review;
        int totalPosCount = 0;
        int totalNegCount = 0;

        // Process each review
        while (getline(csv_read, review)) {
            string curReview = review;

            // Convert review to lowercase for case-insensitive matching
            transform(curReview.begin(), curReview.end(), curReview.begin(), ::tolower);

            // Check for occurrences of positive words
            Node* temp = posWords;
            while (temp) {
                if (curReview.find(temp->word) != string::npos) {
                    temp->frequency++;
                    totalPosCount++;
                }
                temp = temp->next;
            }

            // Check for occurrences of negative words
            temp = negWords;
            while (temp) {
                if (curReview.find(temp->word) != string::npos) {
                    temp->frequency++;
                    totalNegCount++;
                }
                temp = temp->next;
            }
        }

        // Display total counts of positive and negative words
        cout << "\nTotal Counts of positive words = " << totalPosCount << endl;
        cout << "Total Counts of negative words = " << totalNegCount << endl;

        // Display frequency of each positive word used
        cout << "\nFrequency of each positive word in reviews:\n";
        Node* temp = posWords;
        while (temp) {
            if (temp->frequency > 0) {
                cout << temp->word << " = " << temp->frequency << " times" << endl;
            }
            temp = temp->next;
        }

        // Display frequency of each negative word used
        cout << "\nFrequency of each negative word in reviews:\n";
        temp = negWords;
        while (temp) {
            if (temp->frequency > 0) {
                cout << temp->word << " = " << temp->frequency << " times" << endl;
            }
            temp = temp->next;
        }

        // Find the minimum and maximum used words
        int minFreq = INT_MAX;
        int maxFreq = 0;

        // Find min/max for positive words
        temp = posWords;
        while (temp) {
            if (temp->frequency > 0 && temp->frequency < minFreq) {
                minFreq = temp->frequency;
            }
            if (temp->frequency > maxFreq) {
                maxFreq = temp->frequency;
            }
            temp = temp->next;
        }

        // Find min/max for negative words
        temp = negWords;
        while (temp) {
            if (temp->frequency > 0 && temp->frequency < minFreq) {
                minFreq = temp->frequency;
            }
            if (temp->frequency > maxFreq) {
                maxFreq = temp->frequency;
            }
            temp = temp->next;
        }

        // Display max used words
        cout << "\nMaximum used words in the reviews: ";
        temp = posWords;
        while (temp) {
            if (temp->frequency == maxFreq) {
                cout << temp->word << ", ";
            }
            temp = temp->next;
        }
        temp = negWords;
        while (temp) {
            if (temp->frequency == maxFreq) {
                cout << temp->word << ", ";
            }
            temp = temp->next;
        }
        cout << " (" << maxFreq << " times)" << endl;

        // Display min used words
        cout << "\nMinimum used words in the reviews: ";
        temp = posWords;
        while (temp) {
            if (temp->frequency == minFreq) {
                cout << temp->word << ", ";
            }
            temp = temp->next;
        }
        temp = negWords;
        while (temp) {
            if (temp->frequency == minFreq) {
                cout << temp->word << ", ";
            }
            temp = temp->next;
        }
        cout << " (" << minFreq << " times)" << endl;

        // Clean up linked lists
        deleteList(posWords);
        deleteList(negWords);
    }
    else {
        cout << "ERROR: tripadvisor_hotel_reviews.csv open fail" << endl;
    }

    auto end = high_resolution_clock::now();  // End the timer
    auto duration = duration_cast<seconds>(end - start);

    int minutes = duration.count() / 60;
    int seconds = duration.count() % 60;

    cout << "\nTime taken: " << minutes << " minutes " << seconds << " seconds" << endl;
}





