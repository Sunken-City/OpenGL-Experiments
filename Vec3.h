#pragma once

class Vec3
{
public:
	//Instead of making these private, it's much cleaner to make these public. Saves 6 accessor functions.
	double x;
	double y;
	double z;

	Vec3()
	{
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}

	//A sneaky way to use a Vec3 as a Vec2.
	Vec3(double X, double Y)
	{
		x = X;
		y = Y;
		z = 0.0;
	}

	Vec3(double X, double Y, double Z)
	{
		x = X;
		y = Y;
		z = Z;
	}
	
	Vec3& operator+= (Vec3& rhs)
	{
		//Addition of rhs to *this
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	bool operator== (Vec3& rhs)
	{
		//If x, y and z are equivalent, return true.
		return ((x == rhs.x) && (y == rhs.y) && (z == rhs.z));
	}

	bool operator!= (Vec3& rhs)
	{
		//If the values are NOT equivalent, return true.
		return (!((*this) == rhs));
	}
};

inline Vec3 operator+(Vec3& lhs, Vec3&  rhs)
{
	int newX = lhs.x + rhs.x;
	int newY = lhs.y + rhs.y;
	int newZ = lhs.z + rhs.z;
	return Vec3(newX, newY, newZ);
}

inline Vec3 operator-(Vec3& lhs, Vec3&  rhs)
{
	int newX = lhs.x - rhs.x;
	int newY = lhs.y - rhs.y;
	int newZ = lhs.z - rhs.z;
	return Vec3(newX, newY, newZ);
}