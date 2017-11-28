/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/*
 * Author: hutchimw
 *
 * Copyright (C) 2017 hutchimw@miamioh.edu
 * Created on November 16, 2017, 1:23 PM
 */
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include "PNG.h"
#include "Assert.h"


int MP = 0;
int PT = 0;
std::vector<std::pair<int, int>> savedPoints;

bool isBlackPix(std::vector<unsigned char> buff, int index) {
    bool blackPix = false;
    if (buff[index] == 0 && buff[index + 1] == 0 && buff[index + 2] == 0) {
        blackPix = true;
    }
    return blackPix;
}

int avgForImage(std::vector<unsigned char> image, int spot) {
    int avg = (image[spot] + image[spot + 1] + image[spot + 2]) / 3;
    return avg;
}

bool checkMatch(int imageAvg, int maskAvg, int PT) {
    if (imageAvg <= maskAvg - PT || imageAvg >= maskAvg + PT) {
        return true;
    }
    return false;
}

int getPixelIndex(int row, int col, int width) {
    int index = 0;
    index = (4 * width) * row + (4 * col);
    return index;
}

int avgBg(std::vector<unsigned char> imageBuff, int index) {
    int result = (imageBuff[index] + imageBuff[index + 1] +
            imageBuff[index + 2]) / 3;
    return result;
}

int avgBack(int k, int z, PNG mask, PNG image,
        int i, int j, std::vector<unsigned char> imgBuff,
        std::vector<unsigned char> maskBuff) {
    int avg = 0;
    int maskIndex = getPixelIndex(k - j, z - i, mask.getWidth());
    int imgIndex = getPixelIndex(k, z, image.getWidth());

    bool isblack = isBlackPix(maskBuff, maskIndex);
    if (isblack == true) {
        avg = avgBg(imgBuff, imgIndex);
    }
    return avg;
}

int findAvgOfList(std::vector<int> avgList) {
    int sum = 0;
    for (unsigned int i = 0; i < avgList.size(); i++) {
        sum += avgList[i];
    }
    int total = sum / avgList.size();
    return total;
}

int findingMatches(int totalAvg, int i, int j, PNG mask, PNG img,
        int PT, std::vector<unsigned char> buff) {
    int match = 0;
    int noMatch = 0;
    for (int a = i; a < mask.getHeight(); a++) {
        for (int c = j; c < mask.getWidth(); c++) {
            int index = getPixelIndex(a, c, img.getWidth());
            int maskIndex = getPixelIndex(a - i, c - j, mask.getWidth());
            int val = avgBg(buff, index);
            if (isBlackPix(buff, maskIndex)) {
                if ((val <= (totalAvg + PT)) && (val >= (totalAvg - PT))) {
                    match++;
                } else {
                    noMatch++;
                }
            }
        }
    }
    return match - noMatch;
}

bool alreadyFound(std::pair<int, int> points) {
    auto result = std::find_if(savedPoints.begin(), savedPoints.end(),
            [points](const std::pair<int, int>& element)->bool {
                return ((element.first == points.first)
                        && (element.second == points.second));
                {
                }
            });
    bool flag = false;
    if (savedPoints.size() > 1 && result != std::end(savedPoints)) {
        flag = true;
    }

    return flag;
}

bool match(int netMatch, PNG mask) {
    int area = mask.getWidth() * mask.getHeight() * MP / 100;
    if (netMatch > area) {
        return true;
    }
    return false;
}

void saveCheck(int i, int j, bool isMatch) {
    std::pair<int, int> test(i, j);
    if (isMatch && alreadyFound(test)) {
        savedPoints.push_back(test);
    }
}

void findAvgBG(PNG img, PNG mask) {
    std::vector<int> avgList;
    std::vector<unsigned char> imgBuff = img.getBuffer();
    std::vector<unsigned char> maskBuff = mask.getBuffer();
    for (int i = 0; (i < img.getHeight() - mask.getHeight() + 1); i++) {
        for (int j = 0; (j < img.getWidth() - mask.getWidth() + 1); j++) {
            for (int k = i; (k < mask.getHeight() + i); k++) {
                for (int z = j; (z < mask.getWidth() + j); z++) {
                    if (avgBack(k, z, mask, img, i, j, imgBuff, maskBuff)
                            != 0) {
                        avgList.push_back(avgBack(k, z, mask, img, i, j,
                                imgBuff, maskBuff));
                    }
                }
            }
            int totAvg = findAvgOfList(avgList);
            int netMatch = findingMatches(totAvg, i, j, mask, img, PT, imgBuff);
            bool isMatch = match(netMatch, mask);

            saveCheck(i, j, isMatch);
        }
    }
}

bool customSort(std::pair<int, int>& a, std::pair<int, int>& b) {
    if (a.first == b.first) {
        return a.second < b.second;
    } else {
        return a.first < b.first;
    }
}

void sortHelper() {
    std::sort(savedPoints.begin(), savedPoints.end(), customSort);
}

void drawBox(PNG& png, int row, int col, int width, int height) {
    // Draw horizontal lines
    for (int i = 0; (i < width); i++) {
        png.setRed(row, col + i);
        png.setRed(row + height, col + i);
    }
    // Draw vertical lines
    for (int i = 0; (i < height); i++) {
        png.setRed(row + i, col);
        png.setRed(row + i, col + width);
    }
}

void print(PNG& mask, PNG& img) {
    sortHelper();

    for (unsigned int i = 0; i < savedPoints.size(); i++) {
        std::cout << "Match at: " << savedPoints[i].first << ", " <<
                savedPoints[i].second << ", " << savedPoints[i].first
                + mask.getHeight() << ", " << savedPoints[i].second +
                mask.getWidth() << "\n";
        drawBox(img, savedPoints[i].first, savedPoints[i].second,
                img.getWidth(), img.getHeight());
    }
}

int main(int argc, char** argv) {
    std::string largeFile = argv[1];
    std::string smallFile = argv[2];
    std::string outputFile = argv[3];
    MP = 75;
    PT = 32;
    if (argc == 4) {
        // isMask = argv[4]; // always true
    }
    if (argc == 5) {
        MP = std::stoi(argv[5]);  // default 75%
    }
    if (argc == 6) {
        PT = std::stoi(argv[6]);  // default 32
    }

    PNG maskFile;
    PNG imageFile;
    maskFile.load(smallFile);
    imageFile.load(largeFile);
    findAvgBG(imageFile, maskFile);
    print(maskFile, imageFile);
    imageFile.write(outputFile);

    std::cout << "Number of matches: " << savedPoints.size();
    return 0;
}
