#include "figure.h"
#include "point.h"

class Square : public Figure
{
private:
    Point a_, b_, c_, d_;

public:
    Square();
    Square(Point a, Point b, Point c, Point d);
    double metric() const override;
    Point center() const override;
    ~Square() override = default;
    double side() const;
};