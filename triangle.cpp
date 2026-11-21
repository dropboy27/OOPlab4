#include "triangle.h"
#include "point.h"
#include <cmath>

Triangle::Triangle(Point a, Point b, Point c) : a_{a}, b_{b}, c_{c} {}

Point Triangle::center() const
{
    Point a = this->a_;
    Point b = this->b_;
    Point c = this->c_;
    double x_cent = (a.get_x() + b.get_x() + c.get_x()) / 3;
    double y_cent = (a.get_x() + b.get_x() + c.get_x()) / 3;
    Point ans(x_cent, y_cent);
}

double Triangle::metric() const
{
    double area = 0.5 * abs(a_.get_x() * b_.get_y() + b_.get_x() * c_.get_y() + c_.get_x() * a_.get_y() - a_.get_y() * b_.get_x() - b_.get_y() * c_.get_x() - c_.get_y() * a_.get_x());
    return area;
}

bool Triangle::isEquilateral() const
{
    double ab = sqrt((b_.get_x() - a_.get_y()) ^ 2)
}