#pragma once

template <typename T>
class Vec3
{
public:
	//Instead of making these private, it's much cleaner to make these public. Saves 6 accessor functions.
	T x;
	T y;
	T z;

	Vec3()
	{
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}

	Vec3(T X, T Y, T Z)
	{
		x = X;
		y = Y;
		z = Z;
	}

	Vec3<T>& operator+= (Vec3<T>& rhs)
	{
		//Addition of rhs to *this
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vec3<T>& operator-= (Vec3<T>& rhs)
	{
		//Addition of rhs to *this
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	bool operator== (Vec3<T>& rhs)
	{
		//If x, y and z are equivalent, return true.
		return ((x == rhs.x) && (y == rhs.y) && (z == rhs.z));
	}

	bool operator!= (Vec3<T>& rhs)
	{
		//If the values are NOT equivalent, return true.
		return (!((*this) == rhs));
	}
};

template <typename T>
inline Vec3<T> operator+(Vec3<T>& lhs, Vec3<T>&  rhs)
{
	int newX = lhs.x + rhs.x;
	int newY = lhs.y + rhs.y;
	int newZ = lhs.z + rhs.z;
	return Vec3<T>(newX, newY, newZ);
}

template <typename T>
inline Vec3<T> operator-(Vec3<T>& lhs, Vec3<T>&  rhs)
{
	int newX = lhs.x - rhs.x;
	int newY = lhs.y - rhs.y;
	int newZ = lhs.z - rhs.z;
	return Vec3<T>(newX, newY, newZ);
}