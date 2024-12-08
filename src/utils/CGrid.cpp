#include "CGrid.h"

#include <iostream>

#include "misc.h"

CGrid::CGrid(const std::string& aInput) : mData{ aInput }
{
    mRows = static_cast<int>(std::ranges::count(aInput, NEWLINE_DELIMITER));
    mColumns = static_cast<int>(aInput.find(NEWLINE_DELIMITER));
    if (aInput.back() != NEWLINE_DELIMITER) {
        mRows++;
    }
    std::erase(mData, NEWLINE_DELIMITER);
}

CGrid::CGrid(std::string&& aInput) : mData{ std::move(aInput) }
{
    mRows = static_cast<int>(std::ranges::count(aInput, NEWLINE_DELIMITER));
    mColumns = static_cast<int>(aInput.find(NEWLINE_DELIMITER));
    if (aInput.back() != NEWLINE_DELIMITER) {
        mRows++;
    }
    std::erase(mData, NEWLINE_DELIMITER);
}

std::optional<CCell> CGrid::moveInDirection(const CCell& aCell, EDirection aDirection) const
{
    switch (aDirection) {
    case EDirection::Up:
        if (isInBounds(aCell, EDirection::Up)) {
            return getCellAt(aCell.getRow() - 1, aCell.getCol());
        }
        break;
    case EDirection::Down:
        if (isInBounds(aCell, EDirection::Down)) {
            return getCellAt(aCell.getRow() + 1, aCell.getCol());
        }
        break;
    case EDirection::Left:
        if (isInBounds(aCell, EDirection::Left)) {
            return getCellAt(aCell.getRow(), aCell.getCol() - 1);
        }
        break;
    case EDirection::Right:
        if (isInBounds(aCell, EDirection::Right)) {
            return getCellAt(aCell.getRow(), aCell.getCol() + 1);
        }
        break;
    }

    return std::nullopt;
}

std::optional<CCell> CGrid::moveWithVector(const CCell& aCell, CVector aVector) const
{
    const auto lRow = aCell.getRow() + aVector.getVertical();
    const auto lCol = aCell.getCol() + aVector.getHorizontal();
    if (lRow >= 0 && lRow < mRows && lCol >= 0 && lCol < mColumns) {
        return getCellAt(lRow, lCol);
    }

    return std::nullopt;
}

CCell CGrid::getCellAt(int aRow, int aCol) const
{
    return CCell{ mData[aRow * mColumns + aCol], aRow, aCol };
}

void CGrid::setCellDataAt(int aRow, int aCol, char aData)
{
    mData[aRow * mColumns + aCol] = aData;
}

void CGrid::setCellDataAt(const CCell& aCell, char aData)
{
    const auto lIndex = aCell.getRow() * mColumns + aCell.getCol();
    if (lIndex < 0 || lIndex >= mData.size()) {
        std::cerr << "[ERROR] [CGrid] Invalid cell index" << std::endl;
        return;
    }

    mData[lIndex] = aData;
}

std::optional<CCell> CGrid::getFirstOccurrenceOf(char aData) const
{
    const auto lItr = std::ranges::find(mData, aData);
    if (lItr != mData.end()) {
        const auto lIndex = static_cast<int>(std::distance(mData.begin(), lItr));
        return CCell{ aData, lIndex / mColumns, lIndex % mColumns };
    }

    return std::nullopt;
}

std::vector<CCell> CGrid::getAllOccurrencesOf(char aData) const
{
    std::vector<CCell> lCells;
    for (int lRow = 0; lRow < mRows; lRow++) {
        for (int lCol = 0; lCol < mColumns; lCol++) {
            if (mData[lRow * mColumns + lCol] == aData) {
                lCells.emplace_back(aData, lRow, lCol);
            }
        }
    }

    return lCells;
}

int CGrid::getCount(char aData) const
{
    return static_cast<int>(std::ranges::count(mData, aData));
}

void CGrid::print() const
{
    for (int lRow = 0; lRow < mRows; lRow++) {
        for (int lCol = 0; lCol < mColumns; lCol++) {
            std::cout << mData[lRow * mColumns + lCol];
        }
        std::cout << std::endl;
    }
}

EDirection CGrid::rotateDirectionRight(EDirection aDirection)
{
    switch (aDirection)
    {
    case EDirection::Up:
        return EDirection::Right;
    case EDirection::Down:
        return EDirection::Left;
    case EDirection::Left:
        return EDirection::Up;
    case EDirection::Right:
        return EDirection::Down;
    default:
        std::cerr << "[ERROR] [CGrid] Invalid direction" << std::endl;
        return EDirection::Up;
    }
}

bool CGrid::isInBounds(const CCell& aCell, EDirection aDirection) const
{
    switch (aDirection) {
    case EDirection::Up:
        return aCell.getRow() - 1 >= 0;
    case EDirection::Down:
        return aCell.getRow() + 1 < mRows;
    case EDirection::Left:
        return aCell.getCol() - 1 >= 0;
    case EDirection::Right:
        return aCell.getCol() + 1 < mColumns;
    }

    return false;
}
