#include "CCell.h"

#include <ostream>

CCell::CCell(char aData, int aRow, int aCol) : mData{ aData }, mPosition{ aRow, aCol } {}

bool CCell::operator==(const CCell& aOther) const
{
    return mPosition.mRow == aOther.getRow() && mPosition.mCol == aOther.getCol();
}

CVector CCell::operator-(const CCell& aCell) const
{
    return CVector{ mPosition.mCol - aCell.getCol(), mPosition.mRow - aCell.getRow() };
}

CCell CCell::operator+(const CVector& aVector) const
{
    return CCell{ mData, mPosition.mRow + aVector.getVertical(), mPosition.mCol + aVector.getHorizontal() };
}

char CCell::getData() const
{
    return mData;
}

int CCell::getRow() const
{
    return mPosition.mRow;
}

int CCell::getCol() const
{
    return mPosition.mCol;
}

PodPosition CCell::getPosition() const
{
    return mPosition;
}

std::ostream& operator<<(std::ostream& aStream, const CCell& aCell)
{
    aStream << std::format("(Row:{} Col:{} Data:'{}')", aCell.mPosition.mRow, aCell.mPosition.mCol, aCell.mData);
    return aStream;
}
