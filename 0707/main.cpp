/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 08 Jul 2020 08:59:33 PM CST
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <mytest.h>
#include <cstring>

using namespace std;
int add(int a, int b) {
        return a + b;

}

TEST(test, add) {
        EXPECT_EQ(add(3, 4), 7);
        EXPECT_NE(add(3, 4), 8);
        EXPECT_GT(add(3, 4), 7);
        EXPECT_LT(add(3, 4), 8);
        EXPECT_GE(add(3, 4), 7);
        EXPECT_LE(add(3, 4), 7);

}

TEST(test, add2) {
        EXPECT_EQ(add(3, 4), 7);
        EXPECT_NE(add(3, 4), 8);
        EXPECT_GT(add(3, 4), 6);
        EXPECT_LT(add(3, 4), 8);
        EXPECT_GE(add(3, 4), 7);
        EXPECT_LE(add(3, 4), 7);

}

int main() {
    return RUN_ALL_TESTS();
}

