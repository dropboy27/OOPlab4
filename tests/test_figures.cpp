#include "triangle.h"
#include "square.h"
#include "pentagon.h"
#include "figure_collection.h"
#include <gtest/gtest.h>
#include <cmath>
#include <sstream>
#include <string>
#include <utility>

// площадь треугольника и вырожденный случай
TEST(FigureTest, TriangleArea)
{
    Triangle triangle(Point(0, 0), Point(4, 0), Point(0, 3));
    Triangle reversed(Point(0, 0), Point(0, 3), Point(4, 0));
    Triangle flat(Point(0, 0), Point(1, 1), Point(2, 2));

    EXPECT_NEAR(triangle.metric(), 6.0, 1e-6);
    EXPECT_NEAR(reversed.metric(), 6.0, 1e-6);
    EXPECT_NEAR(flat.metric(), 0.0, 1e-6);
}

// площадь квадрата
TEST(FigureTest, SquareArea)
{
    Square square(Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2));

    EXPECT_NEAR(square.metric(), 4.0, 1e-6);
}

// площадь пятиугольника
TEST(FigureTest, PentagonArea)
{
    Pentagon pentagon;

    EXPECT_NEAR(pentagon.metric(), 2.377641290737884, 1e-6);
}

// центры всех фигур
TEST(FigureTest, Centers)
{
    Triangle triangle(Point(0, 0), Point(4, 0), Point(2, 3));
    Square square(Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2));
    Pentagon pentagon;

    Point triangle_center = triangle.center();
    Point square_center = square.center();
    Point pentagon_center = pentagon.center();

    EXPECT_NEAR(triangle_center.x_, 2.0, 1e-6);
    EXPECT_NEAR(triangle_center.y_, 1.0, 1e-6);
    EXPECT_NEAR(square_center.x_, 1.0, 1e-6);
    EXPECT_NEAR(square_center.y_, 1.0, 1e-6);
    EXPECT_NEAR(pentagon_center.x_, 0.0, 1e-6);
    EXPECT_NEAR(pentagon_center.y_, 0.0, 1e-6);
}

// равносторонность треугольника
TEST(FigureTest, TriangleEquilateral)
{
    Triangle regular(Point(0, 0), Point(2, 0), Point(1, std::sqrt(3.0)));
    Triangle other(Point(0, 0), Point(4, 0), Point(0, 3));
    Triangle zero(Point(0, 0), Point(0, 0), Point(0, 0));

    EXPECT_TRUE(regular.isEquilateral());
    EXPECT_FALSE(other.isEquilateral());
    EXPECT_FALSE(zero.isEquilateral());
}

// длина стороны квадрата
TEST(FigureTest, SquareSide)
{
    Square square(Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2));

    EXPECT_NEAR(square.side(), 2.0, 1e-6);
}

// правильность пятиугольника
TEST(FigureTest, PentagonRegular)
{
    Pentagon regular;
    Pentagon other(Point(0, 0), Point(2, 0), Point(2, 2), Point(1, 3), Point(0, 2));
    Pentagon zero(Point(0, 0), Point(0, 0), Point(0, 0), Point(0, 0), Point(0, 0));

    EXPECT_TRUE(regular.isRegular());
    EXPECT_FALSE(other.isRegular());
    EXPECT_FALSE(zero.isRegular());
}

// приведение к правильному и неправильному типу
TEST(FigureTest, DynamicCast)
{
    Triangle triangle(Point(0, 0), Point(4, 0), Point(0, 3));
    Square square;
    Pentagon pentagon;
    Figure* figure = &triangle;

    EXPECT_NE(dynamic_cast<Triangle*>(figure), nullptr);
    EXPECT_EQ(dynamic_cast<Square*>(figure), nullptr);

    figure = &square;
    EXPECT_NE(dynamic_cast<Square*>(figure), nullptr);
    EXPECT_EQ(dynamic_cast<Pentagon*>(figure), nullptr);

    figure = &pentagon;
    EXPECT_NE(dynamic_cast<Pentagon*>(figure), nullptr);
    EXPECT_EQ(dynamic_cast<Triangle*>(figure), nullptr);
}

// добавление и удаление фигур
TEST(FigureCollectionTest, AddRemove)
{
    FigureCollection figures;

    EXPECT_EQ(figures.size(), 0u);
    EXPECT_NEAR(figures.total_metric(), 0.0, 1e-6);
    EXPECT_EQ(figures.get(0), nullptr);
    EXPECT_FALSE(figures.remove(0));
    EXPECT_FALSE(figures.add(nullptr));

    Triangle* triangle = new Triangle(Point(0, 0), Point(4, 0), Point(0, 3));
    EXPECT_TRUE(figures.add(triangle));
    EXPECT_FALSE(figures.add(triangle));
    EXPECT_TRUE(figures.add(new Square()));
    EXPECT_EQ(figures.size(), 2u);
    EXPECT_NEAR(figures.total_metric(), 7.0, 1e-6);

    EXPECT_TRUE(figures.remove(0));
    EXPECT_EQ(figures.size(), 1u);
    EXPECT_NEAR(figures.total_metric(), 1.0, 1e-6);
    EXPECT_NE(dynamic_cast<Square*>(figures.get(0)), nullptr);
    EXPECT_EQ(figures.get(1), nullptr);
}

