#include "figure_collection.h"
#include <utility>
FigureCollection::FigureCollection() : data_{nullptr}, size_{0}, capacity_{0} {}

FigureCollection::~FigureCollection()
{
    for (std::size_t i = 0; i < size_; i++)
    {
        delete data_[i];
    }

    delete[] data_;
}

bool FigureCollection::add(Figure* figure)
{
    if (figure == nullptr)
    {
        return false;
    }

    for (std::size_t i = 0; i < size_; i++)
    {
        if (data_[i] == figure)
        {
            return false;
        }
    }

    if (size_ == capacity_)
    {
        std::size_t new_capacity;

        if (capacity_ == 0)
        {
            new_capacity = 1;
        }
        else
        {
            new_capacity = capacity_ * 2;
        }

        Figure** new_data = new Figure*[new_capacity];

        for (std::size_t i = 0; i < size_; i++)
        {
            new_data[i] = data_[i];
        }

        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    data_[size_] = figure;
    size_++;

    return true;
}

std::size_t FigureCollection::size() const
{
    return size_;
}

double FigureCollection::total_metric() const
{
    double sum = 0;

    for (std::size_t i = 0; i < size_; i++)
    {
        sum += data_[i]->metric();
    }

    return sum;
}

Figure* FigureCollection::get(std::size_t index)
{
    if (index >= size_)
    {
        return nullptr;
    }

    return data_[index];
}

const Figure* FigureCollection::get(std::size_t index) const
{
    if (index >= size_)
    {
        return nullptr;
    }

    return data_[index];
}

bool FigureCollection::remove(std::size_t index)
{
    if (index >= size_)
    {
        return false;
    }

    delete data_[index];

    for (std::size_t i = index; i + 1 < size_; i++)
    {
        data_[i] = data_[i + 1];
    }

    size_--;
    data_[size_] = nullptr;

    return true;
}


void FigureCollection::swap(FigureCollection& other) noexcept
{
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

FigureCollection::FigureCollection(const FigureCollection& other) : data_{nullptr}, size_{0}, capacity_{other.capacity_}
{
    data_ = new Figure*[capacity_];

    try
    {
        for (std::size_t i = 0; i < other.size_; i++)
        {
            data_[i] = other.data_[i]->clone();
            size_++;
        }
    }
    catch (...)
    {
        for (std::size_t i = 0; i < size_; i++)
        {
            delete data_[i];
        }

        delete[] data_;
        throw;
    }
}

FigureCollection& FigureCollection::operator=(const FigureCollection& other)
{
    if (this != &other)
    {
        FigureCollection temp(other);
        swap(temp);
    }

    return *this;
}

FigureCollection::FigureCollection(FigureCollection&& other) noexcept : data_{other.data_}, size_{other.size_}, capacity_{other.capacity_}
{
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

FigureCollection& FigureCollection::operator=(FigureCollection&& other) noexcept
{
    if (this != &other)
    {
        FigureCollection temp(std::move(other));
        swap(temp);
    }

    return *this;
}