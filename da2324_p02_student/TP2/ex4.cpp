// By: Gonçalo Leão

#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

double fractionalKnapsack(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, double usedItems[]) {
    vector<pair<double, int>> v_w;
    double rem = maxWeight;
    double res = 0.0;
    for(int i=0; i<n; i++){
        usedItems[i] = 0.0;
    }
    for(int i=0; i<n; i++){
        double c = (values[i]/weights[i]);
        v_w.push_back(make_pair(c, i));
    }
    sort(v_w.begin(), v_w.end(), [](pair<double,int> p1, pair<double, int> p2) -> bool {return p1.first > p2.first;});
    for(int i=0; i<n; i++){
        int index = v_w.at(i).second;
        if(weights[index] <= rem){
            rem -= weights[index];
            usedItems[index]=1;
            res += values[index];
        }
        else if(weights[index] > rem){
            double q = rem/weights[index];
            usedItems[index] = q;
            res += values[index]*q;
            break;
        }
    }
    return res;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex4, testFractionalKnapsack_3items) {
    const unsigned int n = 3;
    {
        unsigned int values[n] = {60, 100, 120};
        unsigned int weights[n] = {10, 20, 30};
        double usedItems[n];

        EXPECT_NEAR(fractionalKnapsack(values, weights, n, 50, usedItems), 240.0, 0.00001);
        EXPECT_NEAR(usedItems[0], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[1], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[2], 2.0/3.0, 0.00001);
    }
}

TEST(TP2_Ex4, testFractionalKnapsack_7items) {
    const unsigned int n = 7;
    {
        unsigned int values[n] = {10, 5, 15, 7, 6, 18, 3};
        unsigned int weights[n] = {2, 3, 5, 7, 1, 4, 1};
        double usedItems[n];

        EXPECT_NEAR(fractionalKnapsack(values, weights, n, 15, usedItems), 52.0 + 10.0/3.0, 0.00001);
        EXPECT_NEAR(usedItems[0], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[1], 2.0/3.0, 0.00001);
        EXPECT_NEAR(usedItems[2], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[3], 0.0, 0.00001);
        EXPECT_NEAR(usedItems[4], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[5], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[6], 1.0, 0.00001);
    }
}