#include "figure.h"
#include <string>
#include <istream>
#include <cmath>

std::ostream& operator<<(std::ostream& os, const Figure& figure)
{
    figure.print(os);
    return os;
}


bool readFigureData(std::istream& is, const char* name, Point* vertices, int count)
{
    std::string label;
    char opening, comma, closing;

    if (!(is >> label))
    {
        return false;
    }

    if (label != name)  
    {
        is.setstate(std::ios::failbit);
        return false;
    }

    for (int i = 0; i < count; i++)
    {
        if (!(is >> opening >> vertices[i].x_ >> comma >> vertices[i].y_ >> closing))
        {
            return false;
        }

        if (opening != '(' || comma != ',' || closing != ')')
        {
            is.setstate(std::ios::failbit);
            return false;
        }
    }

    Point saved_center;
    double saved_area;
    std::string center_label, area_label;

    if (!(is >> center_label >> opening >> saved_center.x_ >> comma >> saved_center.y_ >> closing >> area_label >> saved_area))
    {
        return false;
    }

    if (center_label != "Center:" || opening != '(' || comma != ',' || closing != ')' || area_label != "Area:")
    {
        is.setstate(std::ios::failbit);
        return false;
    }

    return true;
}

std::istream& operator>>(std::istream& is, Figure& figure)
{
    figure.read(is);
    return is;
}

bool Figure::operator==(const Figure& other) const
{
    double eps = 1e-6;
    return std::abs(metric() - other.metric()) < eps;
}

Figure::operator double() const
{
    return metric();
}