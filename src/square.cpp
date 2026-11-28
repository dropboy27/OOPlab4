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

void Square::print(std::ostream& os) const
{
    Point p = center();
    os << "Square: (" << a_.x_ << ", " << a_.y_ << ") (" << b_.x_ << ", " << b_.y_ << ") (" << c_.x_ << ", " << c_.y_ << ") (" << d_.x_ << ", " << d_.y_ << ")";
    os << "\nCenter: (" << p.x_ << ", " << p.y_ << ")";
    os << "\nArea: " << metric();
}

void Square::read(std::istream& is)
{
    Point vertices[4];

    if (readFigureData(is, "Square:", vertices, 4))
    {
        a_ = vertices[0];
        b_ = vertices[1];
        c_ = vertices[2];
        d_ = vertices[3];
    }
}

Figure* Square::clone() const
{
    return new Square(*this);
}