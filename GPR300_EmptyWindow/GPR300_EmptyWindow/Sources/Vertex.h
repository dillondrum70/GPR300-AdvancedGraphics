#ifndef VERTEX_H
#define VERTEX_H

#include "Vec3.h"
#include "Color.h"

struct Vertex
{
	Vec3 position;
	Color color;

	Vertex(Vec3 pos, Color col)
	{
		position = pos;
		color = col;
	}
};

#endif
