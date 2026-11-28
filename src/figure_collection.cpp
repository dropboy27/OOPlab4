#include "figure_collection.h"

FigureCollection::FigureCollection() : data_{nullptr}, size_{0}, capacity_{0} {}

FigureCollection::~FigureCollection()
{
    for (std::size_t i = 0; i < size_; i++)
    {
        delete data_[i];
    }

    delete[] data_;
}