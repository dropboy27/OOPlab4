#pragma once
class Point
{
private:
    double x_, y_;

public:
    Point() : x_{0}, y_{0} {};
    Point(double x, double y) : x_{x}, y_{y} {};
    double get_x() const
    {
        return x_;
    }
    double get_y() const
    {
        return y_;
    }
};
