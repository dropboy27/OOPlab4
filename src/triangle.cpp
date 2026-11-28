#include "triangle.h"
#include "point.h"
#include <cmath>

Triangle::Triangle(Point a, Point b, Point c) : a_{a}, b_{b}, c_{c} {}

Point Triangle::center() const
{
    double x_cent = (a_.x_ + b_.x_ + c_.x_) / 3;
    double y_cent = (a_.y_ + b_.y_ + c_.y_) / 3;
    Point ans(x_cent, y_cent);
    return ans;
}

double Triangle::metric() const
{
    double area = 0.5 * std::abs(a_.x_ * b_.y_ - a_.y_ * b_.x_ +b_.x_ * c_.y_ - b_.y_ * c_.x_ +c_.x_ * a_.y_ - c_.y_ * a_.x_);
    return area;
}

bool Triangle::isEquilateral() const
{
    double ab = sqrt(pow((b_.x_ - a_.x_), 2) + pow((b_.y_ - a_.y_), 2));
    double ac = sqrt(pow((c_.x_ - a_.x_), 2) + pow((c_.y_ - a_.y_), 2));
    double bc = sqrt(pow((b_.x_ - c_.x_), 2) + pow((b_.y_ - c_.y_), 2));
    double eps = 1e-6;
    if (ab == 0 || ac == 0 || bc == 0)
    {
        return false;
    }
    return (abs((ab - bc)) < eps && abs((ab - ac)) < eps && abs((bc - ac)) < eps);
}

void Triangle::print(std::ostream& os) const
{
    Point p = center();
    os << "Triangle: (" << a_.x_ << ", " << a_.y_ << ") (" << b_.x_ << ", " << b_.y_ << ") (" << c_.x_ << ", " << c_.y_ << ")";
    os << "\nCenter: (" << p.x_ << ", " << p.y_ << ")";
    os << "\nArea: " << metric();
}

void Triangle::read(std::istream& is)
{
    Point vertices[3];

    if (readFigureData(is, "Triangle:", vertices, 3))
    {
        a_ = vertices[0];
        b_ = vertices[1];
        c_ = vertices[2];
    }
}

Figure* Triangle::clone() const
{
    return new Triangle(*this);
}