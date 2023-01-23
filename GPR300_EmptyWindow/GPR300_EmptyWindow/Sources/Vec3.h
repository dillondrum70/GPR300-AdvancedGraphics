#ifndef VEC3_H
#define VEC3_H

struct Vec3
{
	float x, y, z;

	Vec3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vec3(float vX, float vY, float vZ)
	{
		x = vX;
		y = vY;
		z = vZ;
	}
};

#endif