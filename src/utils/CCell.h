#pragma once
#include <iostream>
#include <ostream>
#include <unordered_map>

#include "CVector.h"

struct PodPosition
{
    int mRow;
    int mCol;
};

class CCell 
{
public:
    CCell(char aData, int aRow, int aCol);
    bool operator==(const CCell& aOther) const;
    CVector operator-(const CCell& aCell) const;
    CCell operator+(const CVector& aVector) const;

    [[nodiscard]] char getData() const;
    [[nodiscard]] int getRow() const;
    [[nodiscard]] int getCol() const;
    [[nodiscard]] PodPosition getPosition() const;

    friend std::ostream& operator<<(std::ostream& aStream, const CCell& aCell);

private:
    char mData;
    PodPosition mPosition;
};

template <>
struct std::hash<CCell>
{
    std::size_t operator()(const CCell& aCell) const noexcept
    {
        return static_cast<std::size_t>(aCell.getRow()) + (static_cast<std::size_t>(aCell.getCol()) << 32ll);
    }
};