// глубокое копирование коллекции
TEST(FigureCollectionTest, Copy)
{
    FigureCollection figures;
    figures.add(new Triangle(Point(0, 0), Point(4, 0), Point(0, 3)));
    figures.add(new Square());
    figures.add(new Pentagon());

    FigureCollection copy(figures);
    EXPECT_EQ(copy.size(), 3u);
    EXPECT_NE(copy.get(0), figures.get(0));
    EXPECT_NE(copy.get(1), figures.get(1));
    EXPECT_NE(copy.get(2), figures.get(2));
    EXPECT_NE(dynamic_cast<Triangle*>(copy.get(0)), nullptr);
    EXPECT_NE(dynamic_cast<Square*>(copy.get(1)), nullptr);
    EXPECT_NE(dynamic_cast<Pentagon*>(copy.get(2)), nullptr);
    EXPECT_NEAR(copy.total_metric(), 9.377641290737884, 1e-6);

    FigureCollection assigned;
    assigned.add(new Square());
    assigned = copy;

    EXPECT_EQ(assigned.size(), 3u);
    EXPECT_NE(assigned.get(0), copy.get(0));
    EXPECT_NE(assigned.get(1), copy.get(1));
    EXPECT_NE(assigned.get(2), copy.get(2));

    figures.remove(0);
    copy.remove(1);
    EXPECT_EQ(assigned.size(), 3u);
    EXPECT_NEAR(assigned.total_metric(), 9.377641290737884, 1e-6);
}

// перемещение коллекции
TEST(FigureCollectionTest, Move)
{
    FigureCollection figures;
    figures.add(new Triangle(Point(0, 0), Point(4, 0), Point(0, 3)));
    Figure* original = figures.get(0);

    FigureCollection moved(std::move(figures));
    EXPECT_EQ(figures.size(), 0u);
    EXPECT_EQ(moved.size(), 1u);
    EXPECT_EQ(moved.get(0), original);
    EXPECT_NEAR(moved.total_metric(), 6.0, 1e-6);

    FigureCollection assigned;
    assigned.add(new Square());
    assigned = std::move(moved);

    EXPECT_EQ(moved.size(), 0u);
    EXPECT_EQ(assigned.size(), 1u);
    EXPECT_EQ(assigned.get(0), original);
    EXPECT_NEAR(assigned.total_metric(), 6.0, 1e-6);
}

// вывод фигур в поток
TEST(FigureTest, Output)
{
    Triangle triangle(Point(0, 0), Point(4, 0), Point(0, 3));
    Square square;
    Pentagon pentagon;
    std::ostringstream output;

    output << triangle;

    EXPECT_NE(output.str().find("Triangle:"), std::string::npos);
    EXPECT_NE(output.str().find("(4, 0)"), std::string::npos);
    EXPECT_NE(output.str().find("Center:"), std::string::npos);
    EXPECT_NE(output.str().find("Area: 6"), std::string::npos);

    output << square << pentagon;
    EXPECT_NE(output.str().find("Square:"), std::string::npos);
    EXPECT_NE(output.str().find("Pentagon:"), std::string::npos);
}

// чтение фигур из потока
TEST(FigureTest, Input)
{
    Triangle triangle(Point(0, 0), Point(1, 0), Point(0, 1));
    std::istringstream input("Triangle: (0, 0) (4, 0) (0, 3)\nCenter: (1.33333, 1)\nArea: 6");

    input >> triangle;

    ASSERT_FALSE(input.fail());
    EXPECT_NEAR(triangle.metric(), 6.0, 1e-6);

    Square original(Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2));
    Square square;
    std::stringstream stream;
    stream << original;
    stream >> square;

    ASSERT_FALSE(stream.fail());
    EXPECT_NEAR(square.metric(), 4.0, 1e-6);
}

// сравнение фигур по площади
TEST(FigureTest, Equality)
{
    Triangle first(Point(0, 0), Point(4, 0), Point(0, 3));
    Triangle shifted(Point(1, 1), Point(5, 1), Point(1, 4));
    Triangle close(Point(0, 0), Point(4, 0), Point(0, 3.00000001));
    Triangle smaller(Point(0, 0), Point(4, 0), Point(0, 2));
    Square square(Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2));

    EXPECT_TRUE(first == shifted);
    EXPECT_TRUE(first == close);
    EXPECT_FALSE(first == square);
    EXPECT_TRUE(smaller == square);
}

// преобразование фигуры в число
TEST(FigureTest, DoubleConversion)
{
    Triangle triangle(Point(0, 0), Point(4, 0), Point(0, 3));

    double area = static_cast<double>(triangle);

    EXPECT_NEAR(area, 6.0, 1e-6);
}
