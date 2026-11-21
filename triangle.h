#include "figure.h"
#include "point.h"

class Triangle : public Figure
{
private:
    Point a_, b_, c_;

public:
    Triangle(Point a, Point b, Point c);
    Point center() const override;
    double metric() const override;
};