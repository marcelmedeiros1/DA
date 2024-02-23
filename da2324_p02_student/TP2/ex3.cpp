#include <iostream>
using namespace std;
// By: Gonçalo Leão

unsigned int integerKnapsack(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    int tot = 1<<n;
    int max=0;
    bool bestsol[n];
    for(int i=0; i<tot; i++){
        bool sol[n];
        for(int k=0; k<n; k++) sol[k]=false;
        unsigned int max_val = 0;
        unsigned int cur_w = 0;
        for(int j=0; j<n; j++){
            int f = 1<<j;
            if((i & f) != 0){
                sol[j] = true;
                max_val += values[j];
                cur_w += weights[j];
                if(cur_w > maxWeight) break;
            }
        }
        if(max_val > max && cur_w <= maxWeight){
            max = max_val;
            for(int k=0; k<n; k++){
                bestsol[k] = sol[k];
            }
        }
    }
    for(int i=0; i<n;i++){
        usedItems[i] = bestsol[i];
    }
    return max;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex3, testKnapsack_4items) {
    const unsigned int n = 4;
    {
        unsigned int values[n] = {10, 7, 11, 15};
        unsigned int weights[n] = {1, 2, 1, 3};
        bool usedItems[n];

        EXPECT_EQ(integerKnapsack(values, weights, n, 5, usedItems), 36);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], false);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
    }

    {
        unsigned int values[n] = {3, 4, 5, 6};
        unsigned int weights[n] = {2, 3, 4, 5};
        bool usedItems[n];

        EXPECT_EQ(integerKnapsack(values, weights, n, 5, usedItems), 7);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], false);
        EXPECT_EQ(usedItems[3], false);
    }
}

TEST(TP2_Ex3, testKnapsack_5items) {
    const unsigned int n = 5;
    {
        unsigned int values[n] = {1, 2, 5, 9, 4};
        unsigned int weights[n] = {2, 3, 3, 4, 6};
        bool usedItems[n];

        EXPECT_EQ(integerKnapsack(values, weights, n, 10, usedItems), 16);
        EXPECT_EQ(usedItems[0], false);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
        EXPECT_EQ(usedItems[4], false);
    }
}