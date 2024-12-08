#include "CVector.h"

CVector::CVector(int aHorizontal, int aVertical): mHorizontal{ aHorizontal }, mVertical{ aVertical } {}

int CVector::getHorizontal() const
{
    return mHorizontal;
}

int CVector::getVertical() const
{
    return mVertical;
}

CVector CVector::operator*(int aScalar) const
{
    return CVector{ mHorizontal * aScalar, mVertical * aScalar };
}
