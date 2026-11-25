#pragma once
#include "point.h"
#include <ostream>


class Figure
{
public:
    virtual double metric() const = 0;
    virtual Point center() const = 0;
    virtual ~Figure() = default;
    virtual void print(std::ostream&) const;
};

std::ostream& operator<<(std::ostream& os, const Figure& figure);