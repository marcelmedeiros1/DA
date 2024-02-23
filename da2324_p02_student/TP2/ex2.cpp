#include <iostream>
#include <vector>
using namespace std;
// By: Gonçalo Leão

bool subsetSum(unsigned int A[], unsigned int n, unsigned int T, unsigned int subset[], unsigned int &subsetSize) {
    int tot = 1<<n;
    for(int s = 0; s < tot; s++){
        unsigned int subaux[6];
        int sum=0;
        subsetSize = 0;
        for(int i=0; i<n; i++){
            int f = 1<<i;
            if((s & f) != 0){
                subset[subsetSize] = A[i];
                subsetSize++;
            }
        }
        for(int j=0; j<subsetSize; j++){
            sum += subset[j];
        }
        if(sum==T) { return true;}
    }
    return false;
} // Time Complexity: O(2^n), Space Complexity: O(n)

/// TESTS ///
#include <gtest/gtest.h>

unsigned int sum(unsigned int A[], unsigned int n) {
    unsigned int sum = 0;
    for(unsigned int i = 0; i < n; i++) {
        sum += A[i];
    }
    return sum;
}

// Checks if A is a subset of B
bool isSubset(unsigned int A[], unsigned int nA, unsigned int B[], unsigned int nB) {
    for(unsigned int i = 0; i < nA; i++) {
        bool foundNum = false;
        for(unsigned int j = 0; j < nB; j++) {
            if(A[i] == B[j]) {
                foundNum = true;
                break;
            }
        }
        if(!foundNum) return false;
    }
    return true;
}

TEST(TP2_Ex2, testSubsetSum) {
    unsigned int A[] = {3, 34, 4, 12, 5, 2};
    unsigned int subset[6];
    unsigned int subsetSize;

    unsigned int T = 9;
    EXPECT_EQ(subsetSum(A,6,T,subset,subsetSize), true);
    EXPECT_EQ(sum(subset, subsetSize), T);
    EXPECT_EQ(isSubset(subset, subsetSize, A,6), true);

    T = 20;
    EXPECT_EQ(subsetSum(A,6,T,subset,subsetSize), true);
    EXPECT_EQ(sum(subset, subsetSize), T);
    EXPECT_EQ(isSubset(subset, subsetSize, A,6), true);

    T = 30;
    EXPECT_EQ(subsetSum(A,6,T,subset,subsetSize), false);
}