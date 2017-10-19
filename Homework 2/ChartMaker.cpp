#ifndef CHART_MAKER_CPP
#define CHART_MAKER_CPP

// Copyright (C) 2017 raodm@miamiOH.edu

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "ChartMaker.h"
#include "Point.h"
#include "Chart.h"

int ChartMaker::run() {
    std::string in;
    std::cout << "Enter command (h for help): ";
    do {
        std::cin >> in;
        checkIn(in);
        std::cout << "Enter command (h for help): ";
    } while (in != "q");
    return 0;
}

void ChartMaker::checkIn(std::string in) {
    if (in == "l") {
        load(chart);
    } else if (in == "+") {
        plus(chart);
    } else if (in == "-") {
        minus(chart);
    } else if (in == "*") {
        multiply(chart);
    } else if (in == "/") {
        divide(chart);
    } else if (in == "?") {
        histogram(chart);
    } else if (in == "<") {
        shiftLeft(chart);
    } else if (in == ">") {
        shiftRight(chart);
    } else if (in == "s") {
        save(chart);
    } else if (in == "p") {
        printPoints(chart);
    } else if (in == "h") {
        Help();
    } else {
        std::cout << "Input not received or didn't work \n";
    }}

std::string ChartMaker::Help() {
    std::string input;
    std::cout << "Valid commands are:\n "
            "l: Load data from file as current set of points \n"
            "+: Add data from another to current points \n"
            "-: Subtract data from another file from current points \n"
            "*: Scale current points by give pair of values \n"
            "/: Scale current points by given pair of values \n"
            "?: Print histogram of current point distribution \n"
            "<: Shift points to the left by a given value \n"
            ">: Shift points the the right by a given value \n"
            "s: Save the current set of points to a given file \n"
            "p: Print current set of points on screen \n"
            "h: Print this message \n"
            "q: Quit \n"
            "Enter command (h for help): ";

    return input;
}

void ChartMaker::load(Chart& c) {
    std::string str = " ";
    std::cout << "Enter path to file: ";
    std::cin >> str;
    std::ifstream input(str);
    input >> c;
}

void ChartMaker::plus(Chart& c) {
    Chart temp;
    std::string str;
    std::cout << "Enter path to file: ";
    std::cin >> str;
    std::ifstream input(str);
    input >> temp;
    c.pointList.insert(c.pointList.end(), temp.pointList.begin(),
            temp.pointList.end());
}

void ChartMaker::minus(Chart& c) {
    Chart temp;
    std::string str;
    std::cout << "Enter path to file: ";
    std::cin >> str;
    std::ifstream input(str);
    input >> temp;
    c = c - temp;
}

void ChartMaker::multiply(Chart& c) {
    std::cout << "Enter values to scale x and y by: ";
    std::cin >> x;
    std::cin >> y;
    c = c * Point(x, y);
}

void ChartMaker::divide(Chart& c) {
    std::cout << "Enter values to scale x and y by: ";
    std::cin >> x;
    std::cin >> y;
    c = c / Point(x, y);
}

void ChartMaker::histogram(Chart& c) {
    std::cout << "Enter max size for histogram: ";
    std::cin >> max;
    c.analyze(std::cout, max);
}

void ChartMaker::shiftRight(Chart& c) {
    std::cout << "Enter amount to shift by: ";
    std::cin >> shift;
    c = c << shift;
}

void ChartMaker::shiftLeft(Chart& c) {
    std::cout << "Enter amount to shift by: ";
    std::cin >> shift;
    c = c >> shift;
}

void ChartMaker::save(Chart& c) {
    std::cout << "Enter path to file: ";
    std::cin >> filePath;
    saveFile.open(filePath);
    saveFile << c;
    saveFile.close();
}

void ChartMaker::printPoints(Chart& c) {
    std::cout << c;
}

void ChartMaker::quit() {
    exit = true;
}

#endif
