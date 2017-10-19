// Copyright (C) 2017
#ifndef N_GRAM_GENERATOR_CPP
#define N_GRAM_GENERATOR_CPP

//---------------------------------------------------------------------------
//
// CSE Department, Miami University, Oxford, OHIO.
// All rights reserved.
//
// Miami University makes no representations or warranties about the
// suitability of the software, either express or implied, including
// but not limited to the implied warranties of merchantability,
// fitness for a particular purpose, or non-infringement.  Miami
// University shall not be liable for any damages suffered by licensee
// as a result of using, result of using, modifying or distributing
// this software or its derivatives.
//
// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.
//
//---------------------------------------------------------------------------
#include "NGramGenerator.h"
#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>

using namespace std;
vector<string> vec, nG;

std::multimap<std::string, int> wordMap;
// Implement various methods in your NGramGenerator class in this
// source file.
void findNGram(int len, int k);

NGramGenerator::NGramGenerator(const size_t minGramLen,
        const size_t maxGramLen) {
    this->minGramLen = minGramLen;
    this->maxGramLen = maxGramLen;
}

void NGramGenerator::extractFrom(std::istream& is) {
    is >> word;
    int i = 0;
    while (!is.eof()) {
        // make sure to make lower case
        word = checkAnumeric(word);
        vec.push_back(word);
        is >> word;
        i++;
    }
    int s = vec.size();
    int z;
    for (int j = 0; j < s; j++) {
        for (int k = 1; k <= s; k++) {
            if ((k + j) <= s) {
                z++;
                if (k >= this->minGramLen) {
                    findNGram(k, j, s);
                }
            }
        }
    }
}

void NGramGenerator::printTopNGrams(size_t topK, std::ostream& os) {
    while (!nG.empty()) {
        int count = 0;
        int i;
        std::string s = nG.back();
        count++;
        nG.pop_back();
        for (i = 0; i < nG.size(); i++) {
            if (nG.at(i) == s) {
                nG.at(i) = "";
                count++;
            }
        }
        cout << s << " | " << count << "\n";
    }
}

// j is the position in the vector
int NGramGenerator::findNGram(int len, int j, int s) {
    std::string comp, word;
    for (int i = j; (i - j) < len; i++) {
        comp = vec.at(i);
        word += comp;
        if (i > 1 && comp < vec.at(i)) {
            comp = vec.at(++i);
            word += comp;
        }
    }
    nG.push_back(word);
    return 0;
}

std::string NGramGenerator::checkAnumeric(std::string str) {
    for (string::iterator i = str.begin(); i != str.end(); i++) {
        if (!isalpha(str.at(i - str.begin()))) {
            str.erase(i);
            i--;
        }
    }
    return str;
}
#endif
