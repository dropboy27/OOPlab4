#include "point.h"
#include "pentagon.h"
#include <algorithm>
#include <cmath>
#include <numbers>

Pentagon::Pentagon(Point a, Point b, Point c, Point d, Point f) : a_{a}, b_{b}, c_{c}, d_{d}, f_{f} {}

Pentagon::Pentagon() : Pentagon(Point(1.0, 0.0), Point(std::cos(2 * std::numbers::pi / 5), std::sin(2 * std::numbers::pi / 5)), Point(std::cos(4 * std::numbers::pi / 5), std::sin(4 * std::numbers::pi / 5)), Point(std::cos(6 * std::numbers::pi / 5), std::sin(6 * std::numbers::pi / 5)), Point(std::cos(8 * std::numbers::pi / 5), std::sin(8 * std::numbers::pi / 5))) {}

double Pentagon::metric() const
{
    double area = 0.5 * std::abs(a_.x_ * b_.y_ - a_.y_ * b_.x_ + b_.x_ * c_.y_ - b_.y_ * c_.x_ + c_.x_ * d_.y_ - c_.y_ * d_.x_ + d_.x_ * f_.y_ - d_.y_ * f_.x_ + f_.x_ * a_.y_ - f_.y_ * a_.x_);
    return area;
}

Point Pentagon::center() const
{
    double x_cent = (a_.x_ + b_.x_ + c_.x_ + d_.x_ + f_.x_) / 5;
    double y_cent = (a_.y_ + b_.y_ + c_.y_ + d_.y_ + f_.y_) / 5;
    return Point(x_cent, y_cent);
}

bool Pentagon::isRegular() const
{
    double eps = 1e-6;

    double ab = std::sqrt(std::pow(b_.x_ - a_.x_, 2) + std::pow(b_.y_ - a_.y_, 2));
    double bc = std::sqrt(std::pow(c_.x_ - b_.x_, 2) + std::pow(c_.y_ - b_.y_, 2));
    double cd = std::sqrt(std::pow(d_.x_ - c_.x_, 2) + std::pow(d_.y_ - c_.y_, 2));
    double df = std::sqrt(std::pow(f_.x_ - d_.x_, 2) + std::pow(f_.y_ - d_.y_, 2));
    double fa = std::sqrt(std::pow(a_.x_ - f_.x_, 2) + std::pow(a_.y_ - f_.y_, 2));

    double lengths[5] = {ab, bc, cd, df, fa};

    for (int i = 0; i < 5; i++)
    {
        if (lengths[i] <= eps)
        {
            return false;
        }

        for (int j = i + 1; j < 5; j++)
        {
            if (std::abs(lengths[i] - lengths[j]) >= eps)
            {
                return false;
            }
        }
    }

    Point current[5] = {a_, b_, c_, d_, f_};
    Point previous[5] = {f_, a_, b_, c_, d_};
    Point next[5] = {b_, c_, d_, f_, a_};

    double expected_angle = 3 * std::numbers::pi / 5;

    for (int i = 0; i < 5; i++)
    {
        double ux = previous[i].x_ - current[i].x_;
        double uy = previous[i].y_ - current[i].y_;
        double vx = next[i].x_ - current[i].x_;
        double vy = next[i].y_ - current[i].y_;

        double u_length = std::sqrt(ux * ux + uy * uy);
        double v_length = std::sqrt(vx * vx + vy * vy);
        double cosine = (ux * vx + uy * vy) / (u_length * v_length);

        if (cosine > 1.0)
        {
            cosine = 1.0;
        }
        if (cosine < -1.0)
        {
            cosine = -1.0;
        }

        double angle = std::acos(cosine);

        if (std::abs(angle - expected_angle) >= eps)
        {
            return false;
        }
    }

    return true;
}

void Pentagon::print(std::ostream& os) const
{
    Point p = center();
    os << "Pentagon: (" << a_.x_ << ", " << a_.y_ << ") (" << b_.x_ << ", " << b_.y_ << ") (" << c_.x_ << ", " << c_.y_ << ") (" << d_.x_ << ", " << d_.y_ << ") (" << f_.x_ << ", " << f_.y_ << ")";
    os << "\nCenter: (" << p.x_ << ", " << p.y_ << ")";
    os << "\nArea: " << metric();
}

void Pentagon::read(std::istream& is)
{
    Point vertices[5];

    if (readFigureData(is, "Pentagon:", vertices, 5))
    {
        a_ = vertices[0];
        b_ = vertices[1];
        c_ = vertices[2];
        d_ = vertices[3];
        f_ = vertices[4];
    }
}

Figure* Pentagon::clone() const
{
    return new Pentagon(*this);
}