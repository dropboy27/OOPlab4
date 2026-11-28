#include "figure_collection.h"
#include "triangle.h"
#include "square.h"
#include "pentagon.h"
#include <iostream>

int main()
{
    FigureCollection figures;

    figures.add(new Triangle(Point(0, 0), Point(4, 0), Point(0, 3)));
    figures.add(new Square());
    figures.add(new Pentagon());

    for (std::size_t i = 0; i < figures.size(); i++)
    {
        Figure* figure = figures.get(i);
        std::cout << *figure << '\n';

        Triangle* triangle = dynamic_cast<Triangle*>(figure);
        if (triangle != nullptr)
        {
            std::cout << "Equilateral: " << triangle->isEquilateral() << '\n';
        }

        Square* square = dynamic_cast<Square*>(figure);
        if (square != nullptr)
        {
            std::cout << "Side: " << square->side() << '\n';
        }

        Pentagon* pentagon = dynamic_cast<Pentagon*>(figure);
        if (pentagon != nullptr)
        {
            std::cout << "Regular: " << pentagon->isRegular() << '\n';
        }

        std::cout << '\n';
    }

    std::cout << "Total area: " << figures.total_metric() << '\n';

    return 0;
}