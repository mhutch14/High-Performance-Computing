//  Copyright (C) 2017 hutchimw@miamiOH.edu

/* 
 * File:   main.cpp
 * Author: Mark Hutchinson
 *
 * Created on September 22, 2017, 3:17 PM
 */

#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
int numIterator;

bool test(int a, int b) {
    return a < b;
}

void functionTest(std::vector<int> vec) {
    std::sort(vec.begin(), vec.end(), test);
}

void lambdaTest(std::vector<int> vec) {
    std::sort(vec.begin(), vec.end(), [](int a, int b) { return a < b; });
}

int main(int argc, char** argv) {
    std::string cmd = "lambda";
    numIterator = (argc > 2 ? std::stoi(argv[2]) : 30000000);
    for (int i = 0; i < numIterator; i++) {
        std::vector<int> vec = {3, 6, 8, 5, 4, 1, 2, 3, 0, 15, 11, 15};
        if ((argc > 1) && (argv[1] == cmd)) {
            lambdaTest(vec);
        } else {
            functionTest(vec);
        }
    }
}
