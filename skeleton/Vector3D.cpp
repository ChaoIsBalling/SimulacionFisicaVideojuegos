#include "Vector3D.h"

float Vector3D::modulo()
{
	return  sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));;
}

Vector3D Vector3D::normalized()
{
	float m = modulo();

	return Vector3D(x / m, y / m, z / m);
}

float Vector3D::escalar(const Vector3D* other)
{
	
	return (x*other->x + y*other->y+z*other->z );
}

