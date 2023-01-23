#ifndef COLOR_H
#define COLOR_H

struct Color
{
	float r, g, b, a;

	Color()
	{
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;
		a = 1.0f;
	}

	Color(float vR, float vG, float vB, float vA)
	{
		r = vR;
		g = vG;
		b = vB;
		a = vA;
	}
};

#endif
