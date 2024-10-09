#ifndef TERNARY_FUNCTION_HPP
#define TERNARY_FUNCTION_HPP

#include <iostream>
using namespace std;


class Ternary_fucn {
public:
    // Find index function
    ReviewAndRating* ternarySearchReview(ReviewAndRating* head, int reviewNum, int totalCount) {
        if (reviewNum < 1 || reviewNum > totalCount) return nullptr;

        int mid1_Index = totalCount / 3;
        int mid2_Index = 2 * (totalCount / 3);

        ReviewAndRating* mid1_Node = head;
        ReviewAndRating* mid2_Node = head;

        // Move mid1_Node to the mid1 position
        for (int i = 1; i < mid1_Index && mid1_Node != nullptr; i++) {
            mid1_Node = mid1_Node->next;
        }

        // Move mid2_Node to the mid2 position
        for (int i = 1; i < mid2_Index && mid2_Node != nullptr; i++) {
            mid2_Node = mid2_Node->next;
        }
        
        // Check the user input is the mid or not
        if (reviewNum == mid1_Index) {
            return mid1_Node;
        }
        if (reviewNum == mid2_Index) {
            return mid2_Node;
        }

        // Check the input from other three segment
        if (reviewNum < mid1_Index) {
            // Search the first segment
            return ternarySearchReview(head, reviewNum, mid1_Index);
        }
        else if (reviewNum > mid2_Index) {
            // Search the third segment
            return ternarySearchReview(mid2_Node->next, reviewNum - mid2_Index, totalCount - mid2_Index);
        }
        else {
            // Search the middle segment
            return ternarySearchReview(mid1_Node->next, reviewNum - mid1_Index, mid2_Index - mid1_Index);
        }
    }

};

#endif 