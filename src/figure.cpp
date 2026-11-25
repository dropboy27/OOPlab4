#include "figure.h"

std::ostream& operator<<(std::ostream& os, const Figure& figure)
{
    figure.print(os);
    return os;
}