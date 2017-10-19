#ifndef CHART_MAKER_H
#define CHART_MAKER_H

/** A top-level class to perform operations on chart objects based on
        user input.

        NOTE: You may modify/add as many methods or instance variables
        as needed to design this class.
	
        Copyright (C) 2017 raodm@miamiOH.edu
 */

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>
#include "Chart.h"

class ChartMaker {
public:
    ChartMaker() {
    }

    ~ChartMaker() {
    }

    int run();
    std::string Help();
    void load(Chart& c);
    void plus(Chart& c);
    void minus(Chart& c);
    void multiply(Chart& c);
    void divide(Chart& c);
    void histogram(Chart& c);
    void shiftRight(Chart& c);
    void shiftLeft(Chart& c);
    void save(Chart& c);
    void printPoints(Chart& c);
    void printHelp(Chart& c);
    void quit();
    void checkIn(std::string in);
    Chart chart;

private:
    int x, y = 0;
    int max;
    int shift;
    std::string filePath = "";
    std::ofstream saveFile;
    bool exit = false;
};

#endif
