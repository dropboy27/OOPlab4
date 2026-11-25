#include "figure.h"
#include "point.h"
#include "square.h"
#include <cmath>

Square::Square(): a_{Point(0, 0)}, b_{Point(1, 0)}, c_{Point(0, 1)}, d_{Point(1, 1)} {}
Square::Square(Point a, Point b, Point c, Point d) : a_{a}, b_{b}, c_{c}, d_{d} {}
double Square::metric() const
{
    double area = 0.5 * std::abs(a_.x_ * b_.y_ - a_.y_ * b_.x_ + b_.x_ * c_.y_ - b_.y_ * c_.x_ + c_.x_ * d_.y_ - c_.y_ * d_.x_ + d_.x_ * a_.y_ - d_.y_ * a_.x_);
    return area;
}
Point Square::center() const
{
    double x_cent = (a_.x_ + b_.x_ + c_.x_ + d_.x_) / 4;
    double y_cent = (a_.y_ + b_.y_ + c_.y_ + d_.y_) / 4;
    Point ans(x_cent, y_cent);
    return ans;
}
double Square::side() const
{
    double ab = std::sqrt(pow((b_.x_ - a_.x_), 2) + std::pow((b_.y_ - a_.y_), 2));
    return ab;
}