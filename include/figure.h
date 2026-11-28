#pragma once
#include "point.h"
#include <ostream>
#include <istream>

class Figure
{
public:
    virtual double metric() const = 0;
    virtual Point center() const = 0;
    virtual ~Figure() = default;
    virtual void print(std::ostream&) const = 0;
    virtual void read(std::istream& is) = 0;
    bool operator==(const Figure& other) const;
    operator double() const;
    virtual Figure* clone() const = 0;
};

std::ostream& operator<<(std::ostream& os, const Figure& figure);
bool readFigureData(std::istream& is, const char* name, Point* vertices, int count);
std::istream& operator>>(std::istream& is, Figure& figure);