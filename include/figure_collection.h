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
    bool add(Figure* figure);
    std::size_t size() const;
    double total_metric() const;
    Figure* get(std::size_t index);
    const Figure* get(std::size_t index) const;
    bool remove(std::size_t index);
    void swap(FigureCollection& other) noexcept;
};