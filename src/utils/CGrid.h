#pragma once
#include <optional>
#include <string>
#include <vector>

#include "CCell.h"

enum class EDirection
{
    Up,
    Down,
    Left,
    Right
};

class CGrid
{
public:
    explicit CGrid(const std::string& aInput);
    explicit CGrid(std::string&& aInput);

    std::optional<CCell> moveInDirection(const CCell& aCell, EDirection aDirection) const;
    [[nodiscard]] CCell getCellAt(int aRow, int aCol) const;
    void setCellDataAt(int aRow, int aCol, char aData);
    void setCellDataAt(const CCell& aCell, char aData);
    std::optional<CCell> getFirstOccurrenceOf(char aData) const;
    std::vector<CCell> getAllOccurrencesOf(char aData) const;
    int getCount(char aData) const;
    void print() const;

    static EDirection rotateDirectionRight(EDirection aDirection);
private:
    int mRows;
    int mColumns;
    std::string mData;

    [[nodiscard]] bool isInBounds(const CCell& aCell, EDirection aDirection) const;
};
