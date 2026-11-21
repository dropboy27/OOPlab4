
#pragma once
#include "point.h"

class Figure
{
public:
    virtual double metric() const = 0;
    virtual Point center() const = 0;
    virtual ~Figure() = default;
};
