#pragma once
#include "figure.h"
#include "point.h"

class Pentagon : public Figure
{
private:
    Point a_, b_, c_, d_, f_;

public:
    Pentagon();
    Pentagon(Point a, Point b, Point c, Point d,  Point f);
    double metric() const override;
    Point center() const override;
    ~Pentagon() override = default;
    bool isRegular() const;
    void print(std::ostream&) const override;
    void read(std::istream& is) override;
    Figure* clone() const override;
};