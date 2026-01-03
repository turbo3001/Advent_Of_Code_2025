//
// Created by Luke on 02/01/2026.
//

#pragma once
#include <array>
#include <cmath>
#include <cstdint>
#include <format>

template <typename DataType, std::size_t Size>
struct DimensionalVector
{
  template<std::same_as<DataType>... Args>
  explicit DimensionalVector(Args... Data)
  {
    static_assert(sizeof...(Args) <= Size, "Invalid number of arguments passed to DimensionalVector");
    data = {Data...};
  }

  DimensionalVector operator+(DimensionalVector const &Other)
  {
    DimensionalVector Result;
    for (std::size_t i = 0; i < Size; ++i)
    {
      Result.data[i] = data[i] + Other.data[i];
    }
    return Result;
  }

  DimensionalVector operator-(DimensionalVector const &Other)
  {
    DimensionalVector Result;
    for (std::size_t i = 0; i < Size; ++i)
    {
      Result.data[i] = data[i] - Other.data[i];
    }
    return Result;
  }

  DataType MagnitudeSquared() const
  {
    DataType Result = {};
    for (std::size_t i = 0; i < Size; ++i)
    {
      Result += data[i] * data[i];
    }
    return Result;
  }

  double Magnitude() const
  {
    return std::sqrt(MagnitudeSquared());
  }

  DataType operator%(DimensionalVector const &Other)
  {
    const DimensionalVector Result = *this - Other;
    const DataType MagnitudeSquared = Result.MagnitudeSquared();
    return MagnitudeSquared;
  }

  DataType& operator[]( std::size_t Index) { return data[Index]; }
  const DataType& operator[]( std::size_t Index) const { return data[Index]; }

  std::string ToString() const
  {
    std::string Result = "<";
    for (std::size_t i = 0; i < Size; ++i)
    {
      if (i != 0) Result += ", ";
      Result += std::to_string(data[i]);
    }
    Result += ">";
    return Result;
  }

private:
  std::array<DataType, Size> data;
};

typedef DimensionalVector<int, 3> IntVector3D;
typedef DimensionalVector<intmax_t, 3> IntMaxVector3D;