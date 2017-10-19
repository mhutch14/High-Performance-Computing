/* 
 * File:   Chart.cpp
 * Author: Mark Hutchinson
 * 
 * Copyright 2017
 */

#include <vector>
#include <istream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include "Chart.h"
#include "Point.h"
#include "ChartMaker.h"

int I, II, III, IV;
void print(int max, int scale);

Chart::Chart() {
    pointList = std::vector<Point>(0);  //  Default Constructor
}

Chart::Chart(const std::string& fileName) {
    std::ifstream inFile(fileName);
    std::istream_iterator<Point> in_ter(inFile), eof;
    std::copy(in_ter, eof, std::back_inserter(pointList));
}

Chart::~Chart() {
}

std::ostream& operator<<(std::ostream& os, const Chart& c) {
    for (unsigned int i = 0; i < c.pointList.size(); i++) {
        os << c.pointList.at(i).getX() << ", "
                << c.pointList.at(i).getY() << "\n";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Chart& c) {
    while (!is.eof()) {
        int y = 0, z = 0;
        is >> y >> z;
        Point p(y, z);
        c.pointList.push_back(p);
    }
    return is;
}

Chart& Chart::operator=(const Chart& src) {
    pointList = src.pointList;
    return *this;
}

bool Chart::contains(const Point& p) const {
    return ((std::find(pointList.begin(), pointList.end(), p)
            == pointList.end())) ? true : false;
}

Chart Chart::operator+(const Chart& other) const {
    Chart chart = *this;
    std::copy_if(other.pointList.begin(), other.pointList.end(),
            std::back_inserter(chart.pointList),
            [this](const Point & p) {
                return !(this->contains(p));
            });
    return chart;
}

Chart Chart::operator-(const Chart& other) const {
    Chart chart;
    copy_if(pointList.begin(), pointList.end(),
            std::back_insert_iterator <std::vector < Point >> (chart.pointList),
            [&other] (Point p) {
                return other.contains(p);
            });
    return chart;
}

Chart Chart::operator*(const Point& scale) const {
    Chart chart = *this;
    std::transform(chart.pointList.begin(), chart.pointList.end(),
            chart.pointList.begin(),
            [&scale] (const Point & p) {
                return Point(p.getX() * scale.getX(),
                        p.getY() * scale.getY());
            });
    return chart;
}

Chart Chart::operator/(const Point& scale) const {
    Chart chart = *this;
    std::transform(chart.pointList.begin(), chart.pointList.end(),
            chart.pointList.begin(),
            [&scale] (const Point & p) {
                return Point(p.getX() / scale.getX(),
                        p.getY() / scale.getY());
            });
    return chart;
}

Chart Chart::operator>>(int value) const {
    Chart chart = *this;
    for (; value > 0; value--) {
        chart.pointList.insert(chart.pointList.begin(), Point(0, 0));
    }
    return chart;
}

Chart Chart::operator<<(int value) const {
    Chart chart = *this;
    for (; value > 0; value--) {
        chart.pointList.erase(chart.pointList.begin());
    }
    return chart;
}

void Chart::analyze(std::ostream& os, const int scale) const {
    int histoMax;
    for (unsigned int i = 0; i < pointList.size(); i++) {
        switch (pointList[i].getQuadrant()) {
            case 1: I++;
                break;
            case 2: II++;
                break;
            case 3: III++;
                break;
            case 4: IV++;
                break;
        }

        histoMax = std::max(std::max(I, II), std::max(III, IV));
    }
    print(histoMax, scale);
}

void print(int max, int scale) {
    int quadI, quadII, quadIII, quadIV;
    quadI = (I * scale) / max;
    quadII = (II * scale) / max;
    quadIII = (III * scale) / max;
    quadIV = (IV * scale) / max;

    std::cout << "\nI: ";
    for (; quadI > 0; quadI--) {
        std::cout << "*";
    }
    std::cout << "\nII: ";
    for (; quadII > 0; quadII--) {
        std::cout << "*";
    }
    std::cout << "\nIII: ";
    for (; quadIII > 0; quadIII--) {
        std::cout << "*";
    }
    std::cout << "\nIV: ";
    for (; quadIV > 0; quadIV--) {
        std::cout << "*";
    }
    std::cout << "\n";
}

bool contains(std::vector<Point> v, Point pt) {
    bool inVector = false;
    for (unsigned int i = 0; i < v.size(); i++) {
        if (v.at(i) == pt) {
            inVector = true;
        }
    }
    return inVector;
}
