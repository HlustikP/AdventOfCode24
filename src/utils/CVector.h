#pragma once

class CVector
{
public:
	CVector(int aHorizontal, int aVertical);
	[[nodiscard]] int getHorizontal() const;
	[[nodiscard]] int getVertical() const;
	CVector operator*(int aScalar) const;

private:
	int mHorizontal;
	int mVertical;
};
