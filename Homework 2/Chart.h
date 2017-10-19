/* 
 * File:   Chart.h
 * Author: Mark Hutchinson
 * 
 * Copyright 2017
 */

#ifndef CHART_H
#define CHART_H

#include <string>
#include <vector>
#include "Point.h"

class Chart {
    friend std::ostream& operator<<(std::ostream& os, const Chart& c);
    friend std::istream& operator>>(std::istream& is, Chart& c);

public:
    Chart();  // Constructor

    Chart(const std::string& fileName);
    ~Chart();  // De-constructor

    bool contains(const Point& p) const;
    Chart& operator=(const Chart& src);
    Chart operator+(const Chart& other) const;
    Chart operator-(const Chart& other) const;
    Chart operator*(const Point& scale) const;
    Chart operator/(const Point& scale) const;
    Chart operator>>(int value) const;
    Chart operator<<(int value) const;
    void analyze(std::ostream& os, const int scale) const;
    std::vector<Point> pointList;
private:    
};

#endif /* CHART_H */

