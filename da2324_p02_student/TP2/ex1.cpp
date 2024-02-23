#include <iostream>
using namespace std;
// By: Gonçalo Leão
// With contributions by Eduardo Almeida

int maxSubsequence(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    int max=A[0];
    i=0; j=0;
    int aux_i, aux_j;
    for(aux_i=0; aux_i<n; aux_i++){
        int cur=A[aux_i];
        for(aux_j=aux_i+1; aux_j<n; aux_j++){
            cur += A[aux_j];
            if(cur > max){
                max = cur;
                i = aux_i;
                j = aux_j;
            }
        }
    }
    return max;
    //O(n²)
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex1, maxSubsequence) {
    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n = 9;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequence(A,n,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}