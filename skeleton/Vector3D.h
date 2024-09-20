#pragma once
#include <cmath>
class Vector3D
{
private:
	float x;
	float y;
	float z;
public:
	Vector3D(float X, float Y, float Z) :x(X), y(Y), z(Z) {};

	const float& getX()
	{
		return x;
	}

	const float& getY()
	{
		return y;
	}

	const float& getZ()
	{
		return z;
	}
	float modulo();
	Vector3D normalized();
	float escalar(const Vector3D* other);

	Vector3D operator*( const float n) const
	{
		return Vector3D(x*n, y*n, z*n);
	}
	float operator*(const Vector3D other) const
	{
		return (x * other.x + y * other.y + z * other.z);
	}
		Vector3D operator+( const Vector3D other) const
	{
		return Vector3D(x + other.x , y + other.y , z + other.z);
	}
		Vector3D operator-(const Vector3D other) const
		{
			return Vector3D(x - other.x, y - other.y, z - other.z);
		}

};

