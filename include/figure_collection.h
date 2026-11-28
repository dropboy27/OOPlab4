#pragma once
#include "figure.h"
#include <cstddef>

class FigureCollection
{
private:
    Figure** data_;
    std::size_t size_;
    std::size_t capacity_;

public:
    FigureCollection();
    ~FigureCollection();
    FigureCollection(const FigureCollection& other);
    FigureCollection& operator=(const FigureCollection& other);
    FigureCollection(FigureCollection&& other) noexcept;
    FigureCollection& operator=(FigureCollection&& other) noexcept;
};